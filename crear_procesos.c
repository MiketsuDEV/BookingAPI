#include "crear_procesos.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



void crear_sucursal(const char *ciudad,int capacidad){	// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	if (pid_t == 0){	// proceso hijo		
		execlp("gnome-terminal","gnome-terminal",NULL);
		perror("execvp");
		exit(1);
	}else if(pid_t >1){
		wait(NULL);
	}else{
		perror("error llamando al fork");
		exit(1);
	}
	
	
}

main(){
	crear_sucursal("las palmas", 100);
	exit(0);
}




