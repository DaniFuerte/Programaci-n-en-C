#include <stdio.h>
#include <stdlib.h>

#include "t_element.h"

t_element   new_element (int element) {
    t_element e;
    e.element = element;
    return e;    
}

int         get_element (t_element e) {
    return e.element;
}

void        set_element (t_element * e, int element) {
    e->element = element;
}

int         comapre_to_elements (t_element e1, t_element e2) {
    
    int result = eq;
    if(e1.element != e2.element) {
        if(e1.element > e2.element)
            result = gt;
        else
            result = lt;
    }
    
    return result;
    
}

void        debug_element (t_element e) {
    printf("%d | ", e.element);
}
