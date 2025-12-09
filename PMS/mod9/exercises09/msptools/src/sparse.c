#include "sparse.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

coo_t *coo_alloc(const size_t shape[2], const size_t capacity)
/*
  Purpose:

    Allocates a COO sparse matrix with a given capacity. 
    The number on nonzero elements is set to 0.

  Example:

    ```c
    coo_t *sp = coo_alloc((size_t []){5,5}, 13);
    if (sp==NULL) exit(EXIT_FAILURE);
    size_t k = 0, lower, upper;
    for (size_t j=0;j<5;j++) {
      lower = j-1 < 0 ? 0 : j-1;
      upper = j+1 > 4 ? 4 : j+1;
      for (size_t i=lower;i<=upper;i++) {
        sp->rowidx[k] = i;
        sp->colidx[k] = j;
        if (i==j) sp->val[k] = 2.0;
        else sp->val[k] = -1.0;
        k++;
      }
    }
    // .. do something with sparse matrix ..
    coo_dealloc(sp);
    ```

  Arguments:
    shape      two-dimensional array with row and column dimensions
    capacity   maximum number of nonzero elements

  Return value:
    A pointer to a coo_t, or NULL if an error occurs.
*/
{
  coo_t *sp = malloc(sizeof(*sp));
  if (sp == NULL) {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  sp->shape[0] = shape[0];
  sp->shape[1] = shape[1];
  sp->capacity = capacity;
  sp->nnz = 0;
  sp->rowidx = malloc(capacity * sizeof(*sp->rowidx));
  sp->colidx = malloc(capacity * sizeof(*sp->colidx));
  sp->val = malloc(capacity * sizeof(*sp->val));
  if (sp->rowidx == NULL || sp->colidx == NULL || sp->val == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    coo_dealloc(sp);
    return NULL;
  }
  return sp;
}

void coo_dealloc(coo_t *sp)
// Purpose: Deallocates a coo_t.
{
  if (sp == NULL)
    free(sp->rowidx);
  free(sp->colidx);
  free(sp->val);
  free(sp);
}

/* coo_from_file
  Purpose:

    Reads a sparse matrix in COO format from a text file in the so-called
    Matrix Market (MM) coordinate format (indices are 1-based):

   +----------------------------------------------+
   |%%MatrixMarket matrix coordinate real general | <--- header line
   |%                                             | <--+
   |% comments                                    |    |-- 0 or more lines
   |%                                             | <--+
   |    M  N  L                                   | <--- rows, columns, entries
   |    I1  J1  A(I1, J1)                         | <--+
   |    I2  J2  A(I2, J2)                         |    |
   |    I3  J3  A(I3, J3)                         |    |-- L lines
   |        . . .                                 |    |
   |    IL JL  A(IL, JL)                          | <--+
   +----------------------------------------------+

  Arguments:
    filename   string with filename

  Return value:
    A pointer to a coo_t, or NULL if an error occurs.
*/
coo_t *coo_from_file(const char *filename)
{
  char buf[MM_MAX_LINE_LENGTH];
  char banner[MM_MAX_TOKEN_LENGTH];
  char mtx[MM_MAX_TOKEN_LENGTH]; 
  char crd[MM_MAX_TOKEN_LENGTH];
  char data_type[MM_MAX_TOKEN_LENGTH];
  char storage_scheme[MM_MAX_TOKEN_LENGTH];

  size_t m, n, nnz;
  /* Open file and read dimensions */
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
#ifndef NDEBUG
    FILE_ERR(filename);
#endif
    return NULL;
  }

  /* Read banner/header line */
  char *line = fgets(buf, MM_MAX_LINE_LENGTH, fp);
  if (line == NULL || sscanf(line, "%s %s %s %s %s", banner, mtx, crd, data_type, storage_scheme) != 5) 
  {
    fclose(fp);
    return NULL;
  }
  for (char *p=mtx; *p!='\0'; *p=tolower(*p),p++);  /* convert to lower case */
  for (char *p=crd; *p!='\0'; *p=tolower(*p),p++);  
  for (char *p=data_type; *p!='\0'; *p=tolower(*p),p++);
  for (char *p=storage_scheme; *p!='\0'; *p=tolower(*p),p++);

  if ( (strncmp(banner, "%%MatrixMarket", 14) != 0) || 
       (strncmp(mtx, "matrix", 6) != 0) || 
       (strncmp(crd, "coordinate", 10) != 0) || 
       (strncmp(data_type, "real", 4) != 0) ||
       (strncmp(storage_scheme, "general", 7) != 0) ) {
    fclose(fp);
    return NULL;
  }
  /* Skip comment lines */
  while ((line = fgets(buf, MM_MAX_LINE_LENGTH, fp)) && strncmp(line, "%", 1) == 0)
    continue;
  if (sscanf(line, "%zu %zu %zu", &m, &n, &nnz) != 3)
  {
    fprintf(stderr, "%s: could not read matrix dimensions\n", __func__);
    fclose(fp);
    return NULL;
  }
  /* Allocate sparse_triplet structure */
  coo_t *sp = coo_alloc((size_t[]){m, n}, nnz);
  if (sp == NULL)
  {
    fclose(fp);
    return NULL;
  }
  /* Read triplets and subtract 1 from indices */
  for (size_t i = 0; i < nnz; i++)
  {
    if (3 == fscanf(fp, "%zu %zu %lf", sp->rowidx + i, sp->colidx + i,
                    sp->val + i))
    {
      sp->rowidx[i]--;
      sp->colidx[i]--;
    }
    else
    {
      fprintf(stderr, "%s: could not read triplet\n", __func__);
      fclose(fp);
      coo_dealloc(sp);
      return NULL;
    }
  }
  sp->nnz = nnz;
  /* Close file and return pointer to coo_t */
  fclose(fp);
  return sp;
}

