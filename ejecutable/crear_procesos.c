#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "crear_procesos.h"


void crear_sucursal(const char *ciudad,int capacidad){	// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	if (pid_t == 0){	// proceso hijo
		char *tira[] = {"xterm","-e", "./mini_shell/mini_shell",NULL};		
		execvp("xterm",tira);
		
		
	}else if(pid_t >1){
		wait(NULL);
	}else{
		perror("error llamando al fork");
	}
}

void main(int argc, char *argv[])
{
	crear_sucursal(argv[1], atoi(argv[2]));
	exit(0);
}



