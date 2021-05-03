#include <stdio.h>
#include <stdlib.h>

#define eq  1
#define lt -1
#define gt  0

typedef struct t_element t_element;
struct t_element {
    int element;
};

t_element   new_element (int element);
int         get_element (t_element e);
void        set_element (t_element * e, int element);
int         comapre_to_elements (t_element e1, t_element e2);
void        debug_element (t_element e);

