#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "main.h"
#include "sala.h"
#include "retardo.h"
#include "error_manager.h"

#define CAPACIDAD_SALA 100
#define MAXIMO_ID 1000
#define ASIENTO 1
#define PERSONA 2
void main(int argc, char *argv[])
{
    if(argc != 2){fprintf(stderr,"Error en el numero de argumentos.\n");exit(-1);}
    int numero_hilos = atoi(argv[1]);
    if(numero_hilos == 0){fprintf(stderr,"Error en el argumento pasado por consola.\n");exit(-1);}

    crea_sala(CAPACIDAD_SALA);
    pthread_t hilos[numero_hilos];
    srand(time(NULL));
    for(int i = 0; i < numero_hilos; i++)
    {
        pthread_create(&hilos[i],NULL,reserva_libera_hilos,(void*)i);
    }
    pthread_t hilo_estado;
    pthread_create(&hilo_estado,NULL,estado_sala_hilo,NULL);
    pthread_join (hilo_estado, NULL);
    for(int i = 0; i < numero_hilos; i++)
    {
        pthread_join (hilos[i], NULL);
    }
    estado_sala();
    exit(0);
}
void* reserva_libera_hilos(void* arg)
{
    int valor_reserva[3];
    //reserva
    for(int i = 0; i < 3; i++)
    {
        valor_reserva[i] = reserva_asiento(id_aleatorio(PERSONA));
        if(valor_reserva[i] == ERROR_SALA_LLENA)
        {
            printf("!!HILO %d ABORTADO !! ERROR RESERVA!!\n", (int)arg);
            pthread_exit(NULL);
        }else
        {
            printf("HILO %d: se ha reservado el asiento %d.\n", (int)arg, valor_reserva[i]);
        }
        pausa_aleatoria(2);
    }
    //libera
    for(int i = 0; i < 3; i++)
    {
        int valor_libera = libera_asiento(valor_reserva[i]);
        if(valor_libera == ERROR_ASIENTO_VACIO)
        {
            printf("!!HILO %d ABORTADO !! ERROR LIBERA!!\n", (int)arg);
            pthread_exit(NULL);
        }else
        {
            printf("HILO %d: se ha liberado el asiento %d.\n", (int)arg, valor_reserva[i]);
        }
        pausa_aleatoria(2);
    }
}
void* estado_sala_hilo(void* arg)
{
    for(int i = 0; i < 3; i++)
    {
        estado_sala();
        pausa_aleatoria(2);
    }
}

int id_aleatorio(int tipo_id)
{
    int id = 0;
    switch (tipo_id)
    {
    case ASIENTO:
        id = rand() % CAPACIDAD_SALA;
        break;
    
    case PERSONA:
        id = rand() % MAXIMO_ID;
        break;
    }
    if(id == 0)id++;
    return id;
}
void estado_sala()
{   printf("HILO ESTADO: ");
    printf("Aforo: %d. ", capacidad_sala());
	printf("Asientos ocupados: %d. ", asientos_ocupados());
	printf("Asientos libres: %d.\n", asientos_libres());
/*    
	char asiento;
	for(int i=1; i<=capacidad_sala(); i++)
	{
		asiento = estado_asiento(i) <= 0 ? ' ' : 'x';  
		printf("[%c]", asiento);
		if(i % 20 == 0) printf("\n");
	}
    printf("\n");
*/
	fflush(stdout);
}