#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>   
#include <time.h>      
#include <unistd.h>
#include "cola.h"
#include "mpi.h"


#define MASTER 0
#define INIT_CAR 1
#define END_CAR 10
#define INIT_TRUCK 11
#define END_TRUCK 27

#define PETICION 0
#define ENTRAR 1
#define SALIDA 2
#define APARCADO 3
#define SALIDA_PARKING 4
#define ENTRADA_OK 5
#define SALIDA_OK 6

#define HORARIO 20 // para usarla en un bucle que simule con iteraciones el horario de apertura de un parking
#define TOPE_INFO 5 // tope maximo del array donde guardo la información de un vehiculo

/* como vamos a usar un array de 5 posiciones en donde vamos a guardar:
 * [0] plaza coche || primera plaza camion
 * [1] segunda plaza camion
 * [2] planta en donde este aparcado el vehiculo
 * [3] matricula
 * [4] tipo de maniobra (1 entrar 2 salir 5 entrada realizada 6 salida realizada)
 */

/* la operación reservar_mem_info_vehiculo, se va a encargar de reservar el espacio 
 * necesario para poder guardar la información necesaria de aquellos vehiculos que estén
 * esperando primeros en la cola de acceso y en la de salida del parking
 */
 
void reservar_mem_info_vehiculo(int **first){
	(*first) = malloc(sizeof(int)*TOPE);
}

void abrir (int ***master,int plz, int plnt){
int i;

	//Estimo el número de plantas que tendrá el parking
	(*master) = (int **) malloc(sizeof(int*)*plnt);
		for(i = 0 ; i < plnt ; ++i){
		// Cuantas plazas habrá por planta
			(*master)[i] = (int*) malloc(sizeof(int)*plz);
		}
		
	printf("Parking abierto\n");	
}

void cerrar(int ***master, int plnt){
int i;
	for(i = 0;i < plnt; i++){
		free((*master)[i]);
	}
	
	free((*master));
}

void inicializar (int ***master,int plz, int plnt){
int i,j;
	for(i = 0;i < plnt;++i){
		for(j = 0;j< plz;++j){
			(*master)[i][j] = 0;
		}
	}
}
			

void imprimir_parking(int **master,int p_l,int plz,int plnt){
int i,j;
	fprintf(stdout,"Parking:\n");
	for(i = 0;i < plnt;++i ){
		fprintf(stdout,"Planta %d ->",i);
		for(j = 0;j < plz; ++j){
			fprintf(stdout,"[%d] ",master[i][j]);
		}
		fprintf(stdout,"\n");
	}
	
	fprintf(stdout,"Plazas totales: %d \n",(plnt*plz));
	fprintf(stdout,"Plazas libres:  %d  \n",p_l);
		
}


/*
 * copio los valores de vehiculo[5], o de primero_en_acceder, o de primero_en_salir a aux para que al final de cada operación 
 * se imprima un mensaje por pantalla acerca de la entrada o salida del vehiculo 
 */
void copiar_valores(int datos[TOPE_INFO], int **salida){
int i;
	for(i = 0;i < TOPE_INFO; i++){
		(*salida)[i] = datos[i];
	}
}

void estacionar_coche (int ***master,int *p_l,int plz, int plnt, int datos[TOPE_INFO]){
int i,j,aparcado = 0;
int pln_vehiculo = -1;
int plz_coche = -1;

			
	for(i = 0;i < plnt;i++){
		//printf(" ESTAS EN LA PLANTA %d \n",i);
		for(j = 0; j < plz;j++){
			if((*master)[i][j] == 0){
				pln_vehiculo = i;
				plz_coche  = j;
				(*master)[i][j] = datos[3];
				--(*p_l);
				aparcado = 1;
				printf("El coche %d ha aparcado en la plaza %d de la planta %d\n",datos[3],plz_coche,pln_vehiculo);
			}

			if(aparcado == 1)
				break;
					
		}
		if(aparcado == 1)
			break;
	}
	
						
			
			
	if(aparcado == 1){
		datos[0] = plz_coche;
		datos[2] = pln_vehiculo;
		datos[4] = ENTRADA_OK;
		MPI_Send(datos,5,MPI_INT,datos[3],APARCADO,MPI_COMM_WORLD);
		
	}
}

