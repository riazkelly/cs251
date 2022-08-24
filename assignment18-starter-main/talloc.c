#include <stdlib.h>
#include "value.h"
#include <assert.h>
#include <stdio.h>

#ifndef _TALLOC
#define _TALLOC

// Global variable holding the head of the active list (i.e., the linked
// list containing pointers to all of the memory that has been allocated
// via calls to talloc).
Value *activeList = NULL;

// Replacement for malloc that stores the pointers allocated. It should store
// the pointers in a linked list, and you have license here to duplicate code
// that you wrote for linkedlist.c. To be clear, don't actually call functions 
// that are defined in linkedlist.h, because then you'll end up with circular
// dependencies, since you'll be using talloc in linkedlist.c.
void *talloc(size_t size){
    Value *trackerNode = malloc(sizeof(Value));
    Value *newNode = malloc(size);
    trackerNode -> type = CONS_TYPE;
    trackerNode -> c.car = newNode;
    trackerNode -> c.cdr = activeList;
    activeList = trackerNode;
    return newNode;
}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated for purposes of maintaining the active list. Hint: consider 
// that talloc may be called again after tfree is called...
void tfree() {
    Value *temp;
    while (activeList != NULL) {
        assert(activeList -> type == CONS_TYPE && "Input Invalid: Not CONS");
        free(activeList -> c.car);
        temp = activeList -> c.cdr;
        free(activeList);
        activeList = temp;
    }
    free(activeList);
}


// Replacement for the C function 'exit' that consists of two lines: it calls
// tfree before calling exit. It's useful to have later on, since you'll be able
// to call it to clean up memory and exit your program whenever an error occurs.
// Briefly look up exit to get a sense of what the 'status' parameter does.
void texit(int status) {
    tfree();
    exit(status);
}

#endif