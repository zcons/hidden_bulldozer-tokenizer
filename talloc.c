#include <stdlib.h>
#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"

// A global variable that is a linked list that stores the pointer's
// of all variables that are malloc'ed in the program.
Value *collector;

/* 
 * Replacement for malloc that stores the pointers allocated. It 
 * should store the pointers in some kind of list; a linked list 
 * would do fine, but insert here whatever code you'll need to do so; 
 * don't call functions in the pre-existing linkedlist.h. Otherwise 
 * you'll end up with circular dependencies, since you're going to 
 * modify the linked list to use talloc.
 */
void *talloc(size_t size) {
    
    // If collector is set to NULL, this means the garbage collector
    // is empty or has been empty and needs to be initialized. We
    // its type equal to NULL_TYPE, to let tfree() know that this
    // is the end of the list.
    if (collector == NULL) {
        collector = malloc(sizeof(Value));
        collector->type = NULL_TYPE;
    }
    
    // Creates a temporary CONS_TYPE value node that holds the
    // pointer for the l-value that calls talloc in its car and
    // holds the rest of the list in its cdr. Then resets collector
    // to equal this temporary node, in order to increase the
    // garbage collector.
    Value *new = malloc(sizeof(Value));
    new->type = CONS_TYPE;
    new->c.car = malloc(size);
    new->c.cdr = collector;
    collector = new;
    
    // Return the pointer of the car, where this value's information
    // will be stored.
    return collector->c.car;
}

/* 
 * Free all pointers allocated by talloc, as well as whatever memory 
 * you allocated in lists to hold those pointers.
 */
void tfree() {
    
    // Stores the value of the cdr of collector.
    Value *cdr;
    
    // Uses a while loop to parse through the garbage collector
    // in order to free all the memory in heap.
    while (true) {
        
        // Checks to make sure the collector is initialized, if it is
        // not then break from the while loop as ther is nothing to
        // free.
        if (collector == NULL) {
            break;
        }
        
        // Checks to see if the while loop has reached the end of
        // collector. If it has free collector and set equal to NULL
        // in case there are more talloc's in the program. Thus, 
        // allowing the collector to be reinitialized.
        if (collector->type == NULL_TYPE) {
            free(collector);
            collector = NULL;
            break;
        }
        
        // Once the collector has been checked for its initialization
        // or length, free the car of the collector. Then, reset the
        // the cdr of collector in order to parse down through the 
        // list. Then free the collector and reset it to the cdr.
        free(collector->c.car);
        cdr = collector->c.cdr;
        free(collector);
        collector = cdr;
    }
}

/* 
 * Replacement for the C function "exit", that consists of two lines: 
 * it calls tfree before calling exit. It's useful to have later on; 
 * if an error happens, you can exit your program, and all memory is 
 * automatically cleaned up.
 */
void texit(int status) {
    tfree();
    exit(status);
}


