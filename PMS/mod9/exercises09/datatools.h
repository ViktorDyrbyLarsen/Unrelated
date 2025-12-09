/* datatools.h - support functions for the matrix times vector example
 *
 * DTU Course 02635 - Fall 2021
 *
 * This version uses MSPTools
 *
 * Author:  Bernd Dammann, DTU Compute
 * Version: $Revision$ $Date$
 */
#ifndef __DATATOOLS_H
#define __DATATOOLS_H

#include "array.h"
#include "array2d.h"

void init_data (int m, 		/* number of rows               */
                int n, 		/* number of columns            */
		array_t *a, 	/* result vector of length m    */
		array2d_t *B, 	/* two-dim array of size m-by-n */
		array_t *c, 	/* input vector of length n     */
		array_t *ref	/* reference vector of length m */
               );

int check_results(char *comment, /* comment string 		 */
                  int m,         /* number of rows               */
		  int n,         /* number of columns            */
		  array_t *a,    /* vector of length m           */
		  array_t *ref   /* reference vector of length m */
		 );

#endif  /* __DATATOOLS_H */

