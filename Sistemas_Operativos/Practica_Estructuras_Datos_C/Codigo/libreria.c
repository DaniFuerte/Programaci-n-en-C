#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

enum{
	 TOPE = 1024
};

char buffer[TOPE];

int head (int n){
	int i;

	for (i = 0; i < n ; ++i){
		if (fgets(buffer,TOPE,stdin)==NULL)
			break;
		printf("%s",buffer);
	}
	
	return 0;
}	 
int tail (int n){
	crearVacia();
	for( ; ; ){
		if(feof(stdin))
			break;

	     	if (fgets(buffer,TOPE,stdin)==NULL)
			break;
		insertarFinal(buffer);

	}
		
	mostrarUltimos(n);
	destruir();
	
	return 0;
}	

int longlines(int n){
	crearVacia();
	for( ; ; ){
		if(feof(stdin))
		    break;

		 fgets(buffer,TOPE,stdin);
		 insertarOrdenado(buffer);

    }
    
    mostrarPrimeros(n);
    destruir();
    
    return 0;
}
   
	
