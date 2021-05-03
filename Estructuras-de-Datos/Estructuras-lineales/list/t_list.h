#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../t_element/t_element.h"

#define true  1
#define false 0

typedef struct t_node t_node;
struct t_node {
    t_element info;
    t_node *  next;
};

typedef struct t_list t_list;
struct t_list {
    t_node * head;
};

t_list      new_list ();
void        add_element (t_list * list, t_element e);
t_element   get_head_element (t_list list);
int         is_empty (t_list list);
void        add_element_final   (t_list * list, t_element e);
void        delete_element   (t_list * list, t_element e);
t_list      concatenate     (t_list list1, t_list list2);
void        clear_list      (t_list * list);
void        debug_list      (t_list list);
