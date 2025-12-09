#include <stdlib.h>
#include <stdio.h>
#include "poly.h"

/* Allocates a new polynomial structure */
poly_t * poly_new(unsigned int deg) {
    poly_t * q = malloc(sizeof(*q));
    if (q==NULL) return NULL;
    q->deg = deg;
    q->coef = calloc(deg+1,sizeof(*(q->coef)));
    if (q->coef==NULL) {
        free(q);
        return NULL;
    }
    return q;
}

/* Frees a polynomial structure */
void poly_del(poly_t * p) {
    free(p->coef);
    free(p);
}

/* Prints a polynomial structure */
void poly_print(poly_t * p) {
    unsigned int i;
    if (p==NULL)
        fprintf(stderr,"poly_print: invalid pointer\n");
    else {
        for (i=p->deg;i>0;i--)
            printf("%+g*x^%d ", p->coef[i], i);
        printf("%+g\n", p->coef[0]);
    }
}
