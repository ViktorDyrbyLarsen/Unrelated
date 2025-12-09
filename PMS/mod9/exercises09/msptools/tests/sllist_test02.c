#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void) {

  sllist_t *L = sllist_alloc(0); // Allocate empty list
  assert(L != NULL);
  
  sllist_print(L);
  for (size_t k = 0; k < 4; k++)
    if (sllist_insert(L,0,k + 1)!=MSP_SUCCESS) {
      fprintf(stderr,"Unexpected failure.\n");      
      return EXIT_FAILURE;
    }
  sllist_print(L);
  if (sllist_insert(L, 2, -1) != MSP_SUCCESS) {
      fprintf(stderr,"Unexpected failure.\n");      
      return EXIT_FAILURE;
  }
  sllist_print(L);
  snode_t * N = sllist_find(L, 2);
  assert(N != NULL); 
  if (sllist_insert_after(L, N, -2) != MSP_SUCCESS) {
      fprintf(stderr,"Unexpected failure.\n");      
      return EXIT_FAILURE;
  }
  sllist_print(L);
  
  sllist_dealloc(L);
  return EXIT_SUCCESS;
}
