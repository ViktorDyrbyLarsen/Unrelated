#include <stdlib.h>
#include <math.h>
#include "poly.h"

double polyeval(const poly_t *p, double x) {
    if (!p || !p->coef) {
        return NAN;
    }
    double v = 0.0;
    for (int i = p->deg; i >= 0; i--) {
        v = v * x + p->coef[i];
    }
}