void estacionar_camion(int ***master,int *p_l, int plz,int plnt,int datos[TOPE_INFO]){
int i,j;
int plz_camion_1 = -1;
int plz_camion_2 = -1;
int pln_camion = -1;
int aparcado = 0;

	for(i = 0;i < plnt;++i){
		for(j = 0;j < plz;++j){
			if(((*master)[i][j] == 0)&&((*master)[i][j+1] == 0)){
				pln_camion = i;
				plz_camion_1 = j;
				plz_camion_2 = j+1;
				
				(*master)[i][j] = datos[3];
				(*master)[i][j+1] = datos[3];
				
				(*p_l) = (*p_l)-2;
				
				aparcado = 1;
			}
			
			if(aparcado == 1){
				break;
			}
		}
		
		if(aparcado == 1){
			break;
		}
	}
	
	if(aparcado == 1){
		datos[0] = plz_camion_1;
		datos[1] = plz_camion_2;
		datos[2] = pln_camion;
		datos[4] = ENTRADA_OK;
		MPI_Send(datos,5,MPI_INT,datos[3],APARCADO,MPI_COMM_WORLD);
	}
}
/*
 * Debido a problemas surgidos durante las pruebas de ejecución 
 * con las operaciones individuales de estacionar_coche y estacionar_camion
 * he decidido crear una operación genérica que por dentro compruebe a partir
 * del numero de matricula si el vehiculo que quiere estacionar es un coche 
 * o un camión 
 */
void estacionar_vehiculo(int ***master,int *p_l,int plz,int plnt,int datos[TOPE_INFO]){
int i,j;
int aparcado = 0;// variable que simula un booleano == false
	
	if((datos[3] >= INIT_CAR)&&(datos[3] <= END_CAR)){ //comprobación de si el vehiculo es un coche
		for(i = 0; i < plnt;i++){
			for(j = 0;j < plz;j++){
				if((*master)[i][j] == 0){ // si hay una plaza libre guardare los valores de la plaza y la planta en datos
					(*master)[i][j] = datos[3];
					datos[0] = j;
					datos[2] = i;
					--(*p_l); // decremento las plazas libres
					aparcado = 1; //aparcado == true
				}
				
				if(aparcado == 1)
					break; // si ya he aparcado rompo el primer for
			}
			
			if(aparcado == 1)
				break; // si ya he aparcado rompo el segundo for
		}	
	}else if((datos[3] >=INIT_TRUCK)&&(datos[3] <= END_TRUCK)){// comprobacion de si el vehiculo es un camión
		for(i = 0;i < plnt;i++){
			for(j = 0;j < plz;j++){
				if(((*master)[i][j] == 0)&&((*master)[i][j+1] == 0)){ // si encuentro dos plazas consecutivas y en la misma planta puedo aparcar el camión
					(*master)[i][j] = datos[3];
					(*master)[i][j+1] = datos[3];
					//guardo los datos de información acerca de la ubicación del camión en el parking
					datos[0] = j;
					datos[1] = j+1;
					datos[2] = i;
					(*p_l) = (*p_l)-2; // decremento en dos el total de  plazas libres 
					aparcado = 1;
				}
				
				if(aparcado == 1)
					break;
					
			}
				if(aparcado == 1)
					break;
					
		}
			
	}

	if(aparcado == 1){ // si el vehiculo ha aparcado digo que la entrada ha sido realizada con exito y le paso el mensaje al esclavo (camion||coche) identificado por su matricula (datos[3])
			datos[4] = ENTRADA_OK;
			MPI_Send(datos,5,MPI_INT,datos[3],APARCADO,MPI_COMM_WORLD);
	}
	
	
}

/* liberar_plazas realiza la función inversa de estacionar_vehiculo
 * pero en este caso se trata de una operación rápida, ya que a partir
 * de la información almacenada en el array de 5 posiciones "datos"
 * podemos acceder directamente a la posición exacta de la matriz (parking)
 * donde está estacionado el vehiculo que quiere salir del parking.
 * Una vez que hemos sacado al vehiculo del parking en datos[4] le ponemos un valor 6
 * para indicar que la operación se realizo con éxito
 * y le enviamos al esclavo(coche||camion) un mensaje para indicarle que puede salir del parking)
 */ 

				
void liberar_plazas(int ***master,int *p_l,int datos[TOPE_INFO]){ 
		if((datos[3] >= INIT_CAR)&&(datos[3] <= END_CAR)){
			(*master)[datos[2]][datos[0]] = 0;
			++(*p_l);
		}else if((datos[3] >=INIT_TRUCK)&&(datos[3] <= END_TRUCK)){
			(*master)[datos[2]][datos[0]] = 0;
			(*master)[datos[2]][datos[1]] = 0;
			(*p_l) = (*p_l)+2;
		}
		
		datos[0] = -1;
		datos[1] = -1;
		datos[2] = -1;
		datos[4] = SALIDA_OK;
		MPI_Send(datos,5,MPI_INT,datos[3],SALIDA_OK,MPI_COMM_WORLD); 	
			
}			

void liberar_plaza_coche(int ***master,int *p_l,int plz, int plnt,int datos[TOPE_INFO]){
int i,j,libre = 0;	
	for(i = 0;i < plnt;i++ ){
		for(j = 0; j < plz;j++){
			if((*master)[i][j] == datos[3]){			
				(*master)[i][j] = 0;
				libre = 1;
				++(*p_l);
			}
			if(libre == 1){
				break;
			}	
		}
		
		if(libre == 1){
			break;
		}
	}
	
	if(libre == 1){
		datos[0] = -1;
		datos[2] = -1;
		datos[4] = SALIDA_OK;
		fprintf(stdout,"El coche %d a desocupado la plaza\n",datos[3]);
		MPI_Send(datos,5,MPI_INT,datos[3],SALIDA_OK,MPI_COMM_WORLD);
	}

}

void liberar_plaza_camion(int ***master,int *p_l,int plz, int plnt, int datos[TOPE_INFO]){
int i,j;
int libre = 0;

		for(i = 0;i < plnt;++i){
			for(j = 0; j < plz;++j){
				if(((*master)[i][j] == datos[3])&&((*master)[i][j+1] == datos[3])){
					(*master)[i][j] = 0;
					(*master)[i][j+1] = 0;
					libre = 1;
					(*p_l) = (*p_l)+2;
				}
				
				if(libre ==1){
					break;
				}	
				
			}
			
			if(libre == 1){
				break;
			}
				
		}
		
		if(libre == 1){
			datos[0] = -1;
			datos[1] = -1;
			datos[2] = -1;
			datos[4] = SALIDA_OK;
			MPI_Send(datos,5,MPI_INT,datos[3],SALIDA_OK,MPI_COMM_WORLD);
		}
}

