
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include "util.h"
extern int n_resources;
extern int request_resources(int pid, int resources[]);
extern void release_resources(int pid, int resources[]);


/**
 * Request some resources less than (max – held)
 * Sleep a random amount
 * Release subset of held resources
 * Sleep a random amount
 * @param arg
 * @return
 */
void *run(void *arg)
{
    int process_identifier = *(int *)arg;
    printf("I am running, pid is %d\n", process_identifier);
    int *requests = (int *)malloc(sizeof(int) * n_resources);
    for (int j = 0; j < n_resources; j++)
    {
        requests[j] = random_in_range(2, 9);
    }
    while (true)
    {
        int ret = request_resources(process_identifier, requests);
        sleep(random_in_range(1, 3));
        if (ret == 0)
            break;
    }

    release_resources(process_identifier, requests);
    sleep(random_in_range(1, 3));
    pthread_exit(NULL);
}