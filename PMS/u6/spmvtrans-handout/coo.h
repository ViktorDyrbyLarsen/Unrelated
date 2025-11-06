#ifndef COO_H
#define COO_H

#include <stdlib.h>

typedef struct coo /* coordinate sparse format (COO) */
{
    size_t shape[2];
    size_t nnz;
    size_t capacity;
    size_t *rowidx;
    size_t *colidx;
    double *val;
} coo_t;

#endif
