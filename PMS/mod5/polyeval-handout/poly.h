#ifndef _POLY_H_
#define _POLY_H_

/* Data structure that represents a polynomial of degree deg */
typedef struct {
    unsigned int deg;
    double *coef;
} poly_t;

/* Allocation and deallocation routines */
poly_t * poly_new(unsigned int deg);
void poly_del(poly_t * p);

/* Display polynomial as a string */
void poly_print(poly_t * p);

#endif