/* coo_to_file
  Purpose:

    Writes a sparse matrix in COO format to a text file in the so-called
    Matrix Market (MM) coordinate format (indices are 1-based):

   +----------------------------------------------+
   |%%MatrixMarket matrix coordinate real general | <--- header line
   |%                                             | <--+
   |% comments                                    |    |-- 0 or more lines
   |%                                             | <--+
   |    M  N  L                                   | <--- rows, columns, entries
   |    I1  J1  A(I1, J1)                         | <--+
   |    I2  J2  A(I2, J2)                         |    |
   |    I3  J3  A(I3, J3)                         |    |-- L lines
   |        . . .                                 |    |
   |    IL JL  A(IL, JL)                          | <--+
   +----------------------------------------------+

  Arguments:
    filename   string with filename
    sp         pointer to coo_t

  Return value:
    MSP_SUCCESS if successful, and MSP_FILE_ERR if a file error occurs.
*/
int coo_to_file(const char *filename, const coo_t *sp)
{
  /* Check that sp is not NULL */
  if (sp == NULL)
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
  /* Write sparse_triplet structure to file */
  fprintf(fp, "%%%%MatrixMarket matrix coordinate real general\n");
  fprintf(fp, "%zu %zu %zu\n", sp->shape[0], sp->shape[1], sp->nnz);
  for (size_t i = 0; i < sp->nnz; i++)
    fprintf(fp, "%zu %zu %.17g\n", sp->rowidx[i] + 1, sp->colidx[i] + 1, sp->val[i]);
  fclose(fp);
  return MSP_SUCCESS;
}

void coo_fprint(FILE *stream, const coo_t *sp)
/*
  Purpose:

    Prints a sparse matrix in COO format

  Arguments:
    stream       a pointer to a file stream
    sp           a pointer to a coo_t

  Return value:
    None
*/
{
  if (sp == NULL)
    return;
  fprintf(stream, "<coo_t shape=(%zu,%zu) nnz=%zu>\n", sp->shape[0], sp->shape[1], sp->nnz);
  for (size_t i = 0; i < sp->nnz; i++)
    fprintf(stream, "%4zu %4zu % 8.3g\n", sp->rowidx[i] + 1, sp->colidx[i] + 1, sp->val[i]);
}

void coo_print(const coo_t *sp) { coo_fprint(stdout, sp); }

csp_t *csp_alloc(const size_t shape[2], const size_t nnz, enum cstype csx)
/*
  Purpose:

    Allocates a compressed sparse matrix with a given number of nonzeros.

  Example:

    ```c
    csp_t *sp = csp_alloc((size_t []){6,5}, 10, CSC);
    if (sp==NULL) exit(EXIT_FAILURE);
    for (size_t k=0;k<5;k++) {
      sp->ptr[k] = 2*k;
      sp->idx[2*k]   = k;
      sp->idx[2*k+1] = k+1;      
      sp->val[2*k]   = -1.0;
      sp->val[2*k+1] =  1.0;
    }
    // .. do something with sparse matrix ..
    csp_dealloc(sp);
    ```

  Arguments:
    shape      array with row and column dimensions
    nnz        number of nonzero elements
    csx        CSC or CSR

  Return value:
    A pointer to a csp_t, or NULL if an error occurs.
*/
{
  csp_t *sp = malloc(sizeof(*sp));
  if (sp == NULL) {
#ifndef NDEBUG
    MEM_ERR;
#endif
    return NULL;
  }
  size_t N = (csx == CSC) ? shape[1] : shape[0];
  sp->shape[0] = shape[0];
  sp->shape[1] = shape[1];
  sp->csx = csx;
  sp->idx = malloc(nnz * sizeof(*(sp->idx)));
  sp->ptr = malloc((N + 1) * sizeof(*(sp->ptr)));
  sp->val = malloc(nnz * sizeof(*(sp->val)));
  if (sp->idx == NULL || sp->ptr == NULL || sp->val == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    csp_dealloc(sp);
    return NULL;
  }
  for (size_t k = 0; k < N; k++)
    sp->ptr[k] = nnz;
  return sp;
}

