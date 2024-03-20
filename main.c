#include <stdio.h>
#include <stdlib.h>
#include "sala.h"
#include "test_sala.h"
#include "crear_procesos.h"
#include "shell_interactivo.h"

int main()
{
	puts("Iniciando tests...");
	ejecuta_tests();
	puts("Batería de test completa.");
    exit(0);
}