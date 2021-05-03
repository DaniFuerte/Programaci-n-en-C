#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_stack.h"


t_stack     new_stack() {
    
    t_stack s;
    s.summit = NULL;
    return s;
    
}

void        stack_element(t_stack * stack, t_element element) {
    
    t_node * new = malloc(sizeof(t_node));
    new->info = element;
    new->next = stack->summit;
    stack->summit = new;
    
}

int         is_empty (t_stack stack) {
    
    if(stack.summit == NULL)
        return true;
    return false;
    
}

t_element   get_summit(t_stack stack) {
    
    if(stack.summit != NULL) {
        return stack.summit->info;
    }
    return new_element(-1);
}

t_element   unstack_element(t_stack * stack) {
    
    t_element e = new_element (-1);
    if(stack->summit != NULL) {
        e = stack->summit->info;
        stack->summit = stack->summit->next;
    }
    return e;
    
}

void        clear_stack(t_stack * stack) {
    
    t_node * paux = NULL;
    while(stack->summit != NULL) {
        paux = stack->summit;
        stack->summit = stack->summit->next;
        free(paux);
    }
    
}

void        debug_stack (t_stack  stack) {
    
    t_node * paux = NULL;
    
    if(stack.summit == NULL) {
        printf("PILA VACÍA\n");
    } else {
        paux = stack.summit;
        while(paux != NULL) {
            debug_element(paux->info);
            paux = paux->next;
        }
    }
    
}

