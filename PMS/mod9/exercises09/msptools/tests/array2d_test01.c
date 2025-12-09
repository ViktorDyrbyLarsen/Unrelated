#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void)
{

  array2d_t *a = array2d_alloc((size_t[]){3, 8}, RowMajor);
  assert(a != NULL);

  for (size_t k = 0; k < 24; k++)
    a->val[k] = k + 1;
  array2d_print(a);
  if (array2d_reshape(a, (size_t[]){4, 4}) != MSP_DIM_ERR)
  {
    fprintf(stderr,"Unexpected failure.\n");
    return EXIT_FAILURE;
  }
  if (array2d_reshape(a, (size_t[]){4, 6}) != MSP_SUCCESS)
  {
    fprintf(stderr,"Unexpected failure.\n");      
    return EXIT_FAILURE;
  }
  array2d_print(a);

  array2d_dealloc(a);
  return 0;
}
