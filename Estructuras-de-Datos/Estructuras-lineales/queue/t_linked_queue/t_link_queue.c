#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_link_queue.h"

t_link_queue     new_queue () {
    
    t_link_queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    queue.size = 0;
    return queue;
    
}

void        add_element (t_link_queue * queue, t_element e) {
    
    t_node * new = malloc(sizeof(t_node));
    new->info = e;
    new->prev = NULL;
    new->next = NULL;
    
    if(queue->head == NULL) {
        queue->head = new;
    } else {
        new->prev = queue->tail;
        queue->tail->next = new;
    }
    
    queue->tail = new;
    ++queue->size;
    
}

int         is_empty (t_link_queue queue) {
    
    if(queue.head == NULL || queue.size == 0) 
        return true;
    return false;
    
}

int     size           (t_link_queue queue) {
    return queue.size;
}

t_element   get_first (t_link_queue queue) {
    
    t_element exit = new_element(-1);
    if(queue.head != NULL)
        exit = queue.head->info;
    return exit;
    
}

t_element   take (t_link_queue * queue) {
    
    t_element exit = new_element(-1);
    if(queue->head != NULL) {
        exit = queue->head->info;
        queue->head = queue->head->next;
        --queue->size;
    }
    return exit;
    
}

t_link_queue     concatenate (t_link_queue queue1, t_link_queue queue2) {
    
    t_link_queue result = new_queue();
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
            add_element(&result,paux->info);
            paux = paux->next;
        }
    }
    
    return result;
    
}

t_link_queue     concatenate_reverse (t_link_queue queue1, t_link_queue queue2) {
    
    t_link_queue reverse = new_queue();
    t_node * paux = NULL;
    
    if(queue1.head != NULL) {
        paux = queue1.tail;
        while(paux != NULL) {
            add_element(&reverse, paux->info);
            paux = paux->prev;
        }
    }
    
    if(queue2.head != NULL) {
        paux = queue2.tail;
        while(paux != NULL) {
            add_element(&reverse, paux->info);
            paux = paux->prev;
        }
    }
    
    return reverse;
    
}

void        clear_queue (t_link_queue * queue) {
    
    t_node * paux = NULL;
    while(queue->head != NULL) {
        paux = queue->head;
        queue->head = queue->head->next;
        free(paux);
        --queue->size;
    }
    
}

void        debug_queue (t_link_queue queue) {
    
    t_node * paux = NULL;
    if(queue.head != NULL) {
        printf("\n*********************************************");
        printf("\n*                 DEBUG                     *");
        printf("\n*********************************************\n\n");
        paux = queue.head;
        while(paux != NULL) {
            debug_element(paux->info);
            paux = paux->next;
        }
        printf("\n\n");
        printf("SIZE -> %d \n\n", queue.size);
        printf("\n*********************************************\n\n\n");
    } else {
        printf("EMPTY");
    }
    
}
void        debug_queue_reverse (t_link_queue queue) {
    
    t_node * paux = NULL;
    if(queue.head != NULL) {
        printf("\n*********************************************");
        printf("\n*               DEBUG-REVERSE               *");
        printf("\n*********************************************\n\n");
        paux = queue.tail;
        while(paux != NULL) {
            debug_element(paux->info);
            paux = paux->prev;
        }
        printf("\n\n");
        printf("SIZE -> %d \n\n", queue.size);
        printf("\n*********************************************\n\n\n");
    } else {
        printf("EMPTY");
    }
    
}
