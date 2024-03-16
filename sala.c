#include <stdlib.h>
#include "sala.h"

#define bool int
#define false 0
#define true 1

int const CAPACIDAD_MAXIMA = 20000; //constante límite de asientos que pude tener una sala al crearse
int* ptr_ini_sala; //puntero fijo al inicio del vector de asientos
int* ptr_fin_sala; //puntero fijo al fin del vector de asientos
int* ptr;//puntero auxiliar que usamos como iterador
int num_asientos;    // numero de asientos totales/tamaño de la sala
int num_asientos_ocupados;    // numero de asientos que no estan libres
bool sala_creada;//booleano para ver el estado de la sala 0 = No hay sala creada, 1: Hay una sala creada

int reserva_asiento(int id_persona)
{
  if(!sala_creada){return -1;}//comprobamos si hay una sala ya creada
  if(id_persona <= 0){return -1;}//comprobamos que el id_persona es valido
  for(ptr=ptr_ini_sala;ptr<=ptr_fin_sala;ptr++)
  { 
    if(*ptr == -1){*ptr = id_persona; num_asientos_ocupados++; return ptr - ptr_ini_sala + 1;} //recorremos los asientos hasta encontrar uno vacio y lo reservamos
  }
  return -1;//devolvemos -1 si esta la sala llena
}

int libera_asiento (int id_asiento)
{
  if(!sala_creada) return -1;//comprobamos si hay una sala ya creada
  if (id_asiento > num_asientos || id_asiento <= 0){return -1;}//comprobamos id_asiento es valido
  return *(ptr_ini_sala + id_asiento - 1); //devolvemos el id_persona
}

int estado_asiento (int id_asiento)
{
  if(!sala_creada) return -1;//comprobamos si hay una sala ya creada
  if (id_asiento > num_asientos || id_asiento <= 0){return -1;}//comprobamos id_asiento es valido
  return *(ptr_ini_sala + id_asiento - 1) == -1 ? 0 : *(ptr_ini_sala + id_asiento - 1);//devolvemos el id_persona o un 0 si esta vacio 
}

int asientos_libres (){return num_asientos - num_asientos_ocupados;}

int asientos_ocupados(){return num_asientos_ocupados;}

int capacidad_sala(){return num_asientos;}

int crea_sala (int capacidad)
{
  if(sala_creada) return -1; //comprobamos si hay una sala ya creada
  if(capacidad>CAPACIDAD_MAXIMA || capacidad <= 0)return -1;//comprobamos que la capacidad esta dentro del rango permitido

  ptr_ini_sala = (int*)malloc(capacidad * sizeof(int));//reservamos memoria
  if(ptr_ini_sala == NULL) return -1;//comprobamos que se ha reservado memoria adecuadamente
  ptr_fin_sala = ptr_ini_sala + capacidad - 1;//seteamos puntero fijo al ultimo asiento del vector

  for (ptr=ptr_ini_sala;ptr<=ptr_fin_sala;ptr++)
  {
    *ptr = -1;//ini todos los asientos vacios (-1)
  }
  
  sala_creada = true;
  num_asientos_ocupados = 0;//reset variables
  return num_asientos = capacidad; //devuelve la capacidad de la sala creada 
}
int elimina_sala()
{
  if(!sala_creada) return -1;//comprobamos si hay una sala ya creada
  free(ptr_ini_sala);//liberamos memoria
  num_asientos = 0; num_asientos_ocupados = 0; //reset variables
  return sala_creada = false; //retorna 0 si se elimina la sala correctamente
}
