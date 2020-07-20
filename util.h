#ifndef UTIL_H // to prevent multiple includes in the main file
#define UTIL_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int random_in_range(int nmin, int nmax);
bool vector_compare(int *a, int *b, int len);
void vector_add(int *a, int *b, int len);
void vector_sub(int *a, int *b, int len);
void print_vector(int *a, int length);
void print_matrix(int **m, int p, int r);


#endif // UTIL_H
