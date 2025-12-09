#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void) {

  carray2d_t *a = carray2d_alloc((size_t []){3,8});
  assert(a != NULL);
  
  for (size_t k = 0; k < 24; k++) a->val[0][k] = k+1;
  carray2d_print(a);
  if (carray2d_reshape(a, (size_t []){4,4})!=MSP_DIM_ERR)
    {
    fprintf(stderr,"Unexpected failure.\n");      
    return EXIT_FAILURE;
  }
  if (carray2d_reshape(a, (size_t []){4,6})!=MSP_SUCCESS)
    {
    fprintf(stderr,"Unexpected failure.\n");      
    return EXIT_FAILURE;
  }
  carray2d_print(a);

  carray2d_dealloc(a);
  return EXIT_SUCCESS;
}
