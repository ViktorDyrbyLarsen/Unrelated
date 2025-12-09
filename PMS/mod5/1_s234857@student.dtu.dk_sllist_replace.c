#include <stdlib.h>
#include "sllist.h"

int sllist_replace(const sllist_t *L, const size_t k, const double val) {
    if (!L || !L->head) {
        return 1;
    }
    if (k >= L->length) {
        return 1;
    }

    struct snode *current = L->head;
    for (size_t i = 0; i < k; i++) {
        if (!current->next) return 1;
        current = current->next;
    }
    current->x = val;
    return 0;
}