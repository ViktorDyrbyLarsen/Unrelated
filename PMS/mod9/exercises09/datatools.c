/* datatools.c - support functions for the matrix times vector example
 *
 * DTU Course 02635 - Fall 2021
 *
 * Author:  Bernd Dammann, DTU Compute
 * Version: $Revision$ $Date$
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#include "datatools.h"

void
init_data(int m, 
          int n, 
	  array_t * a, 
	  array2d_t * B, 
	  array_t * c,
	  array_t * ref) {

    int err_count = 0;

    if (m > a->capacity) {
	fprintf(stderr,
		"init_data(): 1st argument array too small: %zu < %d!\n",
		c->capacity, m);
	err_count++;
    }

    if (n > c->capacity) {
	fprintf(stderr,
		"init_data(): 3rd argument array too small: %zu < %d!\n",
		c->capacity, n);
	err_count++;
    }

    if (B->shape[0] != m || B->shape[1] != n) {
	fprintf(stderr,
		"init_data(): 2nd argument matrix has wrong dimensions! "
		"(%zu,%zu) should be (%d,%d)\n",
		B->shape[0], B->shape[1], m, n);
	err_count++;
    }

    if (m > ref->capacity) {
	fprintf(stderr,
		"init_data(): 4th argument array too small: %zu < %d!\n",
		c->capacity, m);
	err_count++;
    }
    if (err_count > 0)
	exit(EXIT_FAILURE);


    //#pragma omp parallel for
    for (int j = 0; j < n; j++)
	c->val[j] = 1.0;
    c->len = n;

    if (B->order == RowMajor) {
	//#pragma omp parallel for
	for (int i = 0; i < m; i++) {
	    ref->val[i] = n * i;
	    a->val[i] = -2005.0;
	    for (int j = 0; j < n; j++)
		B->val[i * n + j] = i;
	}
    }
    else {
	//#pragma omp parallel for
	for (int i = 0; i < m; i++) {
	    ref->val[i] = n * i;
	    a->val[i] = -2005.0;
	}

	//#pragma omp parallel 
	for (int i = 0; i < m; i++) {
	    //#pragma omp for
	    for (int j = 0; j < n; j++)
		B->val[i + j * m] = i;
	}
    }
    a->len = m;
    ref->len = m;

}

int
check_results(char *comment, 
              int m, 
	      int n, 
	      array_t *a_in, 
	      array_t *ref_in) {

    double relerr;
    int i, errors = 0;
    char *marker;
    double TOL = 100.0 * DBL_EPSILON;
    double SMALL = 100.0 * DBL_MIN;
    double *a   = a_in->val;
    double *ref = ref_in->val;

    if ((marker = (char *) malloc(m * sizeof(char))) == NULL) {
	perror("array marker");
	exit(-1);
    }

    for (i = 0; i < m; i++) {
	if (fabs(ref[i]) > SMALL) {
	    relerr = fabs((a[i] - ref[i]) / ref[i]);
	}
	else {
	    relerr = fabs((a[i] - ref[i]));
	}
	if (relerr <= TOL) {
	    marker[i] = ' ';
	}
	else {
	    errors++;
	    marker[i] = '*';
	}
    }
    if (errors > 0) {
	printf("Routine: %s\n", comment);
	printf("Found %d differences in results for m=%d n=%d:\n",
	       errors, m, n);
	for (i = 0; i < m; i++)
	    printf("\t%c a[%d]=%f ref[%d]=%f\n", marker[i], i, a[i], i,
		   ref[i]);
    }
    return (errors);
}
