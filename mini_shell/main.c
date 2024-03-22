#include <stdio.h>
#include <stdlib.h>
#include "sala.h"
#include "test_sala.h"
#include "crear_procesos.h"
#include "shell_interactivo.h"

int main()
{
	//crear_sucursal("Las palmas", 100);
	leer_shell();
    exit(0);
}
int main(int argc, char *argv[])
{
	//crear_sucursal(argv[0], argv[1]);
	printf("%d,%d,", argv[0], argv[1]);
    exit(0);
}