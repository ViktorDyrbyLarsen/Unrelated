#ifndef MY_DGEMV_V1_H
#define MY_DGEMV_V1_H

#include <stdlib.h>

typedef struct array /* dynamic array */
{
    size_t len;
    size_t capacity;
    double *val;
} array_t;

enum storage_order
{
    RowMajor,
    ColMajor
};

typedef struct array2d /* two-dimensional array */
{
    size_t shape[2];
    enum storage_order order;
    double *val;
} array2d_t;

int my_dgemv_v1(
    double alpha,
    double beta,
    const array2d_t *A,
    const array_t *x,
    array_t *y);

#endif
