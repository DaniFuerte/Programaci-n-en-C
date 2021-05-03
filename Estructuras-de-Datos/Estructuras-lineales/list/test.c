#include <stdio.h>
#include <stdlib.h>

#include "t_list.h"

int main (int argc, char * argv []) {
    
    t_list list1 = new_list();
    t_list list2 = new_list();
    t_list list3 = new_list();
    t_element delete = new_element(3);
    
    printf("LISTA 1\n");
    add_element_final(&list1,new_element(5));
    add_element_final(&list1,new_element(1));
    add_element_final(&list1,new_element(5));
    add_element_final(&list1,new_element(0));
    debug_list(list1);
    printf("\n");
    printf("\n");
    
    printf("LISTA 2\n");
    add_element(&list2,new_element(6));
    add_element(&list2,new_element(1));
    add_element(&list2,new_element(3));
    debug_list(list2);
    printf("\n");
    printf("\n");
    
    printf("LISTA 3\n");
    list3 = concatenate(list1,list2);
    debug_list(list3);
    printf("\n");
    printf("\n");
    delete_element(&list3,delete);
    debug_list(list3);
    printf("\n");
    printf("\n");
    
    printf("LISTA 1\n");
    clear_list(&list1);
    debug_list(list1);
    printf("\n");
    printf("\n");
    
    printf("LISTA 2\n");
    clear_list(&list2);
    debug_list(list2);
    printf("\n");
    printf("\n");
    
    printf("LISTA 3\n");
    clear_list(&list3);
    debug_list(list3);
    printf("\n");
    printf("\n");    
    
    return 0;
    
}
