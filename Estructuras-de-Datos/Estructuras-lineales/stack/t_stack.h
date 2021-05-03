#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../t_element/t_element.h"

#define true  0
#define false 1


typedef struct t_node t_node;
struct t_node {
    t_element   info;
    t_node  *   next;
};

typedef struct t_stack t_stack;
struct t_stack {
    t_node   *    summit;
};


t_stack     new_stack();
void        stack_element(t_stack * stack, t_element element);
int         is_empty(t_stack stack);
t_element   get_summit(t_stack stack);
t_element   unstack_element(t_stack * stack);
void        clear_stack(t_stack * stack);
void        debug_stack(t_stack stack);


