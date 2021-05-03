#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_queue.h"


int main (int argc, char * argv []) {
    
    t_queue q1 = new_queue();
    t_queue q2 = new_queue();
    t_queue fibonacci = new_queue();
    
    printf("\n\n");
    
    printf("COLA 1\n");
    add_element(&q1,new_element(1));
    add_element(&q1,new_element(1));
    add_element(&q1,new_element(2));
    add_element(&q1,new_element(3));
    debug_queue(q1);
    
    printf("\n\n");
    
    printf("COLA 2\n");
    add_element(&q2,new_element(5));
    add_element(&q2,new_element(8));
    add_element(&q2,new_element(13));
    add_element(&q2,new_element(21));
    add_element(&q2,new_element(34));
    add_element(&q2,new_element(55));
    add_element(&q2,new_element(89));
    add_element(&q2,new_element(144));
    debug_queue(q2);
    
    printf("\n\n");
    
    printf("FIBONACCI\n");
    fibonacci = concatenate (q1,q2);
    debug_queue(fibonacci);
    
    printf("\n\n");
    
    clear_queue(&q1);
    clear_queue(&q2);
    clear_queue(&fibonacci);
    
    printf("COLA 1\n");
    debug_queue(q1);
    
    printf("\n\n");
    
    printf("COLA 2\n");
    debug_queue(q2);
    
    printf("\n\n");
    
    printf("FIBONACCI\n");
    debug_queue(fibonacci);
    
    printf("\n\n");
    
    return 0;
    
}
