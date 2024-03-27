#ifndef __LL_H__
#define __LL_H__

#include "node.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct LinkedList {
    Node *head;
    Node *tail;
    Node *clock_hand;
    int size; // Current size
    int capacity; // Maximum size
    bool mtf; // Option to move-to-front of cache
    bool clock; // Option to use clock policy
} LinkedList;

// Function to create a linked list
LinkedList *ll_create(int capacity, bool mtf, bool clock);

// Function to delete a linked list
void ll_delete(LinkedList **ll);

// Function to look up a node in the linked list
// Returns a pointer to a new node if lookup was successful, NULL otherwise
Node *ll_lookup(LinkedList *ll, char data);

// Function to insert a node into the linked list
// Returns 0 if item exists, return 1 if item was successfully added
int ll_insert(LinkedList *ll, char data, bool clock);

void ll_print(LinkedList *ll);

#endif
