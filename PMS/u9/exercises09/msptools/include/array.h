#ifndef ARRAY_H
#define ARRAY_H
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct array /* dynamic array */
{
    size_t len;
    size_t capacity;
    double *val;
} array_t;

array_t *array_alloc(const size_t capacity);
array_t *array_zeros(const size_t length);
void array_dealloc(array_t *a);
int array_resize(array_t *a, size_t new_capacity);
int array_push_back(array_t *a, double value);
int array_cmp(const array_t *a, const array_t *ref, size_t *idx, double reltol, double abstol);
array_t *array_from_file(const char *filename);
int array_to_file(const char *filename, const array_t *a);
void array_fprint(FILE *stream, const array_t *a);
void array_print(const array_t *a);

#endif