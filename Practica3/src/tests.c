#include <stdlib.h>
#include "sala.h"
#include <stdio.h>
#include <assert.h>

#define DebeSerCierto(x) 	assert(x)
#define DebeSerFalso(x) 	assert(!(x))

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



void INICIO_TEST (const char* titulo_test){
	printf("********** batería de preubas para %s: ", titulo_test);
	
	fflush(stdout);
}



void FIN_TEST(const char * titulo_test){
	printf("***************** test terminado\n");
}



void test_guarda_estado(){
}


void test_recupera_estado(){
}


void test_guarda_estado_parcial(){
}


void test_recupera_estado_parcial(){
}
