#include "array2d.h"
#include "array.h"
#include <stdio.h>
#include <string.h>

array2d_t *array2d_alloc(const size_t shape[2], enum storage_order order)
/*
  Purpose:

    Allocates a two-dimensional array with a given shape. The array 
    elements are initialized as zero.

  Example:

    ```c
    array2d_t *a = array2d_alloc(size_t nrows, size_t ncols, RowMajor);
    if (a==NULL) exit(EXIT_FAILURE);    
    // .. do something with array ..
    array2d_dealloc(a);
    ```

  Arguments:
    shape        array of length 2 (number of rows and columns)
    order        RowMajor or ColMajor

  Return value:
    A pointer to an array2d_t, or NULL if an error occurs.
*/
{
  array2d_t *a = malloc(sizeof(*a));
  if (a == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  a->shape[0] = shape[0];
  a->shape[1] = shape[1];
  a->order = order;
  a->val = calloc(shape[0] * shape[1], sizeof(*(a->val)));
  if (a->val == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(a);
    a = NULL;
  }
  return a;
}

void array2d_dealloc(array2d_t *a)
/* Purpose: Deallocates an array2d_t. */
{
  if (a)
  {
    free(a->val);
    free(a);
  }
}

array2d_t *array2d_from_file(const char *filename)
/*
  Purpose:

    Reads a two-dimensional array from a text file.

  Arguments:
    filename   string with filename

  Return value:
    A pointer to an array2d_t, or NULL if an error occurs.
*/
{

  array2d_t *arr = NULL;
  char *buf = NULL, *line, *tok, delim[] = " \n";
  size_t colcnt = 0, sz_buf = 0, nrows = 0, ncols = 0;

  /* Open file and find size */
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
#ifndef NDEBUG
    FILE_ERR(filename);
#endif
    return NULL;
  }
  fseek(fp, 0L, SEEK_END);
  sz_buf = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  /* Allocate char buffer */
  buf = malloc(sz_buf);
  if (buf == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    fclose(fp);
    return NULL;
  }

  /* Allocate array_t */
  array_t *data = array_alloc(256);
  if (data == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(buf);
    fclose(fp);
    return NULL;
  }
  data->len = 0;

  /* Parse file */
  while ((line = fgets(buf, sz_buf, fp)))
  {
    tok = strtok(line, delim);
    colcnt = 0;
    while (tok)
    {
      colcnt += 1;
      if (array_push_back(data, atof(tok)) == MSP_MEM_ERR)
        fprintf(stderr, "%s: failed to append value to buffer\n", __func__);
      tok = strtok(NULL, delim);
    }
    if (colcnt == 0)
      break; // Empty line: skip the rest
    nrows += 1;
    if (ncols == 0)
      ncols = colcnt;
    else if (ncols != colcnt && colcnt > 0)
    {
      printf("Error: different column counts encountered.\n");
      free(buf);
      fclose(fp);
      array_dealloc(data);
      return NULL;
    }
  }
  /* Free char buffer and close file */
  free(buf);
  fclose(fp);

  /* Allocate two-dimensional array and copy data */
  arr = array2d_alloc((size_t[]){nrows, ncols}, RowMajor);
  if (arr == NULL)
  {
    array_dealloc(data);
    return NULL;
  }
  memcpy(arr->val, data->val, nrows * ncols * sizeof(*arr->val));
  array_dealloc(data);
  return arr;
}

int array2d_to_file(const char *filename, const array2d_t *a)
/*
  Purpose:

    Writes a two-dimensional array to a text file.

  Arguments:
    filename   string with filename
    a          pointer to array2d_t

  Return value:
    MSP_SUCCESS if successful, and MSP_FILE_ERR if a file error occurs.
*/
{
  if (a == NULL)
  {
#ifndef NDEBUG
    INPUT_ERR;
#endif
    return MSP_ILLEGAL_INPUT;
  }
  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
  {
#ifndef NDEBUG
    FILE_ERR(filename);
#endif
    return MSP_FILE_ERR;
  }
  size_t m = a->shape[0];
  size_t n = a->shape[1];
  size_t st0 = (a->order == RowMajor) ? a->shape[1] : 1;
  size_t st1 = (a->order == RowMajor) ? 1 : a->shape[0];
  for (size_t i = 0; i < m; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      fprintf(fp, "%.17g ", a->val[i * st0 + j * st1]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return MSP_SUCCESS;
}

int array2d_reshape(array2d_t *a, const size_t new_shape[2])
/*
  Purpose:

    Reshapes a two-dimensional array. The new shape must be
    compatible with the number of elements in the array.

  Example:

    ```c
    array2d_t *a = array2d_alloc((size_t []){24,1},RowMajor);
    if (a==NULL) exit(EXIT_FAILURE);
    // .. do someting with array ..
    array2d_reshape(a, (size_t []){4,6});
    // .. do something with array ..
    array2d_dealloc(a);
    ```

  Arguments:
    a            a pointer to a two-dimensional array
    new_shape    new shape 

  Return value:
    MSP_SUCCESS if successful, and MSP_DIM_ERR or MSP_FAILURE if an error occurs.
*/
{
  if (a == NULL)
    return MSP_ILLEGAL_INPUT;
  if (new_shape[0] * new_shape[1] != a->shape[0] * a->shape[1])
    return MSP_DIM_ERR;
  a->shape[0] = new_shape[0];
  a->shape[1] = new_shape[1];
  return MSP_SUCCESS;
}

void array2d_fprint(FILE *stream, const array2d_t *a)
/*
  Purpose:

    Prints an two-dimensional array.

  Arguments:
    stream       a pointer to a file stream
    a            a pointer to an array2d_t

  Return value:
    None
*/
{
  {

    if (a == NULL)
      return;

    /* Print array header */
    fprintf(stream, "<array2d_t shape=(%zu,%zu) order=%s>\n", a->shape[0], a->shape[1], a->order == RowMajor ? "RowMajor" : "ColMajor");

    /* Print routine for one- and two-dimensional arrays */
    size_t m = a->shape[0];
    size_t n = a->shape[1];
    size_t st0 = (a->order == RowMajor) ? a->shape[1] : 1;
    size_t st1 = (a->order == RowMajor) ? 1 : a->shape[0];
    for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        fprintf(stream, "% 8.3g ", a->val[i * st0 + j * st1]);
      }
      fprintf(stream, "\n");
    }
    return;
  }
}

void array2d_print(const array2d_t *a) { array2d_fprint(stdout, a); }
