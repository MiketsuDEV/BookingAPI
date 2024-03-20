#include "crear_procesos.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void crear_sucursal(const *char ciudad, capacidad);
void crear_sucursal(const *char ciudad, capacidad){
// aqui hacemos la llamada a minishell con creacion de procesos con fork y exec
	int pid_t = fork();
	
}




main(){
	int capacidad;
	char nombresala[20];

	while(1){
		// pedimos nombre y cantidad de la sala
		printf("Dime cual quieres que sea el tamaño de la sala");
		scanf("%d",capacidad);
		printf("dime el nombre que quieres ponerle a la sala");
		scanf("%s",nombresala);


		if(!strcmp("salir",nombresala))break;	// aqui lo que hace es que si salir es el nombre de 
							// la sala pues acaba el programa y sale del shell

		void crear_sucursal(nombresala,capacidad);
	}// aqui acaba el programa


}
