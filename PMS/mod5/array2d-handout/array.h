#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>

typedef struct array
{
    size_t len;      // length of array
    size_t capacity; // allocated storage
    double *val;     // pointer to first element
} array_t;

#endif