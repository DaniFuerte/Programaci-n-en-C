#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"



void crearVacia(void){
	 lista = NULL;
}

int longitudlista(void){
	int longitud=0;
	Lista *paux;
	paux=lista;
	while(paux!=NULL){
		paux=paux->next;
		longitud++;
	}
	return longitud;
	
	
	
}
void insertar(char *cadena){
	 Lista *nuevo;
	 nuevo = malloc(sizeof(Lista));
	 strcpy(nuevo->info,cadena);
	 nuevo->next = lista;
	 lista = nuevo;
}

void insertarOrdenado(char *cadena){
	 Lista *nuevo;
	 Lista *paux;
	 nuevo = malloc(sizeof(Lista));
	 strcpy(nuevo->info,cadena);
	 nuevo->next=NULL;
	
 
      if (lista == NULL || strlen(lista->info) <= strlen(cadena)){
         nuevo->next = lista;
         lista = nuevo;
      }else {
		paux=lista;
         while (paux->next != NULL && strlen(paux->next->info) > strlen(cadena)){
            paux = paux->next;
          }
 
         nuevo->next = paux->next;
         paux->next = nuevo;
      }
		
	 

}

void insertarFinal(char *cadena){
	 Lista *nuevo;
	 Lista *paux;
	 nuevo = malloc(sizeof(Lista));
	 strcpy(nuevo->info,cadena);
	 nuevo->next = NULL;
	 
	 if(lista == NULL)
	          lista = nuevo;
	 else{
		  paux = lista;
		  while(paux->next != NULL)
		        paux = paux->next;
		  paux->next = nuevo;
	 }
}
		  
void borrarElemento (char *cadena){
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
		    
void mostrarLista(void){
	 Lista * paux;
	 
	 if(lista != NULL){
		   paux = lista;
		   
		   while(paux != NULL){
			     printf("%s",paux->info);
			     paux = paux->next;
		   }
      }
     
}

void destruir(void){
	Lista *paux;
	 while(lista != NULL){
		paux=lista;
		lista = lista->next;
		free(paux);
	 }
}
void mostrarUltimos(int n){
		int contador;
		Lista *paux;
		if (longitudlista()<= n)
			mostrarLista();
		else{
			contador=longitudlista()-n;
			paux=lista;
			while(contador>0){
				paux=paux->next;
				--contador;
			}
			while(paux!=NULL){
				printf("%s",paux->info);
				paux=paux->next;
			}
			
		}
	
}

void mostrarPrimeros(int n){
	 Lista *paux;
	 paux = lista;
	 while((paux != NULL)&&(n > 0)){
		    printf("%s",paux->info);
		    paux = paux->next;
		    n--;
     }
}


	  
