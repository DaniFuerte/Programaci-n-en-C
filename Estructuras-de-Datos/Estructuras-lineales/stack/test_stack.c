#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_stack.h"

int main (int argc, char * argv []) {
    
    t_element unstack;
    t_stack stack = new_stack();
    
    
    stack_element(&stack, new_element(3));
    stack_element(&stack, new_element(1));
    stack_element(&stack, new_element(6));
    printf("\n");
    printf("\n");
    
    debug_stack(stack);
    
    unstack = unstack_element(&stack);
    
    printf("\n");
    printf("\n");
    
    printf("ELEMENT -> ");
    debug_element(unstack);
    
    printf("\n");
    printf("\n");
    
    debug_stack(stack);
    
    printf("\n");
    printf("\n");
    
    return 0;
    
}
