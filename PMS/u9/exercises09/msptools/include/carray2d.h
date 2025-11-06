#ifndef CARRAY2D_H
#define CARRAY2D_H
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct carray2d /* C-style two-dimensional array */
{
    size_t shape[2];
    double **val;
} carray2d_t;

carray2d_t *carray2d_alloc(const size_t shape[2]);
void carray2d_dealloc(carray2d_t *a);
carray2d_t *carray2d_from_file(const char *filename);
int carray2d_to_file(const char *filename, const carray2d_t *a);
int carray2d_reshape(carray2d_t *a, const size_t new_shape[2]);
void carray2d_fprint(FILE *stream, const carray2d_t *a);
void carray2d_print(const carray2d_t *a);

#endif