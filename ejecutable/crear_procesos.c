#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "crear_procesos.h"
#include "../mini_shell/error_manager.h"

pid_t hijos[10];

pid_t result;
int num_hijos=0;

void crear_sucursal(char *ciudad,  char *capacidad){	// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	if (pid_t == 0){	// proceso hijo
		char *tira[] = {"xterm","-e", "../mini_shell/mini_shell", ciudad, capacidad,  NULL};		
		execvp("xterm",tira);
		
	}else{
		hijos[num_hijos++] = pid_t;
	}

	for (int i =0;i<num_hijos;i++){
		int status;
		result = waitpid(hijos[i],&status,WNOHANG);
		if(result == -1){
			perror("error al esperar al hijo");
		}else if(result >0){
			if(WIFEXITED(status)){
				printf("El hijo con el PID %d y con nombre de %d ha terminado con codigo de salida %d \n",hijos[i],ciudad,WIFEXITED(status));
				hijos[i] = hijos[--num_hijos];
			}
		}
	}
}

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
    if(!strcmp(comando, "crear_sucursal"))
    {
        char *ciudad = strtok(NULL, " ");
		char *capacidad = strtok(NULL, " ");
		crear_sucursal(ciudad, capacidad);


	}else if(!strcmp(comando, "salir"))
	{
		return true;
	}
	return false;
}

