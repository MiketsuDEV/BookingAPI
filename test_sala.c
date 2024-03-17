#include <assert.h>
#include <stdio.h>
#include "sala.h"
#include "test_sala.h"

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

#define CAPACIDAD_CUYAS 943
#define CAPACIDAD_ALFREDO_KRAUS 1570
#define CAPACIDAD_PARANINFO 600
#define CAPACIDAD_PEREZ_GALDOS 1007

#define ID_1 1500
#define ID_2 4321
#define ID_3 7777
#define ID_4 2

void INICIO_TEST (const char* titulo_test)
{
  printf("********** batería de pruebas para %s: ", titulo_test); 
 	// fflush fuerza que se imprima el mensaje anterior
	// sin necesidad de utilizar un salto de línea
	fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
  printf ("********** hecho\n");
}

void test_reserva_basica()
{
	int mi_asiento;
	INICIO_TEST("Reserva básica");
	crea_sala(CAPACIDAD_CUYAS);
	DebeSerCierto(capacidad_sala()==CAPACIDAD_CUYAS);
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	DebeSerCierto(estado_asiento(mi_asiento)>0);
	DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	elimina_sala();
	FIN_TEST("Reserva básica");
}

void test_integridad_sala_creada()
{
	INICIO_TEST("Integridad Sala Creada");
	DebeSerCierto(reserva_asiento(ID_4) == -1);
	DebeSerCierto(libera_asiento(1) == -1);
	DebeSerCierto(estado_asiento(5)== -1);
	DebeSerCierto(asientos_libres() == 0);
	DebeSerCierto(asientos_ocupados() == 0);
	DebeSerCierto(capacidad_sala() == 0);
	DebeSerCierto(elimina_sala() == -1);
	DebeSerCierto(crea_sala(CAPACIDAD_PARANINFO) == CAPACIDAD_PARANINFO);
	DebeSerCierto(crea_sala(CAPACIDAD_PARANINFO) == -1);

	DebeSerFalso(reserva_asiento(ID_4) == -1);
	DebeSerFalso(reserva_asiento(ID_2) == -1);
	DebeSerFalso(libera_asiento(1) == -1);
	DebeSerFalso(estado_asiento(5)== -1);
	DebeSerFalso(asientos_libres() == 0);
	DebeSerFalso(asientos_ocupados() == 0);
	DebeSerFalso(capacidad_sala() == 0);
	DebeSerFalso(elimina_sala() == -1);
	FIN_TEST("Integridad Sala Creada");

}
void test_reserva_multiple()
{
	INICIO_TEST("Reserva Multiple");
	DebeSerCierto(crea_sala(CAPACIDAD_PEREZ_GALDOS) == CAPACIDAD_PEREZ_GALDOS);
	sentarse(ID_1);
	sentarse(-15);
	sentarse(ID_4);
	sentarse(ID_3);
	levantarse(1);
	levantarse(15);
	levantarse(-130);
	levantarse(3);
	estado_sala();
	DebeSerCierto(elimina_sala() == 0);
	FIN_TEST("Reserva Multiple");
}
void estado_sala()
{
	printf("\n######################################\n");
	printf("Estado Sala: ");
	capacidad_sala() == 0 ? printf("cerrada.\n") : printf("abierta.\n");
	printf("Aforo: %d.\n", capacidad_sala());
	printf("Asientos ocupados: %d.\n", asientos_ocupados());
	printf("Asientos libres: %d.\n", asientos_libres());
	char asiento;
	for(int i=1; i<=capacidad_sala(); i++)
	{
		asiento = estado_asiento(i) <= 0 ? ' ' : 'x';  
		printf("[%c]", asiento);
		if(i % 30 == 0) printf("\n");
	}
	printf("\n######################################\n");
	fflush(stdout);
}
void sentarse(int id_persona)
{
	int id_asiento = reserva_asiento(id_persona);
	switch (id_asiento)
	{
	case -1:
		printf("Error al intentar reservar el asiento.\n");
		break;
	
	default:
		printf("Se ha reservado el asiento %d.\n", id_asiento);
		break;
	}
}
void levantarse(int id_asiento)
{
	int id_persona = libera_asiento(id_asiento);
	switch (id_persona)
	{
	case 0:
		printf("El asiento ya esta libre.\n");
		break;
	case -1:
		printf("Error al intentar liberar asiento.\n");
		break;
	default:
		printf("Se ha liberado el asiento %d.\n", id_asiento);
		break;
	}
}
void ejecuta_tests ()
{
	test_integridad_sala_creada();
	test_reserva_basica();
	test_integridad_sala_creada();
	test_reserva_multiple();
	test_integridad_sala_creada();
}


