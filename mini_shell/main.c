#include <stdio.h>
#include <stdlib.h>
#include "sala.h"
#include "shell_interactivo.h"

void main(int argc, char *argv[])
{
    if(argc != 3) printf("Error");
    procesar_crear_sala(argv[1], atoi(argv[2]));
	leer_shell();
    exit(0);
}
