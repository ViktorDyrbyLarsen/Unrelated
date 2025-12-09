#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void)
{

  double x;
  array_t *a = array_alloc(8); // Allocate dynamic array with capacity 8
  assert(a != NULL);

  printf("Enter a sequence of numbers (enter any character to stop): \n");
  while (scanf("%lf", &x) == 1)
    array_push_back(a, x); // Append x to dynamic array

  if (a->len == 0)
    printf("You did not enter any numbers.\n");
  else
  {
    printf("You entered the following numbers: \n");
    for (size_t k = 0; k < a->len; k++)
      printf("  %g\n", a->val[k]);
  }
  array_dealloc(a);
  return EXIT_SUCCESS;
}
