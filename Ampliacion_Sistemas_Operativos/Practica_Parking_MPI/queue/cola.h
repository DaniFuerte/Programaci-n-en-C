#include <stdio.h>
#include <stdlib.h>

#define TOPE 5

/* TAD Queue compuesto:
 * - Registro Node : campo info (array de 5 posiciones que guardara la info del vehículo x), y un campo siguiente que apuntará al siguiente Nodo
 * - Registro Queue : campo cabecera que apuntara al primer Nodo de la Cola, y campo último que apuntará al último vehículo que haya entrado en la Cola
 */ 


typedef struct Node Node;
struct Node{
	int info[TOPE];
	Nodo *sig;
};

typedef struct Queue Queue;
struct Queue {
	Nodo *head;
	Nodo *tail;
};

void create_empty_queue (Queue *c);
void insert (int n[TOPE], Queue *c);
int * head (Queue c);
void peek (Queue *c);
void dispose_queue (Queue *c);
void print_queue (Queue c);
int length (Queue c);
/*int search (Queue c, int n[TOPE]);*/


/*
 * operación "buscar" al final no nos ha hecho falta
 * la dejamos en el código comentada
 *
 */
