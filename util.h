#ifndef UTIL_H // to prevent multiple includes in the main file
#define UTIL_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define ANSI_COLOR_YELLOW  "\x1b[33m"

int random_in_range(int nmin, int nmax);
bool vector_compare(int *a, int *b, int len);
void vector_add(int *a, int *b, int len);
void vector_sub(int *a, int *b, int len);
void print_vector(int *a, int length);
void print_matrix(int **m, int p, int r);


#endif // UTIL_H
