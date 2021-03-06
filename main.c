#include <stdio.h>
#include <string.h>
#include "talloc.h"
#include "linkedlist.h"
#include "value.h"

int main() {
    Value *val1 = talloc(sizeof(Value));
    val1->type = INT_TYPE;
    val1->i = 12;

    Value *val2 = talloc(sizeof(Value));
    val2->type = DOUBLE_TYPE;
    val2->d = 4.3;

    Value *head = makeNull();
    head = cons(val1,head);
    head = cons(val2,head);
    display(head);
    
    int *i = talloc(sizeof(int)*100);
    for (int j = 0; j <100; j++) {
        *(i+j) = 12;
        //printf("%i\n", *(i+j));
    }
    
    Value *reverse2 = reverse(head);

    tfree();
    printf("I can see this.\n");
    Value *val5 = talloc(sizeof(Value));
    texit(1);
    printf("I should never see this.\n");
}
