#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

/*
 * la cabecera y el último apuntan a NULL -> se ha creado una cola vacía
 */
void create_empty_queue ( Queue *c){
	(*c).cabecera = NULL;
	(*c).ultimo = NULL;
}
void insert (int n[TOPE], Queue *c){
Node *nuevo;
int i;
	nuevo = malloc(sizeof(Nodo));// reservo el espacio necesario para guardar un nuevo nodo
	for(i = 0; i < TOPE; ++i) // recorro con un for cada una de las posiciones del array que voy a almacenar en el nuevo Nodo
		nuevo->info[i] = n[i];
	nuevo->sig = NULL;
	if((*c).cabecera == NULL){ // si la cola está vacía -> cabecera y último apuntan a nuevo
		(*c).cabecera = nuevo;
		(*c).ultimo = nuevo;
	}else{ // si no -> sólo lo hará último para que se inserte por el final
		(*c).ultimo->sig = nuevo;
		(*c).ultimo = nuevo;
	}
}
int * head (Queue c){ // devuelvo el primer elemento de la cola 
int i;
int *salida = malloc(sizeof(int)*TOPE); // reservo en salida el espacio suficiente (array de 5 posiciones) para guardar la info del primer elemento 
	for(i = 0; i < TOPE; ++i){ // copio con un for cada una de las posiciones de c.cabecera->info en salida
		salida[i] = c.cabecera->info[i];
	}
	
	return salida; // devuelvo el primer elemento de la cola como salida
}
void peek (Queue *c){ 
Nodo *paux;
	if((*c).cabecera != NULL){ // si la cola no está vacía -> elimino el primer elemento de la cola
		paux = (*c).cabecera; // paux apunta al primer elemento
		(*c).cabecera = (*c).cabecera->sig;// la cabecera apunta al siguiente
		free(paux);// me cargo paux
	}
}	

void dispose_queue (Queue *c){ // hace lo mismo que eliminar cola, pero con un búcle para que se destruya toda la estructura
Nodo *paux;
	if((*c).cabecera != NULL){ 
		while((*c).cabecera != NULL){
			paux = (*c).cabecera;
			(*c).cabecera = (*c).cabecera->sig;
			free(paux);
		}
		printf("Cola liberada\n");
	}
}

void print_queue (Queue c){
Node *paux;
int i;
	if(c.cabecera != NULL){
		paux = c.cabecera;
			while(paux != NULL){
				for(i = 0; i < TOPE;++i){	
					printf("%d  ",paux->info[i]);
				}
				printf("\n");
				paux = paux->sig;
			}
	}
}

int length (Queue c){ // la uso para comprobar desde fuera del TAD si la cola está o no vacía si la longitud == 0 -> Cola vacia
int length = 0;
Node *paux;
	if(c.cabecera != NULL){
		paux = c.cabecera;
			while(paux != NULL){
				  ++length;
				  paux = paux->sig;
			}
	}
	
	return length;
}

/*
int buscar(Queue c, int n[TOPE]){
Node *aux;
int i,encontrado = 0;

	if(c.cabecera != NULL){
		aux = c.cabecera;
		while((aux != NULL)&&(!encontrado)){
				for(i = 0;i < TOPE;++i){
					if(aux->info[i] != n[i]){
					   encontrado = 0;
					   break;
					}else{
					   encontrado = 1;
					}
					
			    	}
			    
			    if(encontrado == 0){
					aux = aux->sig;
			    }else if(encontrado == 1){
					break;
			    }		
		}
	}
	
	return encontrado;
}*/
	
	
			    
					
				
				
				
				
				
