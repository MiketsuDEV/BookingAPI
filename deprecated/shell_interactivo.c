#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell_interactivo.h"
#include "sala.h"
#include "error_manager.h"

void leer_shell()
{
    bool exit = false;
    while(!exit)
    {
        char input[256];
        fgets(input, 256, stdin);
        exit = procesar_input(input);
    }
}

int procesar_input(char* input)
{
    input[strcspn(input, "\n")] = 0; // quitar el salto de linea
    
    //procesamos el comando a realizar
    char* comando = strtok(input, " ");
    if(!strcmp(comando, "ayuda"))
    {
        procesar_ayuda();

    }else if(!strcmp(comando, "reserva"))
    {
        procesar_reservar_asiento();

    }else if(!strcmp(comando, "libera"))
    {
        procesar_liberar_asiento();

    }else if(!strcmp(comando, "estado_asiento"))
    {
        procesar_estado_asiento();
        
    }else if(!strcmp(comando, "estado_sala"))
    {
        procesar_estado_sala();
    
    }else if(!strcmp(comando, "cerrar_sala"))
    {
        if(procesar_cerrar_sala() == true) return true;
    }
    return false;
}
int procesar_crear_sala(char *ciudad, int capacidad)
{
    int estado_proceso = crea_sala(capacidad);
    switch (estado_proceso)
    {
        case ERROR_SALA_ABIERTA:
            printf("Ya hay una sala creada.\n");
            sleep(5);
            exit(1);
            break;
        case ERROR_SALA_CAPACIDAD:
            printf("La capacidad de la sala no es valida.\n");
            sleep(5);
            exit(1);
            break; 
        case ERROR_MEMORIA:
            printf("Se ha producido un error de memoria.\n");
            sleep(5);
            exit(1);
            break;
        default:
            printf("SUCURSAL CREADA\n");
            printf("Nombre: %s.\n", ciudad);
            printf("Capacidad: %d.\n", capacidad);
            procesar_ayuda();
            break;
    }
    return 0;
}
int procesar_reservar_asiento()
{
    int id_persona = atoi(strtok(NULL, " "));
    int estado_proceso = reserva_asiento(id_persona);
    switch (estado_proceso)
    {
        case ERROR_SALA_CERRADA:
            printf("La sala no se ha creado todavia.\n");
            break;
        case ERROR_SALA_LLENA:
            printf("La sala ya esta llena.\n");
            break;
        case ERROR_ID_PERSONA:
            printf("El id de persona no es valido.\n");
            break;
        default:
            printf("Se ha reservado el asiento %d para el id de persona %d.\n",
                    estado_proceso, id_persona);
            break;
    }
    return 0;
}
int procesar_liberar_asiento()
{
    int id_persona = atoi(strtok(NULL, " "));
    int id_asiento = 0;
    bool persona_sentada = false;
    int estado_proceso;
    for(int i=1; i<=capacidad_sala(); i++)
	{
		if(estado_asiento(i) == id_persona)
        {
            persona_sentada = true;
            id_asiento = i;
            break;
        }
	}
    if(persona_sentada = true)
    {
        estado_proceso = libera_asiento(id_asiento);
    }
    switch (estado_proceso)
    {
        case ERROR_SALA_CERRADA:
            printf("La sala no se ha creado todavia.\n");
            break;
        case ERROR_ID_ASIENTO:
            printf("El numero de asiento no es valido.\n");
            break;
        case ERROR_ASIENTO_VACIO:
            printf("El asiento %d esta vacio.\n", id_asiento);
            break;
        default:
            printf("El asiento %d ocupado por el id %d ha sido liberado.\n",
                    id_asiento, estado_proceso);
            break;
    }
    return 0;
}
int procesar_estado_asiento()
{
    int id_asiento = atoi(strtok(NULL, " "));
    int estado_proceso = estado_asiento(id_asiento);
    switch (estado_proceso)
    {
        case ERROR_SALA_CERRADA:
            printf("La sala no se ha creado todavia.\n");
            break;
        case ERROR_ID_ASIENTO:
            printf("El numero de asiento no es valido.\n");
            break;
        case ERROR_ASIENTO_VACIO:
            printf("El asiento %d esta vacio.\n", id_asiento);
            break;
        default:
            printf("El asiento %d esta ocupado por el id de persona %d.\n",
                    id_asiento, estado_proceso);
            break;
    }
    return 0;
}
int procesar_estado_sala()
{
	printf("Estado Sala: ");
	if(capacidad_sala() == ERROR_SALA_CERRADA)
    {
        printf("cerrada.\n");
        return 0;

    }
    printf("abierta.\n");
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
}
int procesar_cerrar_sala()
{
    int estado_proceso = elimina_sala();
    switch (estado_proceso)
    {
        case ERROR_SALA_CERRADA:
            printf("No hay una sala abierta.\n");
            return false;
            break;
        default:
            printf("Se ha cerrado la sala correctamente.\n");
            break;
    }
    return true;
}
int procesar_ayuda()
{
    printf("Guia de Comandos:\n"
            "-reserva <id_persona>\n"
            "-libera <id_persona>\n"
            "-estado_asiento <id_asiento>\n"
            "-estado_sala\n"
            "-cerrar_sala\n"
            );
    return 0;
}