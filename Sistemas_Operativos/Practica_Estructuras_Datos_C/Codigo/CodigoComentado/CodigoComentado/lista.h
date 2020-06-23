#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista Lista;
struct Lista{
	   char  info[1024];
	   Lista *next;
};

Lista *lista;

void crearVacia(void);
void insertar(char *cadena);
void insertarFinal(char *cadena);
void borrarElemento (char *cadena);
void mostrarLista(void);
int longitudlista(void);
void mostrarUltimos(int n);
void mostrarPrimeros(int n);
void destruir(void);
void insertarOrdenado(char *cadena);
void destruir();
