#ifndef ARRAY2D_H
#define ARRAY2D_H
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct array2d /* two-dimensional array */
{
    size_t shape[2];
    enum storage_order order;
    double *val;
} array2d_t;

array2d_t *array2d_alloc(const size_t shape[2], enum storage_order order);
void array2d_dealloc(array2d_t *a);
array2d_t *array2d_from_file(const char *filename);
int array2d_to_file(const char *filename, const array2d_t *a);
int array2d_reshape(array2d_t *a, const size_t new_shape[2]);
void array2d_fprint(FILE *stream, const array2d_t *a);
void array2d_print(const array2d_t *a);

#endif