#include "crear_procesos.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


void crear_sucursal(const *char ciudad, capacidad){
// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	if (pid == 0){	// proceso hijo
		char *arg[] ={"gnome-terminal","-e","./sala.c",NULL,ciudad,capacidad};
		//sala.c es provisional ya que creo que tengo que llamar al shell que hace miguel
		execvp("gnome-terminal",args);
		perror("execvp");
		exit(1);
	}else if(pid >1){
		wait(NULL);
	}else{
		perror("error llamando al fork");
		exit(1);
	}
	
	
}




main(){

}
