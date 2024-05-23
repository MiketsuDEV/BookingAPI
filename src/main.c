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
    if(argc != 3){fprintf(stderr,"Error en el numero de argumentos.\n");exit(-1);}
    int numero_hilos_reserva = atoi(argv[1]);
    if(numero_hilos_reserva == 0){fprintf(stderr,"Error en el argumento pasado por consola.\n");exit(-1);}
    int numero_hilos_libera = atoi(argv[2]);
    if(numero_hilos_libera == 0){fprintf(stderr,"Error en el argumento pasado por consola.\n");exit(-1);}

    if(crea_sala(CAPACIDAD_SALA) <= -1){fprintf(stderr,"Error al crear la sala.\n");exit(-1);}
    srand(time(NULL));

    pthread_t hilos_reserva[numero_hilos_reserva];
    pthread_t hilos_libera[numero_hilos_libera];
    for(int i = 0; i < numero_hilos_reserva; i++)
    {
        pthread_create(&hilos_reserva[i],NULL,reserva_hilo,(void*)i);
    }
    for(int i = 0; i < numero_hilos_libera; i++)
    {
        pthread_create(&hilos_libera[i],NULL,libera_hilo,(void*)i);
    }

    pthread_t hilo_estado;
    pthread_create(&hilo_estado,NULL,estado_sala_hilo,NULL);
    pthread_join (hilo_estado, NULL);
    for(int i = 0; i < numero_hilos_reserva; i++)
    {
        pthread_join(hilos_reserva[i], NULL);
    }
    for(int i = 0; i < numero_hilos_libera; i++)
    {
        pthread_join(hilos_libera[i], NULL);
    }

    estado_sala();
    if(elimina_sala() <= -1){{fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}}
    exit(0);
}
void* reserva_hilo(void* arg)
{
    for(int i = 0; i < 3; i++)
    {
        int valor_reserva = reserva_asiento(id_aleatorio(PERSONA));
        if(valor_reserva == ERROR_SALA_LLENA)
        {
            //variable condicion
        }else
        {
            printf("HILO-RESERVA [%d]: se ha reservado el asiento %d.\n", (int)arg, valor_reserva);
        }
        pausa_aleatoria(2);
    }
    
}
void* libera_hilo(void* arg)
{
    
    for(int i = 0; i < 3; i++)
    {
        int valor_libera = libera_asiento(NULL);
        if(valor_libera == ERROR_ASIENTO_VACIO)
        {
           
        }else
        {
            
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