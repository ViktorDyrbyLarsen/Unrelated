#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void) {

  array_t *a = array_alloc(0);
  assert(a != NULL);
  
  array_print(a);
  for (size_t k = 0; k < 10; k++)
    if (array_push_back(a, k + 0.5)==MSP_FAILURE) {
      fprintf(stderr,"Unexpected failure.\n");      
      return EXIT_FAILURE;
    }
  array_print(a);

  array_dealloc(a);
  return EXIT_SUCCESS;
}
