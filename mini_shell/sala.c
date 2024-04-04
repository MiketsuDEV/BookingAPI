#include <stdlib.h>
#include "sala.h"
#include "error_manager.h"



int const CAPACIDAD_MAXIMA = 20000; //constante límite de asientos que pude tener una sala al crearse
int* ptr_ini_sala; //puntero fijo al inicio del vector de asientos
int* ptr_fin_sala; //puntero fijo al fin del vector de asientos
int* ptr;//puntero auxiliar que usamos como iterador
int num_asientos;    // numero de asientos totales/tamaño de la sala
int num_asientos_ocupados;    // numero de asientos que no estan libres
bool sala_creada;//booleano para ver el estado de la sala 0 = No hay sala creada, 1: Hay una sala creada

int reserva_asiento(int id_persona)
{
  if(!sala_creada){return ERROR_SALA_CERRADA;}
  if(id_persona <= 0){return ERROR_ID_PERSONA;}
  for(ptr=ptr_ini_sala;ptr<=ptr_fin_sala;ptr++)
  { 
    if(*ptr == -1)
    {//recorremos los asientos hasta encontrar uno vacio y lo reservamos
      *ptr = id_persona;
      num_asientos_ocupados++;
      return ptr - ptr_ini_sala + 1;
    } 
  }
  return ERROR_SALA_LLENA;
}

int libera_asiento (int id_asiento)
{
  if(!sala_creada) return ERROR_SALA_CERRADA;
  if (id_asiento > num_asientos || id_asiento <= 0)return ERROR_ID_ASIENTO;
  ptr = ptr_ini_sala + id_asiento - 1;
  int id_persona = *ptr;
  if(id_persona == -1)return ERROR_ASIENTO_VACIO;
  num_asientos_ocupados--;
  *ptr = -1;
  return id_persona; 
}

int estado_asiento (int id_asiento)
{
  if(!sala_creada) return ERROR_SALA_CERRADA;
  if (id_asiento > num_asientos || id_asiento <= 0)return ERROR_ID_ASIENTO;
  return *(ptr_ini_sala + id_asiento - 1) == -1 ? ERROR_ASIENTO_VACIO : *(ptr_ini_sala + id_asiento - 1);//devolvemos el id_persona o un 0 si esta vacio 
}

int asientos_libres (){if(!sala_creada) return ERROR_SALA_CERRADA; return num_asientos - num_asientos_ocupados;}

int asientos_ocupados(){if(!sala_creada) return ERROR_SALA_CERRADA; return num_asientos_ocupados;}

int capacidad_sala(){if(!sala_creada) return ERROR_SALA_CERRADA; return num_asientos;}

int crea_sala (int capacidad)
{
  if(sala_creada) return ERROR_SALA_ABIERTA;
  if(capacidad>CAPACIDAD_MAXIMA || capacidad <= 0)return ERROR_SALA_CAPACIDAD;

  ptr_ini_sala = (int*)malloc(capacidad * sizeof(int));//reservamos memoria
  if(ptr_ini_sala == NULL) return ERROR_MEMORIA;//comprobamos que se ha reservado memoria adecuadamente
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
  if(!sala_creada) return ERROR_SALA_CERRADA;
  free(ptr_ini_sala);//liberamos memoria
  num_asientos = 0; num_asientos_ocupados = 0; //reset variables
  return sala_creada = false; //retorna 0 si se elimina la sala correctamente
}
