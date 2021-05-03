#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../t_element/t_element.h"


#define true  0
#define false 1


typedef struct t_node t_node;
struct t_node {
    t_element   info;
    t_node  *   next;
};


typedef struct t_queue t_queue;
struct t_queue {
    t_node  *   head;
    t_node  *   tail;
};


t_queue     new_queue ();
void        add_element (t_queue * queue, t_element e);
int         is_empty (t_queue queue);
t_element   get_first (t_queue queue);
t_element   take (t_queue * queue);
t_queue     concatenate (t_queue queue1, t_queue queue2);
void        clear_queue (t_queue * queue);
void        debug_queue (t_queue queue);
