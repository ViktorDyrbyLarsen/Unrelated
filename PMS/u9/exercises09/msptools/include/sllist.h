#ifndef SLLIST_H
#define SLLIST_H

#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct snode /* singly linked list node */
{
    double x;           // payload
    struct snode *next; // pointer to next snode (NULL if tail)
} snode_t;

typedef struct sll /* singly linked list */
{
    size_t length;      // length (number of nodes)
    struct snode *head; // pointer to head (NULL if empty)
} sllist_t;

sllist_t *sllist_alloc(size_t len);
void sllist_dealloc(sllist_t *L);
int sllist_insert(sllist_t *L, size_t i, double x);
int sllist_insert_after(sllist_t *L, snode_t *N, double x);
int sllist_delete(sllist_t *L, size_t i);
snode_t *sllist_find(sllist_t *L, size_t i);
sllist_t *sllist_concat(sllist_t *L1, sllist_t *L2);
sllist_t *sllist_split(sllist_t *L, size_t i);
void sllist_fprint(FILE *stream, sllist_t *L);
void sllist_print(sllist_t *L);

snode_t *snode_alloc(double x);
void snode_dealloc(snode_t *N);

#endif