#include "util.h"
int random_in_range(int nmax, int nmin)
{
    srand(time(NULL));
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