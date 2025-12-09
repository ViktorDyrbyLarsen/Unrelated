#include <stdlib.h>
#include "poly.h"

poly_t *polymul(const poly_t *p1, const poly_t *p2)
{
    poly_t *product = malloc(sizeof(poly_t));
    if (!p1 || !p2 || !p1->coef || !p2->coef || !product) {
        return NULL;
    }

    product->coef = calloc(p1->deg + p2->deg + 1, sizeof(double));
    product->deg = p1->deg + p2->deg;
    for (unsigned int i = 0; i <= p1->deg; i++) {
        for (unsigned int j = 0; j <= p2->deg; j++) {
            product->coef[i+j] += p1->coef[i] * p2->coef[j];
        }
    }
    return product;
}
