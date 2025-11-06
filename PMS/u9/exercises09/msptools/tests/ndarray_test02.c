#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void)
{

    ndindex_t *i = ndindex_alloc(4);
    ndarray_t *a = ndarray_alloc(4, (size_t[]){3, 4, 2, 3}, ColMajor);
    ndarray_t *b = ndarray_alloc(4, (size_t[]){3, 4, 2, 3}, ColMajor);

    assert(a != NULL);
    assert(b != NULL);
    assert(i != NULL);

    size_t n = ndarray_nelem(a);
    for (size_t k = 0; k < n; k++)
    {
        *ndarray_entry(a, i) = k;
        *ndarray_entry(b, i) = k + 1e-7;
        ndindex_incr(i, a->shape, ColMajor);
    }
    if (ndarray_cmp(b, a, i, 1e-6, 1e-6))
    {
        fprintf(stderr, "Unexpected failure.\n");
        ndindex_print(i);
        return EXIT_FAILURE;
    }
    if (!ndarray_cmp(b, a, i, 1e-10, 1e-10))
    {
        fprintf(stderr, "Unexpected failure.\n");
        ndindex_print(i);
        return EXIT_FAILURE;
    }

    ndarray_print(a);
    ndarray_reshape(a, 2, (size_t[]){12, 6});
    ndarray_print(a);

    ndarray_dealloc(a);
    ndarray_dealloc(b);
    ndindex_dealloc(i);

    return EXIT_SUCCESS;
}