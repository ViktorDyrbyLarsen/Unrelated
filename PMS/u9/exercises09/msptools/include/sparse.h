#ifndef SPARSE_H
#define SPARSE_H
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct coo /* coordinate sparse format (COO) */
{
    size_t shape[2];
    size_t nnz;
    size_t capacity;
    size_t *rowidx;
    size_t *colidx;
    double *val;
} coo_t;

typedef struct csp /* compressed sparse format (CSC/CSR) */
{
    size_t shape[2];
    enum cstype csx;
    size_t *ptr;
    size_t *idx;
    double *val;
} csp_t;

coo_t *coo_alloc(const size_t shape[2], const size_t capacity);
void coo_dealloc(coo_t *sp);
coo_t *coo_from_file(const char *filename);
int coo_to_file(const char *filename, const coo_t *sp);
void coo_fprint(FILE *stream, const coo_t *sp);
void coo_print(const coo_t *sp);

csp_t *csp_alloc(const size_t shape[2], const size_t nnz, enum cstype csx);
void csp_dealloc(csp_t *sp);
csp_t *csp_from_coo(const coo_t *sp, enum cstype csx);
void csp_fprint(FILE *stream, const csp_t *sp);
void csp_print(const csp_t *sp);

#ifndef MM_MAX_TOKEN_LENGTH
#define MM_MAX_TOKEN_LENGTH 64
#endif

#ifndef MM_MAX_LINE_LENGTH
#define MM_MAX_LINE_LENGTH 1025
#endif

#endif