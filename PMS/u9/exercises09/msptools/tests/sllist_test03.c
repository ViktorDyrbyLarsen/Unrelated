#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "msptools.h"

int main(void)
{
    sllist_t *L1 = sllist_alloc(0); // Allocate empty list
    sllist_t *L2 = sllist_alloc(0); // Allocate empty list
    assert(L1 != NULL && L2 != NULL);

    for (size_t k = 0; k < 4; k++) {
        sllist_insert(L2, 0, k + 1);
        sllist_insert(L1, 0, k + 5);
    }
    sllist_print(L1);
    sllist_print(L2);

    sllist_t *L3 = sllist_concat(L1,L2);
    assert(L3!=NULL && L3->length == L1->length+L2->length);
    sllist_print(L3);

    sllist_t *L4 = sllist_split(L3,3);
    sllist_print(L3);
    sllist_print(L4);

    sllist_dealloc(L1);
    sllist_dealloc(L2);
    sllist_dealloc(L3);
    sllist_dealloc(L4);
    return EXIT_SUCCESS;
}
