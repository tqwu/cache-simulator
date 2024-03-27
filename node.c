#include "node.h"

Node *node_create(char data) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    n->reference_bit = 0;

    return n;
}

void node_delete(Node **n) {
    if (n != NULL && *n != NULL) {
        free(*n);
        *n = NULL;
    }
}

void node_print(Node *n) {
    printf("%c ", n->data);
    printf("%d\n", n->reference_bit);
}