int main (int argc, char *argv[]){
int plazas,plantas = 1;
int vehiculo[5];
int i = 0;

int **parking;
int free_places = 0;
Queue puerta_acceso;
Queue puerta_salida;
int *primero_en_acceder; // guardo la información del primer vehiculo que este esperando en la cola para entrar al parking cuando este este completo.
int *primero_en_salir; // guardo la información del primer vehiculo que va a querer salir del parking o del primero que está en la cola de salida del parking
int *aux; // uso aux para copiar la información del vehiculo que ha entrado o ha salido para imprimirla por pantalla una vez que se haya completada la operación...

MPI_Status estado;
//MPI_Request request;

	//apartado c
	if((argc != 0)&&(argv[1] != NULL)){ // el ejecutable del master debe recibir si o si parametros de entrada para poder funcionar
		plazas = atoi(argv[1]);// convierto con la función "atoi" lo almacenado en la posicion 2 de argv a entero para saber cuantas plazas va a tener el parking
		
		if(argv[2] != NULL){ // si la posición 3 de argv tiene algun valor que no sea NULL
			plantas = atoi(argv[2]);// lo convertiré a entero con "atoi" para saber cuantas plantas va a tener el parking, si no por defecto tendrá 1
		}
	//fin apartado c
	
		/*operaciones de inicialización*/
		abrir(&parking,plazas,plantas); //creo las dimensiones del parking
		reservar_mem_info_vehiculo(&primero_en_acceder); //creo la variable que guardara la info del primero vehiculo que este esperando para entrar en caso de que no haya sitio en el parking 
		reservar_mem_info_vehiculo(&primero_en_salir); // creo la variable que guarda la info del primer coche que este esperando para salir del parking
		reservar_mem_info_vehiculo(&aux); // creo la variable auxiliar para copiar info de vehiculos
		crear_cola_vacia(&puerta_acceso); // creo la cola de acceso
		crear_cola_vacia(&puerta_salida); // creo la cola de salida
		free_places = (plantas*plazas); // establezco el numero total de plazas libres iniciales 
		inicializar(&parking,plazas,plantas); // inicializo todas las posiciones de la matriz(parking) a 0 para indicar que estan libres
		imprimir_parking(parking,free_places,plazas,plantas);
		/*fin operaciones de inicialización*/
		
		MPI_Init(&argc,&argv);
		
		
		
			
		while(1){
			MPI_Recv(vehiculo, 5, MPI_INT, MPI_ANY_SOURCE, PETICION ,MPI_COMM_WORLD, &estado); // master recibe mensaje de petición de un slave determinado 	
	      //MPI_Irecv(vehiculo, 5, MPI_INT, MPI_ANY_SOURCE, PETICION,MPI_COMM_WORLD, &request);
			//master comprueba la petición ENTRAR = 1 SALIDA = 2
			if(vehiculo[4] == ENTRAR){ 
				if(free_places > 0){ // si ha plazas libres
					if(longitud_cola(puerta_acceso) != 0){ // si hay vehiculos esperando para entrar 
						insertar_en_cola(vehiculo,&puerta_acceso); // inserto por el final el slave determinado que acaba de mandar la peticion
						primero_en_acceder = primero_de_la_cola(puerta_acceso); // saco el primer vehiculo de la cola de acceso 
						//MPI_Send(primero_en_acceder,5,MPI_INT,primero_en_acceder[3],ENTRADA_OK,MPI_COMM_WORLD);
						estacionar_vehiculo(&parking,&free_places,plazas,plantas,primero_en_acceder); // y lo estaciono
						eliminar_de_la_cola(&puerta_acceso); // una vez estacionado lo borro de la cola de acceso
						copiar_valores(primero_en_acceder,&aux); // copio los valores del vehiculo que era el primero esperando en aux para imprimirlos por pantalla
					}else{
						//MPI_Send(vehiculo,5,MPI_INT,vehiculo[3],ENTRADA_OK,MPI_COMM_WORLD);
						estacionar_vehiculo(&parking,&free_places,plazas,plantas,vehiculo); // si hay plazas y la cola de espera esta vacia puedo estacionar el slave determinado que mando la peticion al master
						copiar_valores(vehiculo,&aux); // copio sus valores de estacionamiento y matricula para imprimirlos por pantalla
					}
					
					fprintf(stdout,"ENTRADA: Vehiculo %d aparca en la plaza %d de la planta %d. Plazas libres: %d\n",aux[3],aux[0],aux[2],free_places);	
					
				}else{// si el parking esta completo
					insertar_en_cola(vehiculo,&puerta_acceso); // inserto al vehiculo(slave determinado) en la cola	
				}
			}
			
			if(vehiculo[4] == SALIDA){ //si la petición recibida por el master es de salida haré:
				if(longitud_cola(puerta_salida) != 0){// si la cola de salida no esta vacía
					insertar_en_cola(vehiculo,&puerta_salida);// inserto por el final al vehiculo(slave determinado)
					primero_en_salir = primero_de_la_cola(puerta_salida);//saco al primero de la cola de salida
					liberar_plazas(&parking,&free_places,primero_en_salir); // le saco del parking
					eliminar_de_la_cola(&puerta_salida);// le elimino de la cola de salida
					copiar_valores(primero_en_salir,&aux);// copio sus valores en aux para imprimir la información por pantalla
				}else{// si la cola de salida está vacía
					liberar_plazas(&parking,&free_places,vehiculo);//libero la plaza del vehiculo(slave determinado)
					copiar_valores(vehiculo,&aux);//copio sus valores en aux para imprimir la información por pantalla
				}
				
				fprintf(stdout,"SALIDA: Vehiculo %d saliendo. Plazas libres: %d\n",aux[3],free_places);
				
			}
			
		
			
			fprintf(stdout,"Estado actual del parking: \n");
			printf("\n\n");
			imprimir_parking(parking,free_places,plazas,plantas); // en cada iteración informo del estado global del parking
			printf("\n\n");
			
			
			
		}
		
		MPI_Finalize(); 
		liberar_cola_de_memoria(&puerta_acceso);//libero cola de entrada
		liberar_cola_de_memoria(&puerta_salida);//libero cola de salida
		free(primero_en_acceder);//libero la variable primero de la cola de entrada
		free(primero_en_salir);// libero la variable primero de la cola de salida
		free(aux);// libero aux
		cerrar(&parking,plantas);// libero la memoria que he reservado para crear el parking	
			
	
	return 0;
}

}


