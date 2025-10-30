#include <stdlib.h>
#include <math.h>
#include "array2d.h"

/** DTRSV
 *  BLAS level 2 routine for forward/back substitution
 *  Documentation: http://www.netlib.org/blas/#_level_2
 */
void dtrsv_(
  const char * uplo,  /* upper 'U' or lower 'L'               */
  const char * trans, /* not trans. 'N' or trans. 'T'         */
  const char * diag,  /* not unit diag. 'N' or unit diag. 'U' */
  const int * n,      /* dimension                            */
  const double * A,   /* column-major matrix of order n       */
  const int * lda,    /* leading dimension of A               */
  double * x,         /* right-hand side                      */
  const int * incx    /* stride for array x                   */
);

/** Solves system of equations L*U*x = b where
 *  L is unit lower triangular and U is upper triangular.
 *  The matrices L and U must be stored in a single array M
 *  of size n-by-n. On exit, the array b is overwritten by
 *  the solution x.
 *
 *  If successful, the function returns zero, and in case
 *  of an error, the return value is 1.
 *
 *  Inputs:
 *    M       dynamically allocated two-dimensional array of size n-by-n
 *    b       one-dimensional array of length n
 */
int dtrsvsolve(array2d_t * M, double * b) {
    // Insert your code here
}

