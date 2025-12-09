#include "ndarray.h"
#include <stdio.h>
#include <math.h>

ndarray_t *ndarray_alloc(
    const size_t ndim,             // Number of dimensions
    const size_t *shape,           // Shape of array (pointer to array of length ndim)
    const enum storage_order order // RowMajor or ColMajor
)
/*
  Purpose:

    Allocates an n-dimensional array of a given size using row-major 
    or column-major storage order. The elements of the array are  
    initialized with the value zero.

  Example:

    ```c
    ndarray_t * a = ndarray_alloc(3,(size_t []){3,2,4}, RowMajor);
    if (a==NULL) exit(EXIT_FAILURE);
    size_t n = ndarray_nelem(a);  // compute number of elements
    for (size_t k=0;k<n;k++) a->val[k] = 0.0;  // initialize array
    // .. do something with array ..
    ndarray_dealloc(a);
    ```

  Arguments:
    ndim       number of dimensions
    shape      pointer to array of length ndim
    order      RowMajor or ColMajor

  Return value:
    A pointer to an ndarray_t, or NULL if an error occurs.
*/
{
  size_t nelem = 1;
  for (size_t k = 0; k < ndim; k++)
    nelem *= shape[k];
  ndarray_t *arr = malloc(sizeof(*arr));
  if (arr == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  arr->order = order;
  arr->ndim = ndim;
  arr->shape = malloc(2 * ndim * sizeof(*(arr->shape)));
  if (arr->shape == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(arr);
    return NULL;
  }
  for (size_t k = 0; k < ndim; k++)
    arr->shape[k] = shape[k];
  arr->strides = arr->shape + ndim;
  if (order == RowMajor)
  {
    // Default strides for row major array
    arr->strides[ndim - 1] = 1;
    for (size_t k = 1; k < ndim; k++)
      arr->strides[ndim - 1 - k] =
          arr->strides[ndim - k] * arr->shape[ndim - k];
  }
  else
  {
    // Default strides for column major array
    arr->strides[0] = 1;
    for (size_t k = 1; k < ndim; k++)
      arr->strides[k] = arr->strides[k - 1] * arr->shape[k - 1];
  }
  arr->val = calloc(nelem, sizeof(*(arr->val)));
  if (arr->val == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(arr->shape);
    free(arr);
  }
  return arr;
}

void ndarray_dealloc(ndarray_t *arr)
// Purpose: Deallocates an ndarray_t.
{
  if (arr == NULL)
    return;
  free(arr->val);
  free(arr->shape);
  free(arr);
}

ndindex_t *ndindex_alloc(const size_t ndim)
/*
  Purpose:

    Allocates and initializes an n-dimensional index. 

  Example:

    ```c
    ndarray_t *a = ndarray_alloc(3,(size_t []){2,4,3}, RowMajor)
    ndindex_t *i = ndindex_alloc(3);
    if (a==NULL && i==NULL ) exit(EXIT_FAILURE);
    *ndarray_entry(a,i) = 1.0; // set a(i) = 1.0 
    ndindex_incr(i, a->shape, RowMajor);  // increment i
    *ndarray_entry(a,i) = 2.0; // set a(i) = 2.0
    ndarray_dealloc(a);
    ndindex_dealloc(i);
    ```

  Arguments:
    ndim       number of dimensions
    shape      pointer to array of length ndim
    order      RowMajor or ColMajor

  Return value:
    A pointer to an ndarray_t, or NULL if an error occurs.
*/
{
  ndindex_t *i = malloc(sizeof(*i));
  if (i == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  i->ndim = ndim;
  i->idx = calloc(ndim, sizeof(*(i->idx)));
  if (i->idx == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    free(i);
    return NULL;
  }
  return i;
}
void ndindex_dealloc(ndindex_t *i)
// Purpose: Deallocates an ndindex_t.
{
  if (i == NULL)
    return;
  free(i->idx);
  free(i);
}

size_t ndarray_nelem(const ndarray_t *a)
/*
  Purpose:

    Computes the total number of elements in a multi-
    dimensional array.

  Arguments:
    a          a pointer to an ndarray_t

  Returns:
    Number of elements in the array.
*/
{
  if (a == NULL)
    return 0;
  size_t n = 1;
  for (size_t k = 0; k < a->ndim; k++)
    n *= a->shape[k];
  return n;
}

int ndarray_reshape(ndarray_t *a, const size_t new_ndim, const size_t *new_shape)
/*
  Purpose:

    Reshapes an n-dimensional array. The new shape must be
    compatible with the number of elements in the array, 
    and the input array must be contiguous.

  Example:

    ```c
    ndarray_t *a = ndarray_alloc(1,(size_t []){24},RowMajor);
    if (a==NULL) exit(EXIT_FAILURE);
    // .. do something with array ..
    ndarray_reshape(a, 3, (size_t []){2,3,4});
    // .. do something with array ..
    ndarray_dealloc(a);
    ```

  Arguments:
    a          a pointer to a multidimensional array
    new_dim    new dimension
    new_shape  new shape 

  Return value:
    MSP_SUCCESS if successful, and MSP_DIM_ERR, MSP_STRIDE_ERR, 
    or MSP_FAILURE if an error occurs.
*/
{
  // Compute number of elements for shape and new_shape
  size_t new_nelem = 1, nelem = 1;
  for (size_t k = 0; k < a->ndim; k++)
    nelem *= a->shape[k];
  for (size_t k = 0; k < new_ndim; k++)
    new_nelem *= new_shape[k];
  if (new_nelem != nelem)
    return MSP_DIM_ERR;

  // Check that array is contiguous
  if (!ndarray_iscontiguous(a))
    return MSP_STRIDE_ERR;

  // Allocate more memory for shape/strides array if new_ndim > ndim
  if (new_ndim > a->ndim)
  {
    // Allocate new array for shape/strides
    size_t *tmp = realloc(a->shape, 2 * new_ndim * sizeof(*a->shape));
    if (tmp == NULL)
      return MSP_FAILURE;
    a->shape = tmp;
    a->strides = tmp + new_ndim;
  }
  // Overwrite shape by new_shape and update strides
  a->ndim = new_ndim;
  for (size_t k = 0; k < new_ndim; k++)
  {
    a->shape[k] = new_shape[k];
  }
  if (a->order == RowMajor)
  {
    // Default strides for row major array
    a->strides[new_ndim - 1] = 1;
    for (size_t k = 1; k < new_ndim; k++)
      a->strides[new_ndim - 1 - k] =
          a->strides[new_ndim - k] * a->shape[new_ndim - k];
  }
  else
  {
    // Default strides for column major array
    a->strides[0] = 1;
    for (size_t k = 1; k < new_ndim; k++)
      a->strides[k] = a->strides[k - 1] * a->shape[k - 1];
  }
  return MSP_SUCCESS;
}

int ndarray_iscontiguous(ndarray_t *a)
/*
  Purpose:

    Checks if a multidimensional array is contiguous.
  
  Arguments:
    a           a pointer to an ndarray_t

  Returns:
    1 if the array is contiguous and 0 otherwise.
*/
{
  size_t s = 1, ndim = a->ndim;
  if (a->order == RowMajor)
  {
    for (size_t k = 0; k < ndim; k++)
    {
      if (a->strides[ndim - 1 - k] != s)
        return 0;
      s *= a->shape[ndim - 1 - k];
    }
  }
  else
  {
    for (size_t k = 0; k < ndim; k++)
    {
      if (a->strides[k] != s)
        return 0;
      s *= a->shape[k];
    }
  }
  return 1;
}

double *ndarray_entry(const ndarray_t *a, const ndindex_t *i)
/*
  Purpose: 

    Returns a pointer to the element a(i) where i is a multi-index.

  Arguments:
    arr          multi-dimensional array
    i            multi-index
      
  Return value:
    A pointer to a(i) or NULL if i is out of bounds.
*/
{
  if (a == NULL || i == NULL)
    return NULL;
  if (a->ndim != i->ndim)
    return NULL;
  size_t ndim = a->ndim;
  size_t *idx = i->idx;
  size_t *shape = a->shape;
  size_t *strides = a->strides;
  for (size_t k = 0; k < ndim; k++)
  {
    if (idx[k] < 0 || idx[k] >= shape[k])
      return NULL;
  }
  double *p = a->val;
  for (size_t k = 0; k < ndim; k++)
    p += strides[k] * idx[k];
  return p;
}

int ndarray_cmp(const ndarray_t *a, const ndarray_t *ref, ndindex_t *ie, double reltol, double abstol)
/*
  Purpose:

    Checks if two multidimensional darrays are almost equal numerically 
    in a relative and/or absolute sense. The arrays must have the same shape.

  Arguments:
    a            multi-dimensional array
    ref          reference
    ie           pointer to size_t or NULL
    reltol       a positive scalar

  Return value:
    0 if the arrays are almost equal and otherwise a nonzero value.
*/
{
  if (a == NULL || ref == NULL)
    return MSP_FAILURE;
  if (!isnormal(reltol))
    return ref == NULL;
  for (size_t k = 0; k < ref->ndim; k++)
  {
    if (a->shape[k] != ref->shape[k])
      return MSP_DIM_ERR;
    if (a->strides[k] != ref->strides[k])
      return MSP_STRIDE_ERR;
  }
  ndindex_t *i = ndindex_alloc(ref->ndim);
  if (i == NULL)
    return MSP_FAILURE;
  size_t nref = ndarray_nelem(ref);
  double *e, *eref, absdiff, absref;
  for (size_t k = 0; k < nref; k++)
  {
    e = ndarray_entry(a, i);
    eref = ndarray_entry(ref, i);
    absdiff = fabs(*e - *eref);
    absref = fabs(*eref);
    if ((isnormal(absref) && absdiff > reltol * absref) ||
        (absref == 0 && absdiff > abstol) || isnan(absdiff))
    {
      if (ie != NULL && ie->ndim == i->ndim)
      {
        for (size_t j = 0; j < i->ndim; j++)
          ie->idx[j] = i->idx[j];
      }
      return MSP_FAILURE;
    }
    ndindex_incr(i, ref->shape, RowMajor);
  }
  ndindex_dealloc(i);
  return MSP_SUCCESS;
}

void ndindex_incr(ndindex_t *i, size_t *shape, enum storage_order order)
/*
  Purpose:

    Increments a multi-index for an array of a given shape. 
    The index value wraps around if i corresponds to the last element
    in an array whose dimensions are determined by shape[0],..,shape[ndim-1].

  Example:

    ```c
    ndarray_t *a = alloc_ndarray(3,(size_t []){2,4,3}, RowMajor)
    ndindex_t *i = alloc_ndindex(3);
    if (a==NULL && i==NULL ) exit(EXIT_FAILURE);
    *ndarray_entry(a,i) = 1.0; // set a(i) = 1.0 
    ndindex_incr(i, a->shape, RowMajor);  // increment i
    *ndarray_entry(a,i) = 2.0; // set a(i) = 2.0
    dealloc_ndarray(a);
    dealloc_ndindex(i);
    ```

  Arguments:
    ndim       number of dimensions
    shape      pointer to array of length ndim
    order      RowMajor or ColMajor

  Return value:
    A pointer to an ndarray_t, or NULL if an error occurs.
*/
{
  size_t ndim = i->ndim;
  if (order == RowMajor)
  {
    // Row-major
    i->idx[ndim - 1] += 1;
    for (size_t k = 0; k < ndim; k++)
    {
      if (i->idx[ndim - 1 - k] >= shape[ndim - 1 - k])
      {
        i->idx[ndim - 1 - k] = 0;
        if (k < ndim - 1)
          i->idx[ndim - 2 - k] += 1;
      }
      else
        break;
    }
  }
  else
  {
    // Col-major
    i->idx[0] += 1;
    for (size_t k = 0; k < ndim; k++)
    {
      if (i->idx[k] >= shape[k])
      {
        i->idx[k] = 0;
        if (k < ndim - 1)
          i->idx[k + 1] += 1;
      }
      else
        break;
    }
  }
}

void ndarray_fprint(FILE *stream, const ndarray_t *a)
/*
  Purpose:

    Prints an multi-dimensional array.

  Arguments:
    stream       a pointer to a file stream
    a            a pointer to an ndarray_t

  Return value:
    None
*/
{

  if (a == NULL)
    return;

  /* Print array header */
  fprintf(stream, "<ndarray_t shape=(%zu", a->shape[0]);
  for (size_t k = 1; k < a->ndim; k++)
    fprintf(stream, ",%zu", a->shape[k]);
  fprintf(stream, ") order=%s>\n", a->order == RowMajor ? "RowMajor" : "ColMajor");

  if (a->ndim <= 2)
  {
    /* Print routine for one- and two-dimensional arrays */
    size_t m = a->shape[0];
    size_t n = (a->ndim == 2) ? a->shape[1] : 1;
    size_t st0 = a->strides[0];
    size_t st1 = (a->ndim == 2) ? a->strides[1] : 0;
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
  else if (a->ndim > 2)
  {
    ndindex_t *mi = ndindex_alloc(a->ndim);
    if (!mi)
      return;
    size_t m = a->shape[0];
    size_t n = a->shape[1];
    size_t st0 = a->strides[0];
    size_t st1 = a->strides[1];

    size_t slices = ndarray_nelem(a) / (m * n);
    for (size_t k = 0; k < slices; k++)
    {
      fprintf(stream, "slice(:,:");
      for (size_t s = 2; s < a->ndim; s++)
      {
        fprintf(stream, ",%zu", mi->idx[s]);
      }
      fprintf(stream, ") = \n");
      for (size_t i = 0; i < m; i++)
      {
        double *pval = ndarray_entry(a, mi);
        for (size_t j = 0; j < n; j++)
        {
          fprintf(stream, "% 8.3g ", pval[i * st0 + j * st1]);
        }
        fprintf(stream, "\n");
      }
      if (a->order == ColMajor)
      {
        mi->idx[0] = m - 1;
        mi->idx[1] = n - 1;
      }
      ndindex_incr(mi, a->shape, a->order);
    }
    ndindex_dealloc(mi);
  }
}

void ndarray_print(const ndarray_t *arr) { ndarray_fprint(stdout, arr); }

void ndindex_fprint(FILE *stream, const ndindex_t *i)
/*
  Purpose:

    Prints a multidimensional index.

  Arguments:
    stream       a pointer to a file stream
    i            a pointer to an ndindex_t

  Return value:
    None
*/
{
  if (i == NULL)
    return;
  fprintf(stream, "(");
  for (size_t k = 0; k < i->ndim; k++)
  {
    fprintf(stream, "%3zu ", i->idx[k]);
  }
  fprintf(stream, ")\n");
}

void ndindex_print(const ndindex_t *i) { ndindex_fprint(stdout, i); }
