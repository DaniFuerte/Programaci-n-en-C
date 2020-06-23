#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h"

int main (int argc, char* argv[]){
   char opcion;
   int N ;
   int salida; 
   
   if((argv[1] != NULL)&&(argv[2] != NULL)&&(argc == 3)){ // comprobación de que nos han pasado bien los argumentos de entrada en la shell "./practica2 h 5"
        
        opcion = argv[1][0];
        N = atoi(argv[2]);
        switch (opcion){
	          case 'h': head(N);
	                    break;
	          case 't': tail(N);
	                    break;
	          case 'l': longlines(N);
	                    break;
              default:  fputs("Operacion invalidada inserte: h-> Head, t-> Tail, l-> Longlines \n",stderr); // si nos pasa una opcion que no se corresponda con h / t / l se ejecutara el default del case
                        break;
         } 
	     salida = 0;
	     
	}else{ // en caso de que nos hayan pasado un argumento mal sacaremos un mensaje por la salida estandar de errores 
	     
	     fputs("Insercion de argumentos fallida. Debes insertar 2 argumentos como maximo: \n",stderr);
	     fputs("\n",stderr);
	     fputs(" * Head -> h + nº de elementos \n",stderr);
	     fputs(" * Tail -> t + nº de elementos \n",stderr);
	     fputs(" * Longlines -> l + nº de elementos \n",stderr);
	     fputs("\n",stderr);
	     
	     salida = 1;
	}
	   
    return salida; //salida = $? ; Si = 0 -> todo ha ido bien ; | el programa no se ha ejecutado como se esperaba;
    
}
