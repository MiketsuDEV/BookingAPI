#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "error_manager.h"
#include "sala.h"
#include "gestor_ficheros.h"
#include "misala.h"

bool fflag, cflag, oflag = false;

int procesar_orden(int argc, char *argv[])
{
    char opt;
   
    while((opt = getopt(argc, argv, "fco")) != -1)
    {
        switch (opt)
        {
            case 'f':
                fflag = true;
                break;
            case 'c':
                cflag = true;
                break;
            case 'o':
                oflag = true;
                break;
        }
    }
    char* orden = argv[optind];
    optind++;
  

    if(!strcmp(orden, "crea"))
    {
        procesar_crea(argc, argv);

    }else if(!strcmp(orden, "reserva"))
    {
        procesar_reserva(argc, argv);

    }else if(!strcmp(orden, "anula"))
    {
        //procesar_anula();

    }else if (!strcmp(orden, "estado"))
    {
        procesar_estado(argc, argv);
    }

}
int procesar_crea(int argc, char *argv[])
{
    char* ruta = argv[optind]; optind++;
    int capacidad = atoi(argv[optind]); optind++;
    crea_sala(capacidad);
    guarda_estado_sala(ruta, oflag);
    elimina_sala();

}
int procesar_reserva(int argc, char *argv[])
{
    char* ruta = argv[optind]; optind++;
}
int procesar_estado(int argc, char *argv[])
{
    char* ruta = argv[optind]; optind++;
    recupera_estado_sala(ruta);
    printf("Aforo: %d.\n", capacidad_sala());
	printf("Asientos ocupados: %d.\n", asientos_ocupados());
	printf("Asientos libres: %d.\n", asientos_libres());
	char asiento;
	for(int i=1; i<=capacidad_sala(); i++)
	{
		asiento = estado_asiento(i) <= 0 ? ' ' : 'x';  
		printf("[%c]", asiento);
		if(i % 20 == 0) printf("\n");
	}
    printf("\n");
	fflush(stdout);
    return 0;
    elimina_sala();
}