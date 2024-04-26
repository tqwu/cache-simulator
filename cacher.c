#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "ll.h"

void print_usage(void) {
    fprintf(stderr, "USAGE: ./cacher [-N size] <policy>\n\n");
    fprintf(stderr, "<policy> OPTIONS:\n");
    fprintf(stderr, "-F   First-In First-Out (default policy if none provided)\n");
    fprintf(stderr, "-L   Least Recently Used\n");
    fprintf(stderr, "-C   Clock\n");
}

int main(int argc, char **argv) {

    bool policy_FIFO = false;
    bool policy_LRU = false;
    bool policy_clock = false;

    int opt;
    int size = -1;
    char *endptr = NULL;

    if (argc < 2 || argc > 4) {
        print_usage();
        exit(1);
    }

    while ((opt = getopt(argc, argv, "N:FLC")) != -1) {
        switch (opt) {
        case 'N':
            size = (int) strtoull(optarg, &endptr, 10);
            if (endptr == optarg) {
                printf("Invalid size parameter.\n");
                print_usage();
                exit(1);
            }
            break;
        case 'F': policy_FIFO = true; break;
        case 'L': policy_LRU = true; break;
        case 'C': policy_clock = true; break;
        case '?': print_usage(); exit(1);
        default: break;
        }
    }

    // If size parameter was not provided
    if (size == -1 || size == 0) {
        fprintf(stderr, "Invalid size parameter.\n");
        print_usage();
        exit(1);
    }

    LinkedList *ll = NULL;
    char *bit_array = calloc(128, sizeof(char));
    int compulsory_misses = 0;
    int capacity_misses = 0;

    // Created cache with FIFO policy
    if (policy_FIFO) {
        ll = ll_create(size, false, false);
    }
    // Created cache with LRU policy
    else if (policy_LRU) {
        ll = ll_create(size, true, false);
    }
    // Created cache with clock policy
    else if (policy_clock) {
        ll = ll_create(size, false, true);
    }
    // Otherwise if no policy was provided, default to FIFO
    else {
        ll = ll_create(size, false, false);
    }

    // Read operations from stdin as they come in
    char buffer[16];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        // If the item exists in the cache
        if (ll_insert(ll, buffer[0], policy_clock) == 0) {
            printf("HIT\n");
        }

        // If the item does not exist in the cache
        else {
            int ascii = (int) buffer[0];

            // Check if the item was previously in the cache, but subsequently removed
            if (bit_array[ascii] == 1) {
                capacity_misses++;
            }
            // If the item was not previously in the cache, set bit in bit array to 1
            else {
                bit_array[ascii] = 1;
                compulsory_misses++;
            }
            printf("MISS\n");
        }
    }

    // Freeing memory
    ll_delete(&ll);
    free(bit_array);

    printf("%d %d\n", compulsory_misses, capacity_misses);

    return 0;
}

