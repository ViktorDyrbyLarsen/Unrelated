#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <stdlib.h>

enum storage_order { RowMajor, ColMajor };
typedef struct array2d /* two-dimensional array */
{
    size_t shape[2];
    enum storage_order order;
    double *val;
} array2d_t;

#endif
