#include "array.h"
#include <stdio.h>
#include <math.h>

array_t *array_alloc(const size_t capacity)
/*
  Purpose:

    Allocates a dynamic array with a given capacity. The length is 
    initialized as zero, and the array elements are not initialized.

  Example:

    ```c
    array_t *a = array_alloc(50);
    if (a==NULL) exit(EXIT_FAILURE);    
    // .. do something with array ..
    array_dealloc(a);
    ```

  Arguments:
    capacity   array capacity

  Return value:
    A pointer to an array_t, or NULL if an error occurs.
*/
{
  array_t *a = malloc(sizeof(*a));
  if (a == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  a->capacity = (capacity > 0 ? capacity : 1); // Minimum capacity is 1
  a->len = 0;
  a->val = malloc((a->capacity) * sizeof(*(a->val)));
  if (a->val == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(a);
    return NULL;
  }
  return a;
}

array_t *array_zeros(const size_t length)
/*
  Purpose:

    Allocates a dynamic array with a given length. 
    The array elements are initialized as zero.

  Arguments:
    length    array length

  Return value:
    A pointer to an array_t, or NULL if an error occurs.

  See also: array_alloc, array_dealloc
*/
{
  array_t *a = array_alloc(length);
  if (!a)
    return NULL;
  a->len = length;
  for (size_t k = 0; k < length; k++)
    a->val[k] = 0.0;
  return a;
}

void array_dealloc(array_t *a)
/* Purpose: Deallocates an array_t. */
{
  if (a == NULL)
    return;
  free(a->val);
  free(a);
}

int array_resize(array_t *a, size_t new_capacity)
/* 
  Purpose:

    Resizes dynamic array. The length of the array is reduced if 
    the new capacity is smaller than the length, and otherwise 
    the length is unchanged.

  Arguments:
    new_capacity    capacity after resizing

  Return value:
    Returns MSP_SUCCESS if resizing is successful, MSP_MEM_ERR if 
    reallocation fails, and MSP_ILLEGAL_INPUT if the input is a 
    NULL pointer.

  See also: array_alloc, array_dealloc

*/
{
  if (!a)
    return MSP_ILLEGAL_INPUT; // Received null pointer
  double *tmp = realloc(a->val, new_capacity * sizeof(double));
  if (!tmp)
    return MSP_MEM_ERR; // Reallocation failed
  a->val = tmp;
  a->capacity = new_capacity;
  a->len = (a->len <= new_capacity) ? a->len : new_capacity;
  return MSP_SUCCESS; // Reallocation successful
}

int array_push_back(array_t *a, double x)
/*
  Purpose:

    Appends an element to an array and, if necessary, increases the capacity
    by a factor of two.

  Example:

    ```c
    array_t *a = array_alloc(50);
    if (a==NULL) exit(EXIT_FAILURE);    
    for (size_t k=0;k<500;k++) array_push_back(a, 2.0*k);
    // .. do something with array ..
    array_dealloc(a);    
    ```

  Arguments:
    arr        a pointer to an array_t
    value      the value to be appended

  Return value:
    MSP_SUCCESS if successful, MSP_FAILURE if an error occurs, 
    and MSP_ILLEGAL_INPUT if the input is a NULL pointer.
*/
{
  if (!a)
    return MSP_ILLEGAL_INPUT;
  if (a->capacity <= a->len)
  {
    int ret = array_resize(a, 2 * (a->capacity));
    if (ret != MSP_SUCCESS)
      return ret;
  }
  a->val[a->len++] = x;
  return MSP_SUCCESS;
}

int array_cmp(const array_t *a, const array_t *ref, size_t *idx, double reltol, double abstol)
/*
  Purpose:

    Checks if two arrays are almost equal numerically in a relative 
    and/or absolute sense. The arrays must have the same length but 
    may have different strides. 
    
  Arguments:
    a            array
    ref          reference
    idx          pointer to size_t or NULL

  Return value:
    0 if the arrays are almost equal and otherwise a nonzero value.
*/
{
  if (a == NULL)
    return -1;
  if (ref == NULL)
    return -2;
  if (!isfinite(reltol))
    return -3;
  if (a->len != ref->len)
    return MSP_DIM_ERR;
  double absdiff, absref;
  for (size_t k = 0; k < ref->len; k++)
  {
    absdiff = fabs(a->val[k] - ref->val[k]);
    absref = fabs(ref->val[k]);
    if ((isnormal(absref) && absdiff > reltol * absref) ||
        (absref == 0 && absdiff > abstol) || isnan(absdiff))
    {
      if (idx != NULL)
        *idx = k;
      return MSP_FAILURE;
    }
  }
  return MSP_SUCCESS;
}

array_t *array_from_file(const char *filename)
/*
  Purpose:

    Reads an array from a text file.

  Arguments:
    filename   string with filename

  Return value:
    A pointer to an array_t, or NULL if an error occurs.
*/
{
  double v;
  /* Open file and read dimensions */
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
#ifndef NDEBUG
    FILE_ERR(filename);
#endif
    return NULL;
  }
  // Allocate array_t
  array_t *arr = array_alloc(256);
  if (arr == NULL)
  {
    fclose(fp);
    return NULL;
  }
  arr->len = 0;
  /* Read array from file */
  while (fscanf(fp, "%lf", &v) == 1)
  {
    if (array_push_back(arr, v) == MSP_MEM_ERR)
    {
#ifndef NDEBUG
      fprintf(stderr, "%s: failed to append value to buffer\n", __func__);
#endif
    }
  }
  fclose(fp);
  return arr;
}

int array_to_file(const char *filename, const array_t *arr)
/*
  Purpose:

    Writes an array_t to a text file.

  Arguments:
    filename   string with filename
    arr        pointer to array_t

  Return value:
    MSP_SUCCESS if successful, and MSP_FILE_ERR if a file error occurs.
*/
{
  /* Check that pv is not NULL */
  if (arr == NULL)
  {
#ifndef NDEBUG
    INPUT_ERR;
#endif
    return MSP_ILLEGAL_INPUT;
  }
  /* Open file for writing */
  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
  {
#ifndef NDEBUG
    FILE_ERR(filename);
#endif
    return MSP_FILE_ERR;
  }
  /* Write array to file */
  for (size_t i = 0; i < arr->len; i++)
    fprintf(fp, "%.17g\n", arr->val[i]);
  fclose(fp);
  return MSP_SUCCESS;
}

void array_fprint(FILE *stream, const array_t *a)
/*
  Purpose:

    Prints an array_t.

  Arguments:
    stream       a pointer to a file stream
    a            a pointer to an array_t

  Return value:
    None
*/
{
  if (a == NULL)
    return;
  size_t len = a->len;
  fprintf(stream, "<array_t len=%zu capacity=%zu>\n", len, a->capacity);
  for (size_t i = 0; i < len; i++)
  {
    fprintf(stream, " % .3g\n", a->val[i]);
  }
  return;
}

void array_print(const array_t *a) { array_fprint(stdout, a); }
