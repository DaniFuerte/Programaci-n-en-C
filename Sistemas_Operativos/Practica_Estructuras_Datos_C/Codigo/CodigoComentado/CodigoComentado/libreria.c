#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

enum{
	 TOPE = 1024
};

char buffer[TOPE]; // buffer de lectura que se encargara de volvar la información del fichero de la entrada estandar "stdin"

int head (int n){ // imprime los n primeros elementos
	int i;

	for (i = 0; i < n ; ++i){ // mientras que i sea menor que los n primeros elementos  
		if (fgets(buffer,TOPE,stdin)==NULL)// leere de la entrada estandar con el buffer siempre y cuando el elemento leido de  stdin sea distinto de NULL o su longitud no supere los 1024 B 
			break; // si el elemento leido  es NULL rompo el búcle
		printf("%s",buffer); // si todo ha ido bien saco el  elemento almacenado en el buffer por salida estandar
	}
	
	return 0; 
}	 
int tail (int n){// imprime los n ultimos numeros . Necesitare una ED auxiliar, en este caso voy a usar una lista simple enlazada.
	crearVacia();// me creo la lista inicialmente apuntando a NULL o ListaVacia
	for( ; ; ){ // búcle infinito el cual sólo se romperá o finalizara si:
		if(feof(stdin))// he llegado a la marca fin de fichero del fichero stdin
			break;

	     	if (fgets(buffer,TOPE,stdin)==NULL)// o el elemento leido es un elemento vacio
			break;
		insertarFinal(buffer);// en caso contrario mientras no haya llegado al final de fichero insertare los elementos de la lista por el final para mantener el orden en el que fueron leidos en cada iteración

	}
		
	mostrarUltimos(n); //una vez que terminó el búcle mostrare los n ultimos elementos de la lista
	destruir();// y liberare la memoria utilizada con la lista
	
	return 0;
}	

int longlines(int n){// imprime los n elementos mas largos 
	crearVacia();
	for( ; ; ){// búcle infinito que se rompera con la marca fin de fichero
		if(feof(stdin))// si es fin de fichero entonces sal del búcle
		    break;

		 fgets(buffer,TOPE,stdin); // lee de entrada en estandar y vuelva el elemento en el buffer
		 insertarOrdenado(buffer); // insertame de forma ordenada el elemento almacenado en el buffer de lectura

    }
    
    mostrarPrimeros(n); //muestrame los n primeros elementos mas largos
    destruir();// libera memoria 
    
    return 0;
}
   
	