void csp_dealloc(csp_t *sp)
// Purpose: Deallocates a csp_t.
{
  if (sp == NULL)
    return;
  free(sp->idx);
  free(sp->ptr);
  free(sp->val);
  free(sp);
}

csp_t *csp_from_coo(const coo_t *sp, enum cstype csx)
/*
  Purpose:

    Compresses a sparse matrix in the coordinate format to a compressed
    sparse matrix. The row indices are not sorted. 

  Example:

    ```c
    coo_t *sp = coo_alloc((size_t []){5,5}, 13);
    // .. initialize COO sparse matrix ..
    csp_t *csp = csp_from_coo(sp, CSC);
    coo_dealloc(sp);
    // .. do something with csp ..
    csp_dealloc(csp);
    ```

  Arguments:
    sp          a pointer to a coo_t

  Return value:
    A pointer to a csp_t, or NULL if an error occurs.
*/
{
  if (sp == NULL)
    return NULL; /* Check input */

  /* Allocate output */
  csp_t *csp = csp_alloc(sp->shape, sp->nnz, csx);
  if (csp == NULL)
    return NULL;
  /* Allocate workspace */
  size_t N = (csx == CSC) ? sp->shape[1] : sp->shape[0];
  size_t *ws = calloc(N, sizeof(*ws));
  if (ws == NULL)
  {
#ifndef NDEBUG
    MEM_ERR;
#endif
    csp_dealloc(csp);
    return NULL;
  }
  /* Compute column counts */
  size_t *spidx = (csx == CSC) ? sp->colidx : sp->rowidx;
  size_t *spidx_other = (csx == CSC) ? sp->rowidx : sp->colidx;
  for (size_t k = 0; k < sp->nnz; k++)
    ws[spidx[k]]++;
  /* Compute ptr array (store copy in ws)*/
  size_t nz = 0;
  for (size_t k = 0; k < N; k++)
  {
    csp->ptr[k] = nz;
    nz += ws[k];
    ws[k] = csp->ptr[k];
  }
  csp->ptr[N] = nz;
  /* Copy row indices and values */
  size_t j = 0;
  for (size_t k = 0; k < sp->nnz; k++)
  {
    csp->idx[j = ws[spidx[k]]++] = spidx_other[k];
    csp->val[j] = sp->val[k];
  }
  /* Free workspace and return */
  free(ws);
  return csp;
}

void csp_fprint(FILE *stream, const csp_t *sp)
/*
  Purpose:

    Prints a sparse matrix in CSC/CSR format

  Arguments:
    stream       a pointer to a file stream
    sp           a pointer to a csp_t

  Return value:
    None
*/
{
  if (sp == NULL)
    return;
  size_t N = (sp->csx == CSC) ? sp->shape[1] : sp->shape[0];
  fprintf(stream, "<csp_t %s shape=(%zu,%zu) nnz=%zu>\n",
          (sp->csx == CSC) ? "csc" : "csr", sp->shape[0], sp->shape[1], sp->ptr[N]);
  if (sp->csx == CSC)
  {
    for (size_t k = 0; k < N; k++)
    {
      for (size_t i = sp->ptr[k]; i < sp->ptr[k + 1]; i++)
        fprintf(stream, "%4zu %4zu % 8.3g\n", sp->idx[i]+1, k+1, sp->val[i]);
    }
  }
  else
  {
    for (size_t k = 0; k < N; k++)
    {
      for (size_t i = sp->ptr[k]; i < sp->ptr[k + 1]; i++)
        fprintf(stream, "%4zu %4zu % 8.3g\n", k+1, sp->idx[i]+1, sp->val[i]);
    }
  }
}

void csp_print(const csp_t *sp) { csp_fprint(stdout, sp); }
