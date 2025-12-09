#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sllist.h"

int sllist_replace(const sllist_t *L, const size_t k, const double val);

int main(void)
{

    // Create an empty singly linked list 
    sllist_t *L = malloc(sizeof(*L));
    L->length = 0;
    L->head = NULL;

    // Add 10 nodes to the list
    snode_t *node;
    for (int i=0; i<10; i++)
    {
        node = L->head;
        L->head = malloc(sizeof(*node));
        L->head->x = i;
        L->head->next = node;
        L->length++;
    }    
    
    // Replace the value of the node at index 5 by 100
    int rc = sllist_replace(L, 5, 100);
    if (rc != 0)
    {
        fprintf(stderr, "  ***Test failed! Expected return value 0 but got %d.\n", rc);
        return EXIT_FAILURE;
    }   

    // Check that the length of the list is still 10
    if (L->length != 10)
    {
        fprintf(stderr, "  ***Test failed! Expected length: 10\n");
        return EXIT_FAILURE;
    }

    // Check that the value of the node at index 5 is 100
    node = L->head;
    for (int i =0; i<5; i++) 
        node = node->next;
    if (node->x != 100) 
    {
        fprintf(stderr, "  ***Test failed! Expected value: 100\n");
        return EXIT_FAILURE;
    }

    // Check the return value when L is NULL
    if (sllist_replace(NULL, 5, 100) != 1)
    {
        fprintf(stderr, "  ***Test failed! Expected return value: 1\n");
        return EXIT_FAILURE;
    }

    // Check the return value when k is out of bounds
    if (sllist_replace(L, 100, 100) != 1)
    {
        fprintf(stderr, "  ***Test failed! Expected return value: 1\n");
        return EXIT_FAILURE;
    }

    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
