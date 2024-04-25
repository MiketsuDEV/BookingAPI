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
   
    while((opt = getopt(argc, argv, "fc")) != -1)
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
        //procesar_estado();
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