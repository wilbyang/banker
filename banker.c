#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "util.h"
extern pthread_mutex_t lock;

extern int n_processes;
extern int n_resources;

extern int *sys_available;
extern int **held;
extern int **max;
extern int **need;

bool safe_detect();

/**
 * return 0 on success (safe state)
 *  or -1 (an unsafe state) 
 * 
 * 
 * */
int request_resources(int pid, int resources[])
{
    pthread_mutex_lock(&lock);
    int ret;
    bool safe = false;

    if (vector_compare(need[pid], resources, n_resources))
    {
        if (vector_compare(sys_available, resources, n_resources))
        {
            vector_sub(sys_available, resources, n_resources);
            vector_add(held[pid], resources, n_resources);
            vector_sub(need[pid], resources, n_resources);
            safe = safe_detect();
        }
        else
        {
            printf("程序所申请资源大于系统当前所剩资源，推迟执行!\n");
            ret = -1;
        }
    }
    else
    {
        printf("程序所申请资源大于该程序所需资源，无法执行!\n");
        ret = -1;
    }

    if (safe)
    {
        printf("系统安全,进程可以执行!\n");
        ret = 0;
    }
    else
    {
        printf("系统不安全,进程无法执行!\n");
        vector_add(sys_available, resources, n_resources);
        vector_sub(held[pid], resources, n_resources);
        vector_add(need[pid], resources, n_resources);
        ret = -1;
    }

    pthread_mutex_unlock(&lock);
    return ret;
}

void release_resources(int pid, int resources[])
{
    pthread_mutex_lock(&lock);
    vector_add(sys_available, resources, n_resources);
    vector_sub(held[pid], resources, n_resources);
    vector_add(need[pid], resources, n_resources);
    pthread_mutex_unlock(&lock);
}
bool safe_detect()
{
    int *work = sys_available;
    bool *finish = (bool *)malloc(sizeof(bool) * n_processes);
    int i;
    bool safe;

    //初始化finish
    for (i = 0; i < n_processes; i++)
        finish[i] = false;

    for (i = 0; i < n_processes; i++)
    {
        if (finish[i] == false && vector_compare(work, need[i], n_resources))
        {
            printf("尝试执行第%d进程\n", i + 1);
            vector_add(work, held[i], n_resources); //尝试执行该进程，释放资源

            finish[i] = true;
            i = -1; //尝试分配后，从头查找是否还有可以执行的进程，考虑到i++，故此处为-1
        }
    }

    for (i = 0; i < n_processes; i++)
        if (finish[i] == false)
            break;
    if (i == n_processes)
        safe = true;
    else
        safe = false;
    return safe;
}