/*In banker.c, provide an implementation of request_resources() and release_resources() that 
uses the Banker’s algorithm to determine if the resulting state would be safe or unsafe. 
Note that many threads may be calling these functions simultaneously, 
and so you will need to use synchronization.

In process.c provide a function that simulates a process 
that can be used as the start routine of a pthread.

In driver.c, process commandline arguments, create threads, and keep the simulation 
running until there is only one process left.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "util.h"

int n_processes;
int n_resources;

int *sys_available;
int **held;
int **max;
int **need;
pthread_mutex_t lock;
pthread_t *tids;
extern void *run(void *arg);
extern int request_resources(int pid, int resources[]);
extern void release_resources(int pid, int resources[]);
void print_vector(int *a, int length);

void init(int argc, char *argv[])
{
    // ./bankers –n 2 -a 5 7 9
    if (argc < 5)
    {
        fprintf(stderr, "Input should follow: ./bankers –n <# of processes> -a <# of src 1> <# of src 2> <# of src 3>...\n");
        exit(1);
    }

    n_processes = atoi(argv[2]);

    if (n_processes < 0)
    {
        fprintf(stderr, "Number of processes should be be non-negative, while %d is given\n", n_processes);
        exit(1);
    }

    for (int i = 4; i < argc; i++)
    {
        if (atoi(argv[i]) < 0)
        {
            fprintf(stderr, "Number of a resource should be non-negative, while %d is given\n", atoi(argv[i]));
            exit(1);
        }
    }

    n_resources = argc - 4;
    printf("n_resources:%d\n", n_resources);

    // initialize the sys_available vector
    sys_available = (int *)malloc(sizeof(int) * n_resources);
    for (int i = 0; i < n_resources; i++)
    {
        printf("%d\t", atoi(argv[i + 4]));
        sys_available[i] = atoi(argv[i + 4]);
    }
    printf("\nsys_available:\n");
    print_vector(sys_available, n_resources);

    tids = (pthread_t *)malloc(sizeof(pthread_t) * n_processes);

    // initialize the held matrix
    held = (int **)malloc(sizeof(int *) * n_processes);
    for (int i = 0; i < n_processes; i++)
    {
        held[i] = (int *)malloc(sizeof(int) * n_resources);
        for (int j = 0; j < n_resources; j++)
        {
            held[i][j] = 0;
        }
    }

    // initialize the max matrix
    max = (int **)malloc(sizeof(int *) * n_processes);
    for (int i = 0; i < n_processes; i++)
    {
        max[i] = (int *)malloc(sizeof(int) * n_resources);
        for (int j = 0; j < n_resources; j++)
        {
            srand(time(NULL));
            int num = random_in_range(16, 32);
            while (num > sys_available[j])
            {
                num = random_in_range(16, 32);
            }
            max[i][j] = num;
        }
    }

    need = (int **)malloc(sizeof(int *) * n_processes);
    for (int i = 0; i < n_processes; i++)
    {
        need[i] = (int *)malloc(sizeof(int) * n_resources);
        for (int j = 0; j < n_resources; j++)
            need[i][j] = max[i][j] - held[i][j];
    }
}

void print_vector(int *a, int length)
{
    printf("xxhh");

    for (int i = 0; i < length; i++)
    {
        printf("%d", a[i]);
    }
}
void print_matrix(int **m, int p, int r)
{
    int i;
    int j;

    for (i = 0; i < p; i++)
    {
        printf("row: %d:\n", i);
        for (j = 0; j < r; j++)
        {
            printf("%d", max[i][j]);
        }
    }
}
/*
In driver.c, process commandline arguments, create threads, and keep the simulation 
running until there is only one process left.
*/
int main(int argc, char *argv[])
{
    init(argc, argv);
    print_vector(sys_available, n_resources);
    return 0;

    for (int k = 0; k < n_processes; k++)
    {
        printf("I am going to create thread");
        pthread_create(&(tids[k]), NULL, run, &k);
    }

    /* now wait for the thread to exit */
    for (int i = 0; i < n_processes; i++)
        pthread_join(tids[i], 0);

    printf(ANSI_COLOR_YELLOW "Reached the end of the program!\n" ANSI_COLOR_RESET);
    pthread_mutex_destroy(&lock);

    return 0;
}
