#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>   
#include <time.h>   
#include <mpi.h>    
#include <unistd.h>

#define TRUCK_PUERTA 0
#define PETICION_ENTRADA_CAMION 1
#define PETICION_SALIDA_CAMION 2
#define CAMION_APARCADO 3
#define CAMION_HA_SALIDO 4
#define ENTRADA_CAMION_OK 5
#define SALIDA_CAMION_OK 6

/*
#define PETICION 0
#define ENTRAR 1
#define SALIDA 2
#define APARCADO 3
#define SALIDA_PARKING 4
#define ENTRADA_OK 5
#define SALIDA_OK 6
*/

#define TIME_MAX_TRUCK 10



int main(int argc, char *argv[]){
int datos[5];
int matricula;
int plz_camion_1 = -1;
int plz_camion_2 = -1;
int pln_camion = -1;
int tiempo;
MPI_Status e_coche;	
//MPI_Request r_c;

	
	MPI_Init(&argc,&argv);
	
	while(1){
	MPI_Comm_rank(MPI_COMM_WORLD,&matricula);
	datos[0] = -1;
	datos[1] = -1;
	datos[2] = -1;
	datos[3] = matricula;
	datos[4] = PETICION_ENTRADA_CAMION;
	
	fprintf(stdout,"Camion %d pide acceso a la puerta \n",matricula);
	MPI_Send(datos,5,MPI_INT,0,TRUCK_PUERTA,MPI_COMM_WORLD);
	//MPI_Send(primero_en_acceder,MPI_INT,primero_en_acceder[3],ENTRADA_OK,MPI_COMM_WORLD); master levanta la barrera de la entrada;
	//MPI_Recv(&datos,5,MPI_INT,datos[3],ENTRADA_CAMION_OK,MPI_COMM_WORLD,&e_coche);	
	//MASTER ENVIA A SLAVE MPI_Send(datos,5,MPI_INT,datos[3],APARCADO,MPI_COMM_WORLD);
	MPI_Recv(&datos,5,MPI_INT,0,CAMION_APARCADO,MPI_COMM_WORLD,&e_coche);
	srand(time(NULL) * matricula);
	tiempo = rand() % TIME_MAX_TRUCK;
	//fprintf(stdout,"Escucha majo soy el coche %d me voy a sobar %d segundos\n",matricula,tiempo);
	sleep(tiempo);
	//fprintf(stdout,"Majo, soy el camión %d y he aparcado en la plaza %d en la planta %d \n",matricula,datos[0],datos[2]);
	
	datos[4] = PETICION_SALIDA_CAMION;
	
	MPI_Send(datos,5,MPI_INT,0,TRUCK_PUERTA,MPI_COMM_WORLD);
	// MASTER ENVIA A SLAVE MPI_Send(datos,5,MPI_INT,datos[3],SALIDA_OK,MPI_COMM_WORLD);
	MPI_Recv(&datos,5,MPI_INT,0,SALIDA_CAMION_OK,MPI_COMM_WORLD,&e_coche);
	
	//fprintf(stdout,"camión %d sale del parking \n",matricula);
	
	srand(time(NULL) * datos[3]);
	tiempo = rand() % TIME_MAX_TRUCK;
	sleep(tiempo);
	//fprintf(stdout,"Escucha majo soy el camión %d 'I'LL BE BACK' en %d segundos\n",datos[3],tiempo);
	
	}	
    MPI_Finalize();
    return 0;	
}
