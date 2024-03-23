#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if(!strcmp(input, "salir")) return true;
    
    //procesamos el comando a realizar
    char* comando = strtok(input, " ");
    if(!strcmp(comando, "crear_sala"))
    {
        procesar_crear_sala();

    }else if(!strcmp(comando, "reserva"))
    {
        procesar_reservar_asiento();
        return false;

    }else if(!strcmp(comando, "libera"))
    {
        //procesar_liberar_asiento();
        printf("WIP");
        return false;
    }else if(!strcmp(comando, "estado_asiento"))
    {
        procesar_estado_asiento();
        return false;
    }else if(!strcmp(comando, "estado_sala"))
    {
        procesar_estado_sala();
        return false;
    }else if(!strcmp(comando, "cerrar_sala"))
    {
        procesar_cerrar_sala();
        return false;
    }else if(!strcmp(comando, "ayuda"))
    {
        procesar_ayuda();
    }
    return false;
}
int procesar_crear_sala()
{
    int capacidad_sala = atoi(strtok(NULL, " "));
    int estado_proceso = crea_sala(capacidad_sala);
    switch (estado_proceso)
    {
    case ERROR_SALA_ABIERTA:
        printf("Ya existe una sala creada.\n");
        break;
    case ERROR_SALA_CAPACIDAD:
        printf("La capacidad de la sala no es valida.\n");
        break; 
    case ERROR_MEMORIA:
        printf("Se ha producido un error de memoria.\n");
        break;
    default:
        printf("Se ha creado una sala con %d asientos.\n", estado_proceso);
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
{//WIP
    int id_persona = atoi(strtok(NULL, " "));
    bool persona_sentada = false;
    int estado_proceso;
    for(int i=1; i<=capacidad_sala(); i++)
	{
		if(estado_asiento(i) == id_persona)
        {
            persona_sentada = true;
        }
	}
    return 1;
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
	capacidad_sala() == 0 ? printf("cerrada.\n") : printf("abierta.\n");
	printf("Aforo: %d.\n", capacidad_sala());
	printf("Asientos ocupados: %d.\n", asientos_ocupados());
	printf("Asientos libres: %d.\n", asientos_libres());
	char asiento;
	for(int i=1; i<=capacidad_sala(); i++)
	{
		asiento = estado_asiento(i) <= 0 ? ' ' : 'x';  
		printf("[%c]", asiento);
		if(i % 30 == 0) printf("\n");
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
        break;
    default:
        printf("Se ha cerrado la sala correctamente.\n");
        break;
    }
    return 0;
}
int procesar_ayuda()
{
    printf("Guia de Comandos:\n"
            "-crear_sala \n"
            "-reserva <id_persona>\n"
            "-libera <id_persona>\n"
            "-estado_asiento <id_asiento>\n"
            "-estado_sala\n"
            "-cerrar_sala\n"
            "-salir\n"
            );
    return 0;
}