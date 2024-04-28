#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "error_manager.h"
#include "sala.h"
#include "gestor_ficheros.h"
#include "misala.h"
#include "errno.h"

bool fflag, cflag, oflag = false;


#define MAX_ID 10
#define MAX_LONGITUD_ID 4

int procesar_orden(int argc, char *argv[])
{
    extern char *optarg;
    extern int optind;
    char opt;
    int capacidad;
    char* ruta;
    while((opt = getopt(argc, argv, "f:c:o:")) != -1)
    {
        switch (opt)
        {
            case 'f':
                fflag = true;
                ruta = optarg;
                if(!strcmp(ruta, "o"))
                {
                    oflag = true;
                }
                break;
            case 'c':
                cflag = true;
                capacidad = atoi(optarg);
                break;
        }
    }
    char* orden = argv[optind]; optind++;

    if(oflag){ruta = argv[optind];optind++;}
    
  

    if(!strcmp(orden, "crea"))
    {
        procesar_crea(ruta, capacidad);

    }else if(!strcmp(orden, "reserva"))
    {
        procesar_reserva(ruta, argc, argv);

    }else if(!strcmp(orden, "anula"))
    {
        procesar_anula(ruta, argc, argv);

    }else if (!strcmp(orden, "estado"))
    {
        procesar_estado(ruta);
    }

}

void verifica_ruta(const char *ruta){
	if(access(ruta, F_OK)==-1){
		fprintf(stderr,"la ruta %s no existe\n",ruta);
		exit(-1);
	}
	if(access(ruta,R_OK)||access(ruta,W_OK)){
		fprintf(stderr,"no se tienen los permisos adecuados\n");
		exit(-1);
	}
}



int procesar_crea(char* ruta, int capacidad)
{
    if(crea_sala(capacidad) < 0){fprintf(stderr,"Error al crear la sala.\n");exit(-1);}
    guarda_estado_sala(ruta, true, oflag);
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}

}
int procesar_reserva(char* ruta, int argc, char *argv[])
{
    verifica_ruta(ruta);
    recupera_estado_sala(ruta);
    int asientos = asientos_libres();
    int personas = argc - optind;
    if (asientos < personas){
    	fprintf(stderr, "no se pudo realizar la reserva, no hay suficientes asientos \n");
    	exit(-1);
    }
    
    for(int i = 0; optind< argc; i++,optind++)
    {
    	
       reserva_asiento(atoi(argv[optind]));
    }
    guarda_estado_sala(ruta, false,oflag);
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}
}

int procesar_anula(char* ruta, int argc, char *argv[])
{
    verifica_ruta(ruta);
    recupera_estado_sala(ruta);
    for(int i = 0; optind< argc; i++,optind++)
    {
    	int ids = atoi(argv[optind]);
    	if(ids>0 && ids < capacidad_sala()){
    		libera_asiento(ids);
    	}else{
    		fprintf(stderr,"el asiento %d no es valido para liberar\n",ids);
    	}
       
    }
    guarda_estado_sala(ruta, false,oflag);
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}
}
int procesar_estado(char* ruta)
{
    verifica_ruta(ruta);
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
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}
    return 0;
    
}
