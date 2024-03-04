#include <stdio.h>
#include <stdlib.h>
#include "sala.h"

int CAPACIDAD_MAXIMA = 1000;
int* ptr_ini_sala; //Puntero fijo al inicio del vector de asientos
int* ptr_aux;
int num_asientos;    // tamaño sala de cine
int num_asientos_ocupados;    // variable que cuenta numero de asientos
int sala_creada;// 0 = No hay sala creada, 1: Hay una sala creada.

int comprobar_sala(){return sala_creada = 0 ? 0: 1;}

int reserva_asiento(int id_persona){
  if(!comprobar_sala){return -1;}//Comprobamos sala creada
  for(ptr_aux = ptr_ini_sala;ptr_aux<=ptr_ini_sala+num_asientos;ptr_aux++){
    if(*ptr_aux == -1){ *ptr_aux = id_persona; return 0;}
  }
  return -1;
}

int libera_asiento (int id_asiento)
{
  if(!comprobar_sala) return -1;
  *(ptr_ini_sala+id_asiento) = -1;
}

int estado_asiento (int id_asiento)
{
  if(!comprobar_sala) return -1;
  if (id_asiento > capacidad_sala || id_asiento < -1){
    return -1;
  }

  if (*(ptr_ini_sala + id_asiento) == -1){
    return 0;
  }else{
    //return *(ptr_ini_sala + 
  }

}

int asientos_libres (){return CAPACIDAD_MAXIMA - num_asientos_ocupados;}

int asientos_ocupados(){return num_asientos_ocupados;}

int capacidad_sala(){return capacidad_sala;}

int crear_sala (int capacidad)
{
  if (!comprobar_sala()) return -1; //Sala ya creada

  num_asientos = capacidad;
  if(capacidad>CAPACIDAD_MAXIMA || capacidad <= 0)return -1;//Comprobamos que la capacidad esta dentro del rango permitido

  ptr_ini_sala = (int*) malloc(capacidad * sizeof(int));//Reservamos memoria
  if(ptr_ini_sala == NULL) return -1;//Comprobamos que se ha reservado memoria
  
  for (int i =1;i<=capacidad;i++){//Ini todos los asientos vacios (-1)
    *(ptr_ini_sala + i) = -1;
  }
  sala_creada = 1;
  return 0;


}
int eliminar_sala()
{
  if(comprobar_sala) return -1;
  free(ptr_ini_sala);
  num_asientos = 0;
  sala_creada = 0;
  return 0;
}
