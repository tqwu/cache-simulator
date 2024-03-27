#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

struct Node {
    char data;
    Node *next;
    Node *prev;
    int reference_bit; // Utilized for Clock policy
};

// Function to create a node
// Returns a pointer to a new node if creation was successful, NULL otherwise
Node *node_create(char data);

// Function to delete a node
void node_delete(Node **n);

void node_print(Node *n);

#endif
