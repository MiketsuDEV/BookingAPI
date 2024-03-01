#include <stdio.h>
#include <stdlib.h>
#include "sala.h"

int CAPACIDAD_MAXIMA = 100;

int *ptr;

int n;    // tamaño sala de cine

int id_persona;    // identificador de persona

int id_asiento;    // identificador de asiento

int cont;    // variable que cuenta numero de asientos

int sala_creada;

int comprobar_sala(){sala_creada =0? return -1:return 0;}

int reserva_asiento(int id_persona){
}

int libera_asiento (int id_asiento){*(ptr+id_asiento) = -1);}

int estado_asiento (int id_asiento){
  if (id_asiento > n){
    return -1;
  }
  if (*(ptr + id_asiento) == -1){
    return 0;
  }else{
    return id_persona;
  }

}

int asientos_libres (){return CAPACIDAD_MAXIMA - cont;}

int asientos_ocupados(){return cont;}

int capacidad_sala(){return n;}

int crear_sala (int capacidad){
  printf("Selecciona un tamaño para la sala de cine");
  scanf ("%d",&n);
  if (n>CAPACIDAD_MAXIMA){
    printf("La capacidad del Cine no puede excedere CAPACIDAD_MAXIMA");
    n = 0;
    return -1;
  }
  ptr = (int*) malloc(n * sizeof(int));

  for (int i =1;i<=n;i++){
    *(ptr + i) = -1;
  }
  return 0;


}
int eliminar_sala(){
  free(ptr);
  n = 0;
  return 0;
}
