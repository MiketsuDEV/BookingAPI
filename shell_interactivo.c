#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_interactivo.h"

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
    if(!strcmp(input, "salir"))
    {
        return true;
    }
    char* comando = strtok(input, " ");
    if(!strcmp(comando, "crear_sala"))
    {
        char* nombre_sala = strtok(NULL, " ");
        int capacidad_sala = atoi(strtok(NULL, " "));
        printf("DEBUG Nombre de la sala: %s\n", nombre_sala);
        printf("DEBUG Capacidad de la sala: %d\n", capacidad_sala);
        //crear_sucursal(nombre_sala, capacidad_sala);
        return false;
    }
    return false;
}