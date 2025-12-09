#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void) {

  array2d_t * a = array2d_from_file("../data/A1.txt");
  assert(a!=NULL);
  array2d_print(a);
  array2d_dealloc(a);
  
  a = array2d_from_file("../data/v1.txt");
  assert(a != NULL);
  array2d_print(a);
  array2d_dealloc(a);

  return 0;

}
