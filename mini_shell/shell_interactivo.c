#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_interactivo.h"
#include "sala.h"

#define bool int
#define false 0
#define true 1

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
    printf("DEBUG INPUT: %s\n", input);
    if(!strcmp(input, "salir")) return true;
    
    //procesamos el comando a realizar
    char* comando = strtok(input, " ");
    if(!strcmp(comando, "crear_sala"))
    {
        procesar_crear_sala();
        return false;

    }else if(!strcmp(comando, "reserva"))
    {
        procesar_reservar_asiento();
        return false;

    }else if(!strcmp(comando, "libera"))
    {
        procesar_liberar_asiento();
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
        //cerrar_sala();
        return false;
    }
    return false;
}
int procesar_crear_sala()
{
    char* nombre_sala = strtok(NULL, " ");
    int capacidad_sala = atoi(strtok(NULL, " "));
    printf("DEBUG Nombre de la sala: %s\n", nombre_sala);
    printf("DEBUG Capacidad de la sala: %d\n", capacidad_sala);
    crear_sucursal(nombre_sala, capacidad_sala);
    return 0;
}
int procesar_reservar_asiento()
{
    int id_persona = atoi(strtok(NULL, " "));
    reserva_asiento(id_persona);
    printf("DEBUB Reserva para el id_persona: %d\n", id_persona);
    return 0;
}
int procesar_liberar_asiento()
{
    int id_persona = atoi(strtok(NULL, " "));
    for(int i=1; i<=capacidad_sala(); i++)
	{
		if(estado_asiento(i) == id_persona){libera_asiento(i);return 0;}
	}
    return 1;
}
int procesar_estado_asiento()
{
    int id_asiento = atoi(strtok(NULL, " "));
    estado_asiento(id_asiento);
    return 0;
}
int procesar_estado_sala()
{
	printf("\n######################################\n");
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
	printf("\n######################################\n");
	fflush(stdout);
    return 0;
}
int procesar_cerrar_sala()
{
    elimina_sala();
    return 0;
}