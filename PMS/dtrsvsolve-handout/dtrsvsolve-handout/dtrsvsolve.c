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
    if (!M || !M->val || !b || M->shape[0] != M->shape[1]) return 1;
    
    const int n = M->shape[0];
    const int lda = n;
    const int incx = 1;
    const char trans = (M->order == RowMajor) ? 'T' : 'N';

    for (int i = 0; i < n; i++) {
        if (M->val[i*n + i] == 0.0) return 1; // singular matrix
    }
    
    if (M->order == RowMajor) {
      
      char uplo, diag;

      // Solving L * y = b
      uplo = 'U'; // L becomes upper due to transpose
      diag = 'U';
      dtrsv_(&uplo, &trans, &diag, &n, M->val, &lda, b, &incx);

      // Solving U * x = y
      uplo = 'L'; // U becomes lower due to transpose
      diag = 'N';
      dtrsv_(&uplo, &trans, &diag, &n, M->val, &lda, b, &incx);
    }
    else if (M->order == ColMajor) {
      char uplo, diag;

      // Solving L * y = b
      uplo = 'L';
      diag = 'U';
      dtrsv_(&uplo, &trans, &diag, &n, M->val, &lda, b, &incx);

      // Solving U * x = y
      uplo = 'U';
      diag = 'N';
      dtrsv_(&uplo, &trans, &diag, &n, M->val, &lda, b, &incx);
    }
    

    return 0;
    

}

