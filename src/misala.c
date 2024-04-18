#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "error_manager.h"

int procesar_orden(int argc, char *argv[])
{
    char* orden = argv[1];
    char opt;
    bool fflag, cflag = false;
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
        
            default:
                break;
        }
    }
    for(; optind <  argc; optind ++)
    {
        printf("%s\n", argv[optind]);
    }
    if(fflag) printf("F\n");
    if(cflag) printf("C\n");

    if(!strcmp(orden, "crea"))
    {

    }else if(!strcmp(orden, "reserva"))
    {

    }else if(!strcmp(orden, "anula"))
    {
        
    }else if (!strcmp(orden, "estado"))
    {

    }

}