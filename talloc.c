#include <stdlib.h>
#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"

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
    Value *cell = malloc(sizeof(size));
    if (collector == NULL) {
        collector = malloc(sizeof(Value));
        collector->type = NULL_TYPE;
    }
    
    Value *new = malloc(sizeof(Value));
    new->type = CONS_TYPE;
    new->c.car = cell;
    new->c.cdr = collector;
    collector = new;
    return cell;
}

/* 
 * Free all pointers allocated by talloc, as well as whatever memory 
 * you allocated in lists to hold those pointers.
 */
void tfree() {
    Value *cdr1 = collector->c.cdr;
    while (true) {
        if (collector->type == NULL_TYPE) {
            free(collector);
            break;
        }
        printf("%i\n", collector->type);
        free(collector->c.car);
        free(collector);
        
        collector = cdr1;
        cdr1 = collector->c.cdr;
    }
}

/* 
 * Replacement for the C function "exit", that consists of two lines: 
 * it calls tfree before calling exit. It's useful to have later on; 
 * if an error happens, you can exit your program, and all memory is 
 * automatically cleaned up.
 */
void texit(int status) {
    //printf("yes");
}


