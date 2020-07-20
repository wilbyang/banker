#include <stdio.h>
#include "util.h"
int random_in_range(int nmin, int nmax)
{

    int x = nmin + rand() % (nmax - nmin + 1);
    return x;
}
/**
 * If vector a >= vector b, return True
 * 
 */
bool vector_compare(int *a, int *b, int len)
{
    int i = 0;
    while (i < len)
    {
        if (*(a + i) < *(b + i))
        {
            return false;
        }

        i++;
    }
    return true;
}

void vector_add(int *a, int *b, int len) 
{
    int i = 0;
    while (i < len)
    {
        *(a + i) += *(b + i);
        i++;
    }
}

void vector_sub(int *a, int *b, int len)
{
    int i = 0;
    while (i < len)
    {
        *(a + i) -= *(b + i);
        i++;
    }
}

void print_vector(int *a, int length)
{
    for (int i = 0; i < length; i++)
    {

        printf("%d\t", a[i]);
    }
    printf("\n");
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
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}