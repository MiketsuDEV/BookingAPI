#include "crear_procesos.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



void crear_sucursal(const char *ciudad,int capacidad){	// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	if (pid_t == 0){	// proceso hijo
		char *tira[] = {"gnome-terminal","-e","./a",NULL};		
		execvp("gnome-terminal",tira);
		
		
	}else if(pid_t >1){
		wait(NULL);
	}else{
		perror("error llamando al fork");
		exit(1);
	}
}





