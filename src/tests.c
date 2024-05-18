#include <stdlib.h>
#include "sala.h"
#include "misala.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define DebeSerCierto(x) assert(x)
#define DebeSerFalso(x) assert(!(x))

#define CAPACIDAD_CUYAS 847
#define CAPACIDAD_ALFREDO_KRAUS 1200
#define PEREZ_GALDOS 522
#define PARANINFO 10




#define ID_1  120
#define ID_2 -2
#define ID_3 -1
#define ID_4 1500
#define ID_5 2
#define ID_6 1


int* estado_sala(){
	int *estado = (int*) malloc(capacidad_sala() * sizeof(int));
	if (estado == NULL){
		fprintf(stderr, "Ocurrio un error al intentar ocupar espacio en memoria");
		return NULL;
	}
	for(int i =1; i <capacidad_sala();i++){
		estado[i] =estado_asiento(i);
	}
	return estado;
}



void INICIO_TEST (const char* titulo_test){
printf("********** batería de preubas para %s: ", titulo_test);

fflush(stdout);
}



void FIN_TEST(const char * titulo_test){
printf("***************** test terminado\n");
}

void test_crea(){
	INICIO_TEST ("test para la creacion de sala");
	const *char = "../tests/crea",
	
	int argc =5;
	char *argv[] =
}


void test_guarda_estado_sala(){
	INICIO_TEST ("test para guardar el estado de la sala");
	const char* ruta_fichero = "../tests/guarda_estado_sala";
	
	int capacidad = 100;
	crea_sala(capacidad);
	
	for(int i =1;i<=10;i++){
		DebeSerCierto(reserva_asiento(i) == i);
	}
	
	DebeSerCierto(libera_asiento(4)==-15);
	libera_asiento(8);
	
		
	DebeSerCierto(guarda_estado_sala(ruta_fichero)==0);
	FILE* file = fopen(ruta_fichero, "r");
	DebeSerCierto(file != NULL);
	fclose(file);
	elimina_sala();
	FIN_TEST("guarda estado");
}


void test_recupera_estado(){
	INICIO_TEST ("test para recuperar el estado de la sala");
	crea_sala (100);
	const char* ruta_fichero = "../tests/guarda_estado_sala";
	const char * ruta_fichero_falsa = "..test/no_guarda_nada";
	const char * ruta_fichero_falsa2 = "";
	DebeSerFalso(recupera_estado_sala(ruta_fichero_falsa2)== 0);
	DebeSerFalso(recupera_estado_sala(ruta_fichero_falsa)== 0);
	DebeSerCierto(recupera_estado_sala(ruta_fichero) == 0);
	DebeSerCierto(estado_asiento(1) ==1);
	DebeSerCierto(estado_asiento(3) ==3);
	DebeSerFalso(estado_asiento(4) == 4);
	DebeSerCierto(asientos_libres() == 92);
	elimina_sala();
	FIN_TEST("recupera estado sala");
}


void test_guarda_estado_parcial(){
	INICIO_TEST ("test para guardar el estado parcial de la sala");
	char* ruta_fichero = "../tests/guarda_estado_sala";
	int capacidad = 100;
	crea_sala(capacidad);
	
	for (int i=1; i<=10; i++){
		DebeSerCierto(reserva_asiento(i) == i);
		
		
	}
	int asientos[] = {1,2,3};
	DebeSerCierto(guarda_estadoparcial_sala(ruta_fichero,3,asientos)==0 );
	printf("\n valor de estado asiento 1 %d \n", estado_asiento(1));
	elimina_sala();
	
	FIN_TEST("guarda estado parcial");
}


void test_recupera_estado_parcial(){

	INICIO_TEST ("test para recuperar el estado parcial de la sala");
	char* ruta_fichero = "../tests/guarda_estado_sala";
	crea_sala(100);
	int tamaño = 3;
	int asientos[] = {1,2,3};
	DebeSerCierto(recupera_estadoparcial_sala(ruta_fichero,tamaño,asientos) == 0);
	DebeSerCierto(asientos_ocupados() == 3);
	printf("\n asientos ocupados %d \n", asientos_ocupados());
	printf("\n asientos libres %d \n", asientos_libres());
	for (int i =1; i<=100;i++){
		printf("\n valor de estado asiento %d %d \n",i, estado_asiento(i));

	}
	
	printf("\n valor de estado asiento 10 %d \n", estado_asiento(10));
	DebeSerCierto(estado_asiento(1) == 1);
	DebeSerCierto(estado_asiento(2) == 2);
	DebeSerCierto(estado_asiento(5) != 5);
	elimina_sala();
	
	FIN_TEST("recupera estado parcial");
}

int main(){
	test_guarda_estado_sala();
	test_recupera_estado();
	test_guarda_estado_parcial();
	test_recupera_estado_parcial();
}

