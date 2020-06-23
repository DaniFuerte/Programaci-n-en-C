#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser.h"

int
hay_background(tline * tok){
return tok->background != 0;
}

int
es_comando_cd(tline *tok){
  return strcmp(tok->commands[0].argv[0],"cd") == 0;
}

void
redireccionar_entrada(char * f){
int file;
    file = open(f,O_RDONLY); // Se abre un fichero en modo lectura, ya que estamos haciendo redireccion de entrada.
    if (file < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(file,0); // Cierra fichero y duplica su valor al descriptor de fichero de stdin 
    close(file);
}
void
redireccionar_salidas(char *f, int n){
int file;
    file = creat(f,0744); // Se crea un fichero con los permisos pertinentes.
    if(file < 0){
       perror("creat");
       exit(EXIT_FAILURE);
    }
   
    dup2(file,n); // Cierra fichero y duplica su valor a n que puede ser o 1 o 2 en función de lo que queramos redireccionar por la salida
    close(file);
}

void
e_comando(tline * tok){
int pid;    
    pid = fork(); // Creamos el proceso para ejecutar el comando con la llamada a sistema fork.
   
    if(pid < 0 ){
       perror("fork"); // pid = 0 proceso hijo, pid >0 proceso padre y < 0 habrá un error.
       exit(EXIT_FAILURE);
    }else if(pid == 0){
/**
* Probando redirecciones con un solo comando ejecutado
* */
    if(tok->redirect_input != NULL)
        redireccionar_entrada(tok->redirect_input); 
    if(tok->redirect_output != NULL)
        redireccionar_salidas(tok->redirect_output,1);
    if(tok->redirect_error != NULL)
        redireccionar_salidas(tok->redirect_error,2);
 
 
    execvp(tok->commands[0].filename,tok->commands[0].argv); // Llamada a sistema que ejecuta el comando
    exit(EXIT_SUCCESS);
    }

    if(!hay_background(tok))
        waitpid(pid,NULL,0); // Si hay background el promp deberá esperar a la finalización del proceso que se esté ejecutando
 
}

void
cerrar_pipes(int **p, int n){
int i,j;
    for(i = 0 ; i < n ;i++){
     for(j = 0; j < 2 ; j++){
       close(p[i][j]);
     }
    }
}

void
esperar_hijos(int *p, int n){
int i;
     for(i = 0 ; i < n ; i++){
       waitpid(p[i],NULL,0);
     }
}

void
e_comandos(tline * tok){
int **pipes; // Matriz dinámica para crear pipes
int *pids;
int i;


    pipes = malloc(sizeof(int *) * tok->ncommands-1); // Me creo en la matriz tantas filas como pipes necesite (el numero de pipes será igual al número de comandos -1)
    
    for(i = 0 ; i < tok->ncommands-1 ; i++){ // Recorro cada una de las filas que he creado dentro de la matriz dinámica 
      pipes[i] = malloc(sizeof(int) * 2); // En cada fila reservo el espacio suficiente para guardar dos enteros, que se corresponderán con un 0 o un 1 (lectura o escritura).
      pipe(pipes[i]); // ''Abre una tubería'' para comunicar los comandos que vamos a utilizar
    }

    pids = malloc(sizeof(int) * tok->ncommands); // Reservo memoria para crear procesos hijos que será igual al número total de comandos que se pasen

    for(i = 0; i < tok->ncommands ; i++){
      pids[i] = fork();
      if(pids[i] < 0){
         perror("fork"); 
         exit(EXIT_FAILURE);
      }else if(pids[i] == 0){
         if(!hay_background(tok)){
            signal(SIGINT,SIG_DFL);
            signal(SIGQUIT,SIG_DFL);
      }
 // Probando redirecciones
         if((i == 0)&&(tok->redirect_input != NULL)){
            redireccionar_entrada(tok->redirect_input);
         }
 
         if(i == tok->ncommands-1){
            if(tok->redirect_output != NULL){
               redireccionar_salidas(tok->redirect_output,1);
            }
            if(tok->redirect_error != NULL){
               redireccionar_salidas(tok->redirect_error,2);
            }          
   
         }
         
         if (tok->ncommands>1) { // Si hay más de un comando
             if(i == 0){ 
                dup2(pipes[i][1],1); // Duplico el valor de escritura de esa casilla del pipe y se pasa por salida estandar 
             }else if( i == tok->ncommands-1){ // Si es el ultimo comando
                dup2(pipes[i-1][0],0); // Se duplica el valor de lectura del pipe anterior y se pasa por entrada estandar
             }else{				 
                dup2(pipes[i][1],1); 
                dup2(pipes[i-1][0],0);
             }
             
             cerrar_pipes(pipes,tok->ncommands-1); // Se cierran los pipes

         }    

         execvp(tok->commands[i].filename,tok->commands[i].argv); // Se ejecuta el comando en la posición i, cogemos el nombre y ejecutamos todos los argumentos que hayamos pasado
         exit(EXIT_SUCCESS);  

     }      
    }
  
  cerrar_pipes(pipes,tok->ncommands-1);

  if(!hay_background(tok)){
     esperar_hijos(pids,tok->ncommands);
  }    

// Liberamos la memoria reservada con malloc
  for(i = 0 ; i < tok->ncommands-1 ; i++)
     free(pipes[i]); // Cerramos la parte correspondiente a malloc sizeof(int) *2

  free(pipes); // Cerramos la matriz dinámica de pipes
  free(pids); // Cerramos el array de los identificadores de procesos.
}

int
main (void){
tline * line;
char buffer[1024];

   signal(SIGINT,SIG_IGN);
   signal(SIGQUIT,SIG_IGN);
   
   
   for(;;){
      //printf(":~$ ");
      printf("===>");
      if (fgets(buffer,1024,stdin)==NULL)
          break;
      if(strlen(buffer) == 1){ // condicion para cubrir el caso en el que el usuario pulsa enter sin haber escrito nada y vuelva a imprimirse por 1 (stdout) el prompt
         continue;
      }else{
         line = tokenize(buffer);
      }  
      if(line->ncommands > 1){
         e_comandos(line);
      }else{
         if(es_comando_cd(line)){
            if((line->commands[0].argc > 1)&&(line->commands[0].argv[1] != NULL)){
               if(chdir(line->commands[0].argv[1])<0)
                  perror(line->commands[0].argv[1]);
               }else{
                  if (chdir(getenv("HOME"))<0)
                    perror("HOME");
               }
         }else{
               e_comando(line);
         }  
      }    
   
   }
   return 0;
}
