#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_queue.h"

t_queue     new_queue () {
    
    t_queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
    
}

void        add_element (t_queue * queue, t_element e) {
    
    t_node * new = malloc(sizeof(t_node));
    
    new->info = e;
    new->next = NULL;
    
    if(queue->head == NULL) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    
}

int         is_empty (t_queue queue) {
    
    if(queue.head == NULL)
        return true;
    return false;
    
}

t_element   get_first (t_queue queue) {
    
    t_element exit = new_element(-1);
    if(queue.head != NULL) 
        exit = queue.head->info;
    return exit; 
    
}

t_element   take (t_queue * queue) {
    
    t_element exit = new_element(-1);
    if(queue->head != NULL) { 
        exit = queue->head->info;
        queue->head = queue->head->next;   
    }
    return exit;     
    
}

t_queue     concatenate (t_queue queue1, t_queue queue2) {
    
    t_queue  result = new_queue();
    t_node * paux = NULL;
    
    if(queue1.head != NULL) {
        paux = queue1.head;
        while(paux != NULL) {
            add_element(&result, paux->info);
            paux = paux->next;
        }
        
    }
    
    if(queue2.head != NULL) {
        paux = queue2.head;
        while(paux != NULL) {
            add_element(&result, paux->info);
            paux = paux->next;
        }
        
    }
    
    return result;
    
}

void        clear_queue (t_queue * queue) {
    
    t_node * paux = NULL;
    while(queue->head != NULL) {
        paux = queue->head;
        queue->head = queue->head->next;
        free(paux);
    }
    
}

void        debug_queue (t_queue queue) {
    
    t_node * paux = NULL;
    
    if(queue.head != NULL) {
        paux = queue.head;
        while(paux != NULL) {
            debug_element(paux->info);
            paux = paux->next;
        }
    } else {
        printf("COLA VACIA \n");
    }
    
}
