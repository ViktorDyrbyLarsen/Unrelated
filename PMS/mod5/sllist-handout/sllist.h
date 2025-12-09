#ifndef SLLIST_H
#define SLLIST_H

#include <stdlib.h>

typedef struct snode
{
    double x;           // Payload
    struct snode *next; // Pointer to next snode (NULL if tail)
} snode_t;

typedef struct sll
{
    size_t length;      // Length (number of nodes)
    struct snode *head; // Pointer to head (NULL if empty)
} sllist_t;

#endif