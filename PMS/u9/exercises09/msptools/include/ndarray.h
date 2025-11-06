#ifndef NDARRAY_H
#define NDARRAY_H
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct ndarray /* n-dimensional array */
{
    size_t ndim;
    size_t *shape;
    size_t *strides;
    enum storage_order order;
    double *val;
} ndarray_t;

typedef struct ndindex /* multi-index for n-dimensional array */
{
    size_t ndim;
    size_t *idx;
} ndindex_t;

ndarray_t *ndarray_alloc(const size_t ndim, const size_t *shape, const enum storage_order order);
void ndarray_dealloc(ndarray_t *a);
int ndarray_reshape(ndarray_t *a, const size_t new_ndim, const size_t *new_shape);
int ndarray_iscontiguous(ndarray_t *a);
size_t ndarray_nelem(const ndarray_t *a);
double *ndarray_entry(const ndarray_t *a, const ndindex_t *i);
int ndarray_cmp(const ndarray_t *a, const ndarray_t *ref, ndindex_t *ie, double reltol, double abstol);
void ndarray_fprint(FILE *stream, const ndarray_t *a);
void ndarray_print(const ndarray_t *a);

ndindex_t *ndindex_alloc(const size_t ndim);
void ndindex_dealloc(ndindex_t *idx);
void ndindex_incr(ndindex_t *i, size_t *shape, enum storage_order order);
void ndindex_fprint(FILE *stream, const ndindex_t *i);
void ndindex_print(const ndindex_t *i);

#endif