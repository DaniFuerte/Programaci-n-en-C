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
    t_node  *   prev;
};


typedef struct t_link_queue t_link_queue;
struct t_link_queue {
    t_node  *   head;
    t_node  *   tail;
    int         size;
};


t_link_queue     new_queue ();
void        add_element (t_link_queue * queue, t_element e);
int         is_empty (t_link_queue queue);
int         size     (t_link_queue queue);
t_element   get_first (t_link_queue queue);
t_element   take (t_link_queue * queue);
t_link_queue     concatenate (t_link_queue queue1, t_link_queue queue2);
t_link_queue     concatenate_reverse (t_link_queue queue1, t_link_queue queue2);
void        clear_queue (t_link_queue * queue);
void        debug_queue (t_link_queue queue);
void        debug_queue_reverse (t_link_queue queue);
