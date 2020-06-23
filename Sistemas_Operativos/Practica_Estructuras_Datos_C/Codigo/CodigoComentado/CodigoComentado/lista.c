#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"



void crearVacia(void){ // post lista inicialemente vacia 
	 lista = NULL;
}

int longitudlista(void){ // pre lista post longitud lista = sumatorio de cada uno de los nodos de la lista
	int longitud=0;
	Lista *paux;
	paux=lista;
	while(paux!=NULL){ // mientras la lista no sea vacia 
		paux=paux->next; // pasa al siguiente nodo incrementando el contador "longitud" en una unidad
		longitud++;
	}
	return longitud;
	
	
	
}
void insertar(char *cadena){// post inserta un nuevo elemento en la lista
	 Lista *nuevo;
	 nuevo = malloc(sizeof(Lista));// reservo memoria
	 strcpy(nuevo->info,cadena);// copio el elemento en el nuevo nodo
	 nuevo->next = lista;// el campo siguiente de nuevo  apunta a lista
	 lista = nuevo;// a lista apunta al nuevo nodo
}

void insertarOrdenado(char *cadena){// post inserta de forma ordenada en la lista en funcion de la longitud de la cadena
	 Lista *nuevo;
	 Lista *paux;
	 nuevo = malloc(sizeof(Lista));
	 strcpy(nuevo->info,cadena);
	 nuevo->next=NULL;
	
 
      if (lista == NULL || strlen(lista->info) <= strlen(cadena)){// si la lista esta vacia o la longitudo del nuevo elemento elemento es mayor que la del primero elemento de la lista 
         nuevo->next = lista; 
         lista = nuevo;// el nuevo elemento sera el primer elemento de la lista
      }else {
		paux=lista;
         while (paux->next != NULL && strlen(paux->next->info) > strlen(cadena)){// si no recorro la lista hasta dar con un elemento ya existene en la lista cuya longitud sea menor que la del nuevo elemento
            paux = paux->next;
          }
 
         nuevo->next = paux->next;
         paux->next = nuevo; // y lo inserto por delante del elemento que es menor que el nuevo elemento 
      }
		
	 

}

void insertarFinal(char *cadena){// post inserta un nuevo elemento por el final de la lista 
	 Lista *nuevo;
	 Lista *paux;
	 nuevo = malloc(sizeof(Lista));
	 strcpy(nuevo->info,cadena);
	 nuevo->next = NULL;
	 
	 if(lista == NULL)// si la lista esta vacia -> el nuevo nodo sera el primer nodo de la lista
	          lista = nuevo;
	 else{// | recorro la lista hasta llegar al final de la misma e inserto el nuevo nodo
		  paux = lista;
		  while(paux->next != NULL)
		        paux = paux->next;
		  paux->next = nuevo;
	 }
}
		  
void borrarElemento (char *cadena){// pre recibe un elemento  post busca el elemento en la lista y si existe lo borra
	 Lista *pact;
	 Lista *pant;
	 int encontrado;
	 
	 if(lista != NULL){
		   pant = NULL;
		   pact = lista;
		   while((pact != NULL)&&(encontrado == 0)){
	              if(pact->info == cadena)
					   encontrado = 1;
				  else{
				       pant = pact; 
				       pact = pact->next;
				       
		          }
		   
            }
     }
       
     if(encontrado != 0){
		                 if(pant == NULL)
		                    pant = lista->next;
		                 else
		                     pant->next = pact->next;
     }
     
     free(pact);
     	        
} 	      
		    
void mostrarLista(void){// post muestra todos los elementos de una lista
	 Lista * paux;
	 
	 if(lista != NULL){
		   paux = lista;
		   
		   while(paux != NULL){
			     printf("%s",paux->info);
			     paux = paux->next;
		   }
      }
     
}

void destruir(void){// post destruye la lista por completo
	Lista *paux;
	 while(lista != NULL){// recorre la lista liberando memoria con la funcion free 
		paux=lista;
		lista = lista->next;
		free(paux);
	 }
}
void mostrarUltimos(int n){// pre recibe una lista y un entero n post muestra los n ultimos elementos de la lista 
		int contador;
		Lista *paux;
		if (longitudlista()<= n)// Si la longitud de la lista es menor que el entero n -> muestra toda la lista 
			mostrarLista();
		else{
			contador=longitudlista()-n;// | calculo la diferencia de elementos que se deben de descartar 
			paux=lista;
			while(contador>0){ // recorro la lista descartando los elementos que no vamos a mostrar
				paux=paux->next;
				--contador;
			}
			while(paux!=NULL){// una vez descartados los primeros elementos de la lista continuo recorriendola en este caso mostrando los n ultimos elementos
				printf("%s",paux->info);
				paux=paux->next;
			}
			
		}
	
}

void mostrarPrimeros(int n){// pre recibe una lista y un entero  post muestra los n primeros elementos . FUNCION CREADA PARA LONGLINES
	 Lista *paux;
	 paux = lista;
	 while((paux != NULL)&&(n > 0)){//mientras que no haya llegado al final de la lista y que n sea mayor que 0 mostrare los n primeros elementos
		    printf("%s",paux->info);
		    paux = paux->next;
		    n--;
     }
}


	  
