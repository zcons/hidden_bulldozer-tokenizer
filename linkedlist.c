#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include <assert.h>


/* 
 * Creates a new NULL_TYPE value node.
 */
Value *makeNull() {
    
    // Allocates space in memory for the null type node and sets its
    // type equal to NULL.
    Value *node = talloc(sizeof(Value));
    node->type = NULL_TYPE;
    return node;
}

/*
 * Creates a new CONS_TYPE value node.
 */
Value *cons(Value *car, Value *cdr) {
    
    // Allocates space in memory for the new node.
    Value *node = talloc(sizeof(Value));
    
    // Points the car and cdr of node to the apporpriate parameters.
    node->c.car = car;
    node->c.cdr = cdr;
    node->type = CONS_TYPE;
    return node;
}

/* 
 * Displays the contents of the linked list to the screen in some
 * kind of readable format.
 */
void display(Value *list) {
    
    // Indicates the beginning of a list.
    printf("[");   
    
    // A temporary variable to keep track of the values in the linked
    // list. Keeps list pointer pointing at list instead of changing 
    // it. Keeps track of car and cdr of temp.
    Value *temp = list;
    Value *car1 = car(temp);
    Value *cdr1 = cdr(temp);
    
    // Used for printing commas.
    int first = 1;
    
    while (true) {
        
        // If temp is of NULL_TYPE, means the linked list is empty.
        // Otherwise decide to print a comma or not.
        if (temp->type == NULL_TYPE) {
            printf("]\n");
            break;
        } else {
            
            // If not the first element in the list print a comma.
            // If it is, reset first.
            if (!first) {
                printf(", ");
            } else {
                first = 0;
            }
        }
        
        // Based on the type print the actual value of the car.
        if (car1->type == INT_TYPE) {
            printf("%i", car1->i);
        } else if (car1->type == DOUBLE_TYPE) {
            printf("%lf", car1->d);
        } else if (car1->type == STR_TYPE) {
            printf("%s", car1->s);
        }
        
        // Reset thee values to parse through the list.
        temp = cdr1;
        car1 = car(temp);
        cdr1 = cdr(temp);
    }
}



/* 
 * Return a new list that is the reverse of the one that is passed 
 * in. No stored data within the linked list should be duplicated; 
 * rather, a new linked list of CONS_TYPE nodes should be created, 
 * that point to items in the original list.
 */
Value *reverse(Value *list) {
    
    // Make a new list called reverse that returns the reverse
    // of the list. make the first node to have type NULL_TYPE
    // to indicate the end of the list.
    Value *reverse = makeNull();
    
    // Similar to display, allows list pointer to not change in order 
    // to parse through the list.
    Value *temp = list;
    while (true) {
        
        // Once temp's type is NULL_TYPE, break, as this indicates 
        // the end of the list.
        if (temp->type == NULL_TYPE) {
            break;
        }
        
        // Cons the cell with reverse, this reverses the list.
        // This is because the first value in list is placed first
        // in reverse and cons places the next value on top of the
        // first value, so on and so on.
        reverse = cons(car(temp), reverse);
        temp = cdr(temp);
    }
    return reverse;
}

/* 
 * Utility to make it less typing to get car value. Use assertions to 
 * make sure that this is a legitimate operation.
 */
Value *car(Value *list) {
    assert(list != NULL);
    return list->c.car;
}

/* 
 * Utility to make it less typing to get cdr value. Use assertions to 
 * make sure that this is a legitimate operation.
 */
Value *cdr(Value *list) {
    assert(list != NULL); 
    return list->c.cdr;
}

/*
 * Utility to check if pointing to a NULL_TYPE value. Use assertions 
 * to make sure that this is a legitimate operation.
 */
bool isNull(Value *value) {
    if (value->type == NULL_TYPE) {
        return 1;
    }
    return 0;
}

/*
 * Measure length of list. Use assertions to make sure that this is a 
 * legitimate operation.
 */
int length(Value *value) {

    // As with display and reverse, point to the same data as value
    // but we don't want to change the pointer of value. Thus,
    // copy the pointer to temp, to parse through the list. 
    Value *temp = value;
    
    // Keeps track of the car, cdr and length.
    Value *car1 = car(temp);
    Value *cdr1 = cdr(temp);
    int length = 0;
    while (true) {    
        // If temp is empty, this means the end of the list has
        // been reached so return the reverse.
        if(temp->type == NULL_TYPE) {
            return length;
        }

        // Increment the length and parse down through value.
        length++;
        temp = cdr1;
        car1 = car(temp);
        cdr1 = cdr(temp);
    }
    return 0;
}


