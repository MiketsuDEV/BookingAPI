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
        procesar_anula(argc, argv);

    }else if (!strcmp(orden, "estado"))
    {
        procesar_estado(argc, argv);
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


int procesar_crea(int argc, char *argv[])
{

    char* ruta = argv[optind]; optind++;
    verifica_ruta(ruta); 
    int capacidad = atoi(argv[optind]); optind++;
    crea_sala(capacidad);
    guarda_estado_sala(ruta, oflag);
    elimina_sala();

}
int procesar_reserva(int argc, char *argv[])
{
    char* ruta = argv[optind]; optind++;
    verifica_ruta(ruta);
    recupera_estado_sala(ruta);
    int asientos = asientos_libres();
    int personas = argc - optind;
    if (asientos < personas){
    	fprintf(stderr, "no se pudo realizar la reserva, no hya suficientes asientos \n");
    	return 1;
    }
    
    for(int i = 0; optind< argc; i++,optind++)
    {
    	
       reserva_asiento(atoi(argv[optind]));
    }
    guarda_estado_sala(ruta, oflag);
    /*
    strcpy(id_persona[i], argv[optind]);
    num_id++;
    */

}
int procesar_anula(int argc, char *argv[])
{
    char* ruta = argv[optind]; optind++;
    verifica_ruta(ruta);
    recupera_estado_sala(ruta);
    char id_asiento [MAX_ID][MAX_LONGITUD_ID];
    int num_id = 0;
    for(int i = 0; optind< argc; i++,optind++)
    {
    	int ids = atoi(argv[optind]);
    	if(atoi(argv[optind])>0 && atoi(argv[optind])<capacidad_sala()){
    		libera_asiento(ids);
    	}else{
    		fprintf(stderr,"el asiento %d no es valido para liberar",ids);
    	}
       
    }
    guarda_estado_sala(ruta, oflag);
    /*
    strcpy(id_persona[i], argv[optind]);
    num_id++;
    */

}
int procesar_estado(int argc, char *argv[])
{
    char* ruta = argv[optind]; optind++;
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
    return 0;
    elimina_sala();
}
