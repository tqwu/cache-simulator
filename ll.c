#include "ll.h"

LinkedList *ll_create(int capacity, bool mtf, bool clock) {
    LinkedList *L = malloc(sizeof(LinkedList));

    L->head = node_create('\0');
    L->tail = node_create('\0');
    L->clock_hand = node_create('\0');

    L->tail->prev = L->head;
    L->head->next = L->tail;

    L->size = 0;
    L->capacity = capacity;
    L->mtf = mtf;
    L->clock = clock;

    return L;
}

void ll_delete(LinkedList **ll) {
    while ((*ll)->head != NULL) {
        Node *curr = (*ll)->head;
        (*ll)->head = (*ll)->head->next;
        node_delete(&curr);
    }
    free(*ll);
    *ll = NULL;
}

Node *ll_lookup(LinkedList *ll, char data) {

    // Tracking the current position
    Node *curr = ll->head->next;

    while (curr != ll->tail) {

        // If item is already in the linked list
        if (curr->data == data) {

            // If clock policy is enabled, set reference bit
            if (ll->clock) {
                curr->reference_bit = 1;
            }

            // If LRU policy is enabled, move node to the front of the linked list
            if (ll->mtf) {

                // Bridging nodes behind and in front of current node
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;

                // Moving the node to the front
                curr->next = ll->head->next;
                curr->prev = ll->head;
                ll->head->next = curr;
                curr->next->prev = curr;
            }
            return curr;
        }

        curr = curr->next;
    }
    return NULL;
}

int ll_insert(LinkedList *ll, char data, bool clock) {

    // Returns if the item already exists in the cache
    if (ll_lookup(ll, data) != NULL) {
        return 0;
    }

    // If the linked list is at capacity
    if (ll->size == ll->capacity) {

        if (clock) {
            Node *curr = ll->clock_hand;

            while (curr->reference_bit == 1) {
                curr->reference_bit = 0;

                if (curr->prev != ll->head) {
                    curr = curr->prev;
                } else {
                    curr = ll->tail->prev;
                }
            }

            // Replace the node pointed to by the clock hand with a newly inserted node
            Node *new = node_create(data);
            new->prev = curr->prev;
            new->next = curr->next;
            curr->prev->next = new;
            curr->next->prev = new;
            node_delete(&curr);

            // Moving the clock hand
            if (new->prev != ll->head) {
                ll->clock_hand = new->prev;
            } else {
                ll->clock_hand = ll->tail->prev;
            }

            return 1;
        } else {
            // Removing the last node
            Node *last = ll->tail->prev;
            last->prev->next = ll->tail;
            ll->tail->prev = last->prev;
            node_delete(&last);

            // Decrementing size of linked list
            ll->size -= 1;
        }
    }

    // Creating node which will be inserted
    Node *new = node_create(data);

    // Inserting node
    new->prev = ll->head;
    new->next = ll->head->next;
    ll->head->next->prev = new;
    ll->head->next = new;

    // Incrementing size of linked list
    ll->size += 1;

    // If clock policy is enabled and the linked list only has one item
    if (clock && ll->size == 1) {
        ll->clock_hand = new;
    }

    return 1;
}

void ll_print(LinkedList *ll) {
    for (Node *temp = ll->head->next; temp != ll->tail; temp = temp->next) {
        node_print(temp);
    }
}
