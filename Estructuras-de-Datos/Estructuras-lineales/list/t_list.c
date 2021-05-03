#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_list.h"

t_list  new_list () {

    t_list list;
    list.head = NULL;
    return list;
    
}


void    add_element (t_list * list, t_element e) {
    
    t_node * new = malloc(sizeof(t_node));
    new->info = e;
    new->next = list->head;
    list->head = new;
    
}


t_element  get_head_element (t_list list) {
    
    t_element e = new_element (-1);
    if(list.head != NULL)
        e = list.head->info;
    return e;
    
}


int     is_empty (t_list list) {
    
    if(list.head == NULL)
        return true;
    return false;
    
}


void    add_element_final   (t_list * list, t_element e) {
    
    t_node * paux = NULL;
    t_node * new = malloc(sizeof(t_node));
    
    new->info = e;
    new->next = NULL;
    
    if(list->head == NULL)
        list->head = new;
    else {
        paux = list->head;
    
        while(paux->next != NULL)
            paux = paux->next;
    
        paux->next = new;    
    }
}


void    delete_element   (t_list * list, t_element e) {
    
    int found = false;
    t_node * pant = NULL;
    t_node * pact = list->head;
    
    while(pact != NULL && (found == false)) {
        
        if(comapre_to_elements(e,pact->info) == true) {
             found = true;
        } else {
            pant = pact;
            pact = pact->next;
        }        
    }
    
    if(found != false) {
        if (pant == NULL)
            pant = list->head->next;
        else
            pant->next = pact->next;
    }
    
}


t_list  concatenate     (t_list list1, t_list list2) {
    
    t_node * paux = NULL;
    t_list result;
    if(list1.head != NULL) {
        
        paux = list1.head;
        while (paux != NULL) {
            add_element_final (&result, paux->info);
            paux = paux->next;
        }
        
    }
    
    if(list2.head != NULL) {
        
        paux = list2.head;
        while (paux != NULL) {
            add_element_final (&result, paux->info);
            paux = paux->next;
        }
        
    }
    
    return result;
    
}


void    clear_list      (t_list * list) {
    
    t_node * paux = NULL;
    while(list->head != NULL) {
        paux = list->head;
        list->head = list->head->next;
        free(paux);
    }
    
}


void    debug_list      (t_list list) {
    
    t_node * paux = NULL;
    
    if(list.head == NULL) {
        printf("LISTA VACÍA \n");
    } else {
        paux = list.head;
        while(paux != NULL) {
            debug_element(paux->info);
            paux = paux->next;
        }
    }
    
}
