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

int *a;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t *tids;
extern void *run(void *arg);
extern int request_resources(int pid, int resources[]);
extern void release_resources(int pid, int resources[]);

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

        sys_available[i] = atoi(argv[i + 4]);
        printf("%d\t", sys_available[i]);
    }


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
            int num = random_in_range(6, 16);
            while (num > sys_available[j])
            {
                num = random_in_range(6, 16);
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



void print_status()
{
    printf("\nsys_available:\n");

    print_vector(sys_available, n_resources);

    printf("\nmax:\n");
    print_matrix(max, n_processes, n_resources);
    printf("\nheld:\n");
    print_matrix(held, n_processes, n_resources);
    printf("\nneed:\n");
    print_matrix(need, n_processes, n_resources);
}

int main(int argc, char *argv[])
{
    init(argc, argv);
    print_status();
    int *thread_ids = (int *)malloc(sizeof(int) * n_processes);
    for (int k = 0; k < n_processes; k++)
    {
        thread_ids[k] = k;
    }
    for (int k = 0; k < n_processes; k++)
    {

        pthread_create(&(tids[k]), NULL, run, &thread_ids[k]);
        printf("I created thread %d\n", k);
    }

    /* now wait for the thread to exit */
    for (int i = 0; i < n_processes; i++)
        pthread_join(tids[i], NULL);

    printf(ANSI_COLOR_YELLOW "Reached the end of the program!\n");
    pthread_mutex_destroy(&lock);

    return 0;
}
