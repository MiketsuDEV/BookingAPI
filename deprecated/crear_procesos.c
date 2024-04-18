#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "crear_procesos.h"
#include "../mini_shell/error_manager.h"

#define MAXIMO_SUCURSALES 10
pid_t hijos[MAXIMO_SUCURSALES];
char ciudades[MAXIMO_SUCURSALES][256];

pid_t result;

void crear_sucursal(char *ciudad,  char *capacidad){	// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	if (pid_t == -1){
		perror("error al crear un nuevo proceso");
	}else{

		if (pid_t == 0){	// proceso hijo
			char *tira[] = {"xterm","-e", "../mini_shell/mini_shell", ciudad, capacidad,  NULL};		
			execvp("xterm",tira);
		
		}else{
			for(int i=0; i< MAXIMO_SUCURSALES;i++)
			{
				if(hijos[i] == -1)
				{
					hijos[i] = pid_t;
					strcpy(ciudades[i], ciudad);
					break;
				}
			}
		}
	}
}

void leer_shell()
{
	for(int i=0; i< MAXIMO_SUCURSALES;i++)
	{
		hijos[i]= -1;
	}
	bool exit = false;
    while(!exit)
    {
        char input[256];
        fgets(input, 256, stdin);
        exit = procesar_input(input);
		comprobar_hijos();
    }
}
int procesar_input(char* input)
{
    input[strcspn(input, "\n")] = 0; // quitar el salto de linea
    
    //procesamos el comando a realizar
    char* comando = strtok(input, " ");
    if(!strcmp(comando, "crear_sucursal"))
    {
        char *ciudad = strtok(NULL, " ");
		char *capacidad = strtok(NULL, " ");
		if(ciudad == NULL && capacidad == NULL)
		{
			printf("Error en los parametros de la sucursal.\n");
			return false;	
		}
		crear_sucursal(ciudad, capacidad);


	}else if(!strcmp(comando, "salir"))
	{
		return true;
	}
	return false;
}
int comprobar_hijos()
{
	for (int i =0;i<MAXIMO_SUCURSALES;i++){
		if(hijos[i] != -1)
		{
			int status;
			result = waitpid(hijos[i],&status,WNOHANG);
			if(result == -1){
				perror("error al esperar al hijo");
			}else if(result >0){
				if(WIFEXITED(status)){
					printf("La sucursal %s  con  PID %d ha cerrado.\n",ciudades[i],hijos[i]);
					hijos[i] = -1;
				}
			}
		}
	}
}
