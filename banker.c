#include <stdio.h>
#include <pthread.h>
#include "util.h"
extern pthread_mutex_t lock;

extern int n_processes;
extern int n_resources;

extern int *sys_available;
extern int **held;
extern int **max;
extern int **need;


/**
 *
 * @param pid
 * @param resources
 * @return 0 on success (safe state)
 * or -1 (an unsafe state)
 */
int request_resources(int pid, int resources[])
{

    pthread_mutex_lock(&lock);
    printf("pid %d is requesting:\n", pid);
    print_vector(resources, n_resources);
    printf("remaining resources are:\n", pid);
    print_vector(sys_available, n_resources);
    int ret;
    for (int i = 0; i < n_processes; i++)
    {
        for (int j = 0; j < n_resources; j++)
            need[i][j] = max[i][j] - held[i][j];
    }

    if (vector_compare(need[pid], resources, n_resources))
    {
        if (vector_compare(sys_available, resources, n_resources))
        {
            printf("safe!\n");

            vector_sub(sys_available, resources, n_resources);
            vector_add(held[pid], resources, n_resources);
            vector_sub(need[pid], resources, n_resources);
            ret = 0;
        }
        else
        {
            printf("unsafe, requesting more than available!\n");
            ret = -1;
        }
    }
    else
    {
        printf("unsafe, requesting more than needed!\n");
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