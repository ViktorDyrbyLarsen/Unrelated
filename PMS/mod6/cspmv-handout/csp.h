#ifndef CSP_H
#define CSP_H

#include <stdlib.h>

enum cstype { CSC, CSR };
typedef struct csp /* compressed sparse format (CSC/CSR) */
{
    size_t shape[2];
    enum cstype csx;
    size_t *ptr;
    size_t *idx;
    double *val;
} csp_t;

#endif
