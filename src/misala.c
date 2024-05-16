#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "error_manager.h"
#include "sala.h"
#include "misala.h"

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
    if(fflag = false){fprintf(stderr,"No se ha especificado el argumento -f\n"); exit(-1);}
    

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

int verifica_ruta(const char *ruta, const char *proceso){

   

    if(!strcmp(proceso, "crea")){
        if(access(ruta, F_OK) == -1) return 0;
        if(oflag){
            return 0;
        }else{
            fprintf(stderr,"no se puede sobreescribir el archivo,no se ha especificado la opcion -o\n");
            exit(-1);
        }
    }
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
    verifica_ruta(ruta, "crea");
    if(crea_sala(capacidad) < 0){fprintf(stderr,"Error al crear la sala.\n");exit(-1);}
    if(guarda_estado_sala(ruta) < 0){
        fprintf(stderr,"Error al guardar la sala.\n");exit(-1);
    }
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}
    return 0;

}
int procesar_reserva(char* ruta, int argc, char *argv[])
{
    verifica_ruta(ruta, "reserva");
    int fd = open(ruta, O_RDONLY);
    if(fd == -1) return ERROR_FICHERO_OPEN;
    int capacidad;
    if((read(fd,&capacidad,sizeof(int))) == -1) return ERROR_FICHERO_READ;
    if(crea_sala(capacidad) < 0){fprintf(stderr,"Error al crear la sala.\n");exit(-1);}
    if(close(fd) == -1)return ERROR_FICHERO_CLOSE;
    recupera_estado_sala(ruta);

    int asientos = asientos_libres();
    int personas = argc - optind;
    if (asientos < personas){
    	fprintf(stderr, "no se pudo realizar la reserva, no hay suficientes asientos \n");
    	exit(-1);
    }
    int asientos_reservados[personas];
    int id_persona;
    for(int i = 0; i < personas; i++,optind++)
    {
        id_persona = atoi(argv[optind]);
        if(id_persona < 0){fprintf(stderr, "error id_persona no valido \n");}
        asientos_reservados[i] = reserva_asiento(id_persona);
    }
    int error = guarda_estadoparcial_sala(ruta, personas, asientos_reservados);
    if(error < 0){
        fprintf(stderr, "error al guardar el estado de la sala\n");
        exit(-1);
    }
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}
    return 0;
}

int procesar_anula(char* ruta, int argc, char *argv[])
{
    verifica_ruta(ruta, "anula");
    int fd = open(ruta, O_RDONLY);
    if(fd == -1) return ERROR_FICHERO_OPEN;
    int capacidad;
    if((read(fd,&capacidad,sizeof(int))) == -1) return ERROR_FICHERO_READ;
    if(crea_sala(capacidad) < 0){fprintf(stderr,"Error al crear la sala.\n");exit(-1);}
    if(close(fd) == -1)return ERROR_FICHERO_CLOSE;
    int numero_asientos = argc - optind;
    int asientos[numero_asientos];
    int it = 0;
    for(int i = 0; i < numero_asientos; i++,optind++)
    {
    	int id_asiento = atoi(argv[optind]);
    	if(id_asiento > 0 && id_asiento <= capacidad_sala()){
            asientos[it] = id_asiento; it++;
    	}else{
    		fprintf(stderr,"el asiento %d no es valido para liberar\n",id_asiento);
    	}
       
    }
    int asientos_final[it];
    for(int i = 0; i< it; i++)
    {
        asientos_final[i] = asientos[i];
    }
    int error = recupera_estadoparcial_sala(ruta, it, asientos_final);
    if(error < 0){
        fprintf(stderr, "error al recuperar el estado de la sala\n");
        exit(-1);
    }
    for(int i = 0; i< it; i++)
    {
        libera_asiento(asientos_final[i]);
    }
    error = guarda_estadoparcial_sala(ruta, it, asientos_final);
    if(error < 0){
        fprintf(stderr, "error al guardar el estado de la sala\n");
        exit(-1);
    }
    if(elimina_sala() < 0){fprintf(stderr,"Error al eliminar la sala.\n");exit(-1);}
    return 0;
}
int procesar_estado(char* ruta)
{
    verifica_ruta(ruta, "estado");
    int fd = open(ruta, O_RDONLY);
    if(fd == -1) return ERROR_FICHERO_OPEN;
    int capacidad;
    if((read(fd,&capacidad,sizeof(int))) == -1) return ERROR_FICHERO_READ;
    if(crea_sala(capacidad) < 0){fprintf(stderr,"Error al crear la sala.\n");exit(-1);}
    if(close(fd) == -1)return ERROR_FICHERO_CLOSE;

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
