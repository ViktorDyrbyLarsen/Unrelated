#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void)
{

  ndarray_t *a = ndarray_alloc(3, (size_t[]){3, 4, 2}, RowMajor);
  assert(a != NULL);

  size_t n = ndarray_nelem(a);
  for (size_t k = 0; k < n; k++)
    a->val[k] = k + 1;

  ndarray_print(a);
  if (ndarray_reshape(a, 2, (size_t[]){4, 6}) != MSP_SUCCESS) {
    fprintf(stderr, "%s: failed to reshape\n", __FILE__);
    return EXIT_FAILURE;
  }
  ndarray_print(a);
  if (ndarray_reshape(a, 3, (size_t[]){3, 2, 4}) != MSP_SUCCESS) {
    fprintf(stderr, "%s: failed to reshape\n", __FILE__);
    return EXIT_FAILURE;
  }
  ndarray_print(a);
  if (ndarray_reshape(a, 1, (size_t[]){24}) != MSP_SUCCESS){
    fprintf(stderr, "%s: failed to reshape\n", __FILE__);
    return EXIT_FAILURE;
  }
  ndarray_print(a);
  if (ndarray_reshape(a, 3, (size_t[]){1, 2, 12}) != MSP_SUCCESS){
    fprintf(stderr, "%s: failed to reshape\n", __FILE__);
    return EXIT_FAILURE;
  }
  ndarray_print(a);
  if (ndarray_reshape(a, 2, (size_t[]){2, 12}) != MSP_SUCCESS){
    fprintf(stderr, "%s: failed to reshape\n", __FILE__);
    return EXIT_FAILURE;
  }
  ndarray_print(a);
  if (ndarray_reshape(a, 2, (size_t[]){1, 5}) != MSP_DIM_ERR) {
    fprintf(stderr, "%s line %d: expected failure\n", __FILE__, __LINE__);
    return EXIT_FAILURE;
  }
  ndarray_dealloc(a);

  return EXIT_SUCCESS;
}
