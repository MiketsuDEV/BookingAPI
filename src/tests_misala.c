#include <stdlib.h>
#include "sala.h"
#include "misala.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define DebeSerCierto(x) assert(x)
#define DebeSerFalso(x) assert(!(x))

void INICIO_TEST (const char* titulo_test){
printf("********** batería de preubas para %s: ", titulo_test);

fflush(stdout);
}



void FIN_TEST(const char * titulo_test){
printf("***************** test terminado\n");
}

void test_crea_sala(){
	INICIO_TEST ("prueba de creacion test--> en la cual es todo corrector");
	const char* ruta_fichero = "../public/teror";
	int argc = 5;
	char *argv[] = {"misala", "crea", "-f", (char*)ruta_fichero, "-c", "100"};
	procesar_orden(argc, argv);
	FIN_TEST("prueba finalizada");
	
}

int main(){
	test_crea_sala();
}
