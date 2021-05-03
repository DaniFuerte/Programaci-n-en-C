#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_link_queue.h"


int main (int argc, char * argv []) {
    
    t_link_queue q1 = new_queue();
    t_link_queue q2 = new_queue();
    t_link_queue q3 = new_queue();
    
    add_element(&q1,new_element(1));
    add_element(&q1,new_element(1));
    add_element(&q1,new_element(2));
    add_element(&q1,new_element(3));
    add_element(&q1,new_element(5));
    add_element(&q1,new_element(8));
    
    add_element(&q2,new_element(13));
    add_element(&q2,new_element(21));
    add_element(&q2,new_element(34));
    add_element(&q2,new_element(55));
    add_element(&q2,new_element(89));
    add_element(&q2,new_element(144));
    
    debug_queue(q1);
    debug_queue(q2);
    
    debug_queue_reverse(q1);
    debug_queue_reverse(q2);
    
    q3 = concatenate(q1,q2);
    
    debug_queue(q3);
    debug_queue_reverse(q3);
    
    clear_queue(&q1);
    clear_queue(&q2);
    clear_queue(&q3);
    
    return 0;
    
}
