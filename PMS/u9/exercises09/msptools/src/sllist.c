#include <stdio.h>
#include "sllist.h"

sllist_t *sllist_alloc(size_t len)
/* 
  Purpose: 
    Allocates a singly linked list of a given length. The payload is 
    initialized as zero.

  Arguments:
    len        length of list

  Return value:
    A pointer to an sllist_t, or NULL if an error occurs.
*/

{
    sllist_t *L = calloc(1, sizeof(sllist_t));
    if (!L)
        return NULL;
    if (len > 0)
    {
        for (size_t k = 0; k < len; k++)
        {
            if (sllist_insert(L, 0, 0.0))
            {
                sllist_dealloc(L);
                return NULL;
            }
        }
    }
    return L;
}

void sllist_dealloc(sllist_t *L)
/* Purpose: Deallocates a sllist_t and all its nodes. */
{
    if (L)
    {
        while (L->length > 0)
            sllist_delete(L, 0);
        free(L);
    }
}

snode_t *snode_alloc(double x)
/* 
  Purpose:

    Allocated a node for a singly linked list.

  Arguments:
    x          value (payload) 

  Returns:
    A pointer to a snode_t, or NULL if an error occurs.
*/
{
    snode_t *N = calloc(1, sizeof(snode_t));
    if (!N)
        return NULL;
    N->x = x;
    return N;
}

void snode_dealloc(snode_t *N)
/* Purpose: Deallocates an snode_t. */
{
    if (N)
        free(N);
}

int sllist_insert_after(sllist_t *L, snode_t *N, double x)
/* 
  Purpose:

    Inserts a new node with value x after a given node.

  Arguments:
    L           pointer to an sllist_t
    N           pointer to an snote_t that is in L
    x           value to be inserted 

  Returns:
    MSP_SUCCESS if successful, MSP_MEM_ERR if allocation fails, and 
    MSP_ILLEGAL_INPUT if any of the inputs is a null pointer.
*/
{
    if (!N || !L)
        return MSP_ILLEGAL_INPUT;
    snode_t *Nnew = snode_alloc(x);
    if (!Nnew)
        return MSP_MEM_ERR;
    Nnew->next = N->next;
    N->next = Nnew;
    L->length++;
    return MSP_SUCCESS;
}

int sllist_insert(sllist_t *L, size_t i, double x)
/*
  Purpose:

    Inserts a new node with value x at a given index.

  Arguments:
    L           pointer to an sllist_t
    i           index (0-based)
    x           value to be inserted 

  Returns:
    MSP_SUCCESS if successful, MSP_MEM_ERR if allocation fails, and 
    MSP_ILLEGAL_INPUT if the input is invalid or if index is out of
    bounds.
*/
{
    if (!L || i > L->length)
        return MSP_ILLEGAL_INPUT;
    snode_t *nptr;
    if (i == 0)
    {
        nptr = snode_alloc(x);
        if (!nptr)
            return MSP_MEM_ERR;
        nptr->next = L->head;
        L->head = nptr;
        L->length++;
    }
    else
    {
        snode_t *prev = sllist_find(L, i - 1);
        int ret = sllist_insert_after(L, prev, x);
        if (ret != MSP_SUCCESS)
            return ret;
    }
    return MSP_SUCCESS;
}

int sllist_delete(sllist_t *L, size_t i)
/*
  Purpose:

    Deletes and deallocates a node at a given index.

  Arguments:
    L           pointer to an sllist_t
    i           index (0-based)

  Returns:
    MSP_SUCCESS if successful, MSP_ILLEGAL_INPUT if the input 
    is invalid or if index is out of bounds, and MSP_FAILURE
    if an error occurs.
*/
{
    if (!L || i >= L->length)
        return MSP_ILLEGAL_INPUT;
    snode_t *nptr;
    if (i == 0)
    {
        nptr = L->head;
        L->head = nptr->next;
    }
    else
    {
        snode_t *prev = sllist_find(L, i - 1);
        if (!prev)
            return MSP_FAILURE;
        nptr = prev->next;
        prev->next = nptr->next;
    }
    snode_dealloc(nptr);
    L->length--;
    return MSP_SUCCESS;
}

snode_t *sllist_find(sllist_t *L, size_t i)
/*
  Purpose:

    Locates node at index i.

  Arguments:
    L           pointer to an sllist_t
    i           index (0-based)

  Returns:
    A pointer to node at index i, or NULL if the input is invalid 
    or if index is out of bounds.
*/
{
    if (!L || i >= L->length)
        return NULL;
    snode_t *nptr = L->head;
    for (size_t k = 0; k < i; k++)
        nptr = nptr->next;
    return nptr;
}

sllist_t *sllist_concat(sllist_t *L1, sllist_t *L2)
/*
  Purpose:

    Concatenates two lists. The input lists are not modified.

  Arguments:
    L1         a pointer to an sllist_t
    L2         a pointer to an sllist_t

  Returns:
    A pointer to a new list that contains a copy of the nodes
    of the input lists, or NULL is an error occurs.
*/
{
    if (!L1 || !L2)
        return NULL;
    sllist_t *L = sllist_alloc(L1->length + L2->length);
    if (!L)
        return NULL;
    snode_t *N = L->head;
    snode_t *Nt = L1->head;
    size_t n = L1->length;
    for (size_t k = 0; k < n; k++)
    {
        N->x = Nt->x;
        N = N->next;
        Nt = Nt->next;
    }
    Nt = L2->head;
    n = L2->length;
    for (size_t k = 0; k < n; k++)
    {
        N->x = Nt->x;
        N = N->next;
        Nt = Nt->next;
    }
    return L;
}

sllist_t *sllist_split(sllist_t *L, size_t i)
/*
  Purpose:

    Splits a list at a given index.

  Arguments:
    L          a pointer to an sllist_t
    i          index (0-based)

  Returns:
    A pointer to a new list that contains the node at index i
    and subsequent nodes, or NULL is an error occurs. The input 
    list is modified so that it contains the nodes up until 
    index i.
*/
{
    if (!L || i >= L->length)
        return NULL;

    sllist_t *Lt = sllist_alloc(L->length - i);
    if (!L)
        return NULL;
    if (i == 0)
    {
        Lt->head = L->head;
        Lt->length = L->length;
        L->head = NULL;
        L->length = 0;
    }
    else
    {
        snode_t *N = sllist_find(L, i - 1);
        if (!N)
        {
            sllist_dealloc(Lt);
            return NULL;
        }
        Lt->head = N->next;
        N->next = NULL;
        Lt->length = L->length - i;
        L->length = i;
    }
    return Lt;
}

void sllist_fprint(FILE *stream, sllist_t *L)
/*
  Purpose:

    Prints the content of a singly linked list.

  Arguments:
    stream     a pointer to a file stream
    L          a pointer to an sllist_t
*/
{
    if (!L)
        return;
    fprintf(stream, "<sllist_t length=%zu>\n", L->length);
    snode_t *nptr = L->head;
    for (size_t k = 0; k < L->length; k++)
    {
        fprintf(stream, "  % -12.3g\n", nptr->x);
        nptr = nptr->next;
    }
}

void sllist_print(sllist_t *L) { sllist_fprint(stdout, L); }