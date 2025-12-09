#include "carray2d.h"
#include "array2d.h"
#include <stdio.h>
#include <string.h>

carray2d_t *carray2d_alloc(const size_t shape[2])
/*
  Purpose:

    Allocates a C-style two-dimensional array (row-major storage) with 
    shape[0] rows and shape[1] columns. The elements or the array are not 
    initizlized. An Iliffe vector is used to store pointers to the rows 
    of the array.

  Example:

    ```c
    cmatrix_t * mat = carray2d_alloc((size_t []){4,3});
    if (mat==NULL) exit(EXIT_FAILURE);
    for (size_t i=0;i++;i<3*4) mat->val[0][k] = 1.0+k;
    mat->val[0][0] = 1.0; // Element in first row/col
    mat->val[3][2] = 5.0; // Element in last row/col
    // .. do something with cmatrix ..
    carray2d_dealloc(mat);
    ```

  Arguments:
    shape      array of length 2 (number of rows and columns)

  Return value:
    A pointer to a cmatrix_t, or NULL if an error occurs.
*/
{
  // Allocate struct
  carray2d_t *a = malloc(sizeof(*a));
  if (a == NULL) {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  a->shape[0] = shape[0];
  a->shape[1] = shape[1];
  // Allocate pointer array
  a->val = malloc(shape[0] * sizeof(*(a->val)));
  if (a->val == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(a);
    return NULL;
  }
  // Allocate storage for values and set row pointers
  a->val[0] = calloc(shape[0] * shape[1], sizeof(*(a->val[0])));
  if (a->val[0] == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(a->val);
    free(a);
    return NULL;
  }
  for (size_t k = 1; k < shape[0]; k++)
    a->val[k] = a->val[0] + k*shape[1];
  return a;
}

void carray2d_dealloc(carray2d_t *a)
// Purpose: Deallocates a cmatrix_t.
{
  if (a) {
    free(a->val[0]);
    free(a->val);
    free(a);
  }
}

carray2d_t *carray2d_from_file(const char *filename)
/*
  Purpose:

    Reads a two-dimensional array from a text file.

  Arguments:
    filename   string with filename

  Return value:
    A pointer to an carray2d_t, or NULL if an error occurs.
*/
{
  array2d_t *tmp = array2d_from_file(filename);
  if (!tmp)
    return NULL;
  carray2d_t *a = carray2d_alloc(tmp->shape);
  if (!a)
    return NULL;
  memcpy(a->val[0], tmp->val, tmp->shape[0] * tmp->shape[1] * sizeof(*(a->val[0])));
  array2d_dealloc(tmp);
  return a;
}

int carray2d_to_file(const char *filename, const carray2d_t *a)
/*
  Purpose:

    Writes a two-dimensional array to a text file.

  Arguments:
    filename   string with filename
    a          pointer to carray2d_t

  Return value:
    MSP_SUCCESS if successful, and MSP_FILE_ERR if a file error occurs.
*/
{
  array2d_t tmp;
  tmp.shape[0] = a->shape[0];
  tmp.shape[1] = a->shape[1];
  tmp.val = a->val[0];
  return array2d_to_file(filename, &tmp);
}

int carray2d_reshape(carray2d_t *a, const size_t new_shape[2])
/*
  Purpose:

    Reshapes a two-dimensional array. The new shape must be
    compatible with the number of elements in the array.

  Example:

    ```c
    carray2d_t *a = array2d_alloc((size_t []){24,1});
    if (a==NULL) exit(EXIT_FAILURE);
    // .. do someting with array ..
    carray2d_reshape(a, (size_t []){4,6});
    // .. do something with array ..
    carray2d_dealloc(a);
    ```

  Arguments:
    a            a pointer to a two-dimensional array
    new_shape    new shape 

  Return value:
    MSP_SUCCESS if successful, and MSP_DIM_ERR or MSP_FAILURE if an error occurs.
*/
{
  if (a == NULL) {
#ifndef NDEBUG
    INPUT_ERR;
#endif
    return MSP_ILLEGAL_INPUT;
  }
  if (new_shape[0] * new_shape[1] != a->shape[0] * a->shape[1])
      return MSP_DIM_ERR;
  if (new_shape[0] > a->shape[0]) {
    /* Increase length of pointer array */
    double ** tmp = realloc(a->val, new_shape[0]*sizeof(*a->val));
    if (!tmp) return MSP_FAILURE;
    a->val = tmp;
  }
  for (size_t k=1;k<new_shape[0];k++) 
    a->val[k] = a->val[0] + k*new_shape[1];
  a->shape[0] = new_shape[0];
  a->shape[1] = new_shape[1];
  return MSP_SUCCESS;
}

void carray2d_fprint(FILE *stream, const carray2d_t *a)
/*
  Purpose:

    Prints an two-dimensional array.

  Arguments:
    stream       a pointer to a file stream
    a            a pointer to an carray2d_t

  Return value:
    None
*/
{
  {

    if (a == NULL)
      return;

    /* Print array header */
    fprintf(stream, "<carray2d_t shape=(%zu,%zu)>\n", a->shape[0], a->shape[1]);

    /* Print entries  */
    size_t m = a->shape[0];
    size_t n = a->shape[1];
    for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        fprintf(stream, "% 8.3g ", a->val[i][j]);
      }
      fprintf(stream, "\n");
    }
    return;
  }
}

void carray2d_print(const carray2d_t *a) { carray2d_fprint(stdout, a); }
