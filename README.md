# Caching Simulator
A simple command line cache simulator which supports single character items and three caching algorithms.\
After each lookup, the program will print whether the accessed item is a HIT or MISS. A summary of the total number of compulsory misses and capacity misses is printed at the end of the program.

## Design Choices
- The three caching algorithms/policies are FIFO (First In First Out), LRU (Least Recently Used), and Clock/Second-Chance
- A doubly linked list is the underlying data structure for the cache
- A bit array of size 128 coupled with ASCII encoding is used to keep track of capacity misses

**Definitions for this program:**
- Compulsory miss: a miss that occurs when the first access to a block is not and has never been in the cache
- Capacity miss: a miss on an item that has previously been in the cache, but subsequently removed

## Build/Clean
Build/clean this program with the following commands: 

    $ make
    $ make all
    $ make clean

## Running
Run this program with the following command and corresponding policy option:

    $ ./cacher [-N size] <policy>;

    $ <policy> OPTIONS:
    $ -F   First-In First-Out (default policy if none provided)
    $ -L   Least Recently Used
    $ -C   Clock

Exit the program with `Ctrl+D`.

## Files included
    cacher.c    : source file for the cache
    ll {h,c}.   : source files for struct and functions of doubly linked list
    node {h,c}. : source files for struct and functions of a node in the linked list
