#ifndef CARRAY2D_H
#define CARRAY2D_H
#include <stdlib.h>

typedef struct carray2d /* C-style two-dimensional array */
{
    size_t shape[2];
    double **val;
} carray2d_t;

#endif