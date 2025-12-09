#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void) {

  coo_t *a = coo_from_file("../data/MM1.txt");
  assert(a != NULL);
  coo_print(a);

  csp_t * b = csp_from_coo(a, CSC);
  assert(b != NULL);
  csp_print(b);
  
  csp_t * c = csp_from_coo(a, CSR);
  assert(c != NULL);
  csp_print(c);

  coo_dealloc(a);
  csp_dealloc(b);
  csp_dealloc(c);

  return EXIT_SUCCESS;
}