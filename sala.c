#include <stdio.h>
#include <stdlib.h>
#include "sala.h"

int CAPACIDAD_MAXIMA = 1000;
int* ptr_ini_sala; //Puntero fijo al inicio del vector de asientos
int* ptr;//Puntero auxiliar que usamos como iterador
int num_asientos;    // tamaño sala de cine
int num_asientos_ocupados;    // variable que cuenta numero de asientos
int sala_creada;// 0 = No hay sala creada, 1: Hay una sala creada.

int comprobar_sala(){return sala_creada = 0 ? 0 : 1;}

int reserva_asiento(int id_persona)
{
  if(!comprobar_sala){return -1;}//Comprobamos si hay una sala ya creada
  if(id_persona <= 0){return -1;}//Comprobamos id_persona es valido
  for(ptr=ptr_ini_sala;ptr<=ptr_ini_sala+num_asientos;ptr++){ 
    if(*ptr == -1){ *ptr = id_persona; return 0;} //Recorremos los asientos hasta encontrar uno vacio
  }
  return -1;
}

int libera_asiento (int id_asiento)
{
  if(!comprobar_sala) return -1;//Comprobamos si hay una sala ya creada
  if (id_asiento > capacidad_sala || id_asiento <= 0){return -1;}//Comprobamos id_asiento es valido
  return *(ptr_ini_sala+id_asiento-1) == -1 ? 0 : *(ptr_ini_sala+id_asiento-1);
}

int estado_asiento (int id_asiento)
{
  if(!comprobar_sala) return -1;//Comprobamos si hay una sala ya creada
  if (id_asiento > capacidad_sala || id_asiento <= 0){return -1;}//Comprobamos id_asiento es valido
  return *(ptr_ini_sala+id_asiento-1) == -1 ? 0 : *(ptr_ini_sala+id_asiento-1);
}

int asientos_libres (){return num_asientos - num_asientos_ocupados;}

int asientos_ocupados(){return num_asientos_ocupados;}

int capacidad_sala(){return num_asientos;}

int crear_sala (int capacidad)
{
  if (!comprobar_sala()) return -1; //Comprobamos si hay una sala ya creada
  if(capacidad>CAPACIDAD_MAXIMA || capacidad <= 0)return -1;//Comprobamos que la capacidad esta dentro del rango permitido

  ptr_ini_sala = (int*) malloc(capacidad * sizeof(int));//Reservamos memoria
  if(ptr_ini_sala == NULL) return -1;//Comprobamos que se ha reservado memoria adecuadamente
  
  for (ptr=ptr_ini_sala;ptr<=ptr_ini_sala+capacidad;ptr++){
    *ptr = -1;//Ini todos los asientos vacios (-1)
  }
  sala_creada = 1;
  return num_asientos = capacidad;
}
int eliminar_sala()
{
  if(comprobar_sala) return -1;//Comprobamos si hay una sala ya creada
  free(ptr_ini_sala);//Liberamos memoria
  num_asientos = 0;
  sala_creada = 0;
  return 0;
}
