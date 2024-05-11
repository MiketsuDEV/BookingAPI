#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
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
  if(num_asientos == num_asientos_ocupados){return ERROR_SALA_LLENA;}
  for(ptr=ptr_ini_sala;ptr<=ptr_fin_sala;ptr++)
  { 
    if(*ptr == -1)
    {//recorremos los asientos hasta encontrar uno vacio y lo reservamos
      *ptr = id_persona;
      num_asientos_ocupados++;
      return ptr - ptr_ini_sala + 1;
    } 
  }
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
  return *(ptr_ini_sala + id_asiento - 1) == -1 ? ERROR_ASIENTO_VACIO : *(ptr_ini_sala + id_asiento - 1);
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

int guarda_estado_sala(const char* ruta_fichero)
{
  int fd = open(ruta_fichero, O_WRONLY | O_CREAT | O_EXCL, 0666);
  if(fd == -1) return ERROR_FICHERO_OPEN;
  if((write(fd, &asientos_libres, sizeof(int))) == -1) return ERROR_FICHERO_WRITE;
  if((write(fd, &asientos_ocupados, sizeof(int))) == -1) return ERROR_FICHERO_WRITE;

  int block_size = calcular_blk_size(ruta_fichero);
  if(block_size == ERROR_MEMORIA) return ERROR_MEMORIA;
  int capacidad = asientos_libres;
  ptr = ptr_ini_sala;

  while((capacidad - block_size) >= 0)
  {
    if((write(fd, ptr, block_size*sizeof(int))) == -1) return ERROR_FICHERO_WRITE;
    capacidad-= block_size;
    ptr+= block_size;
  }
  if((write(fd, ptr, capacidad*sizeof(int))) == -1) return ERROR_FICHERO_WRITE;
    
  if(close(fd) == -1)return ERROR_FICHERO_CLOSE;
  return 0;
}
int recupera_estado_sala(const char* ruta_fichero)
{//WIP
  int fd = open(ruta_fichero, O_RDONLY);
  if(fd == -1) return ERROR_FICHERO_OPEN;

  int block_size = calcular_blk_size(ruta_fichero);
  int capacidad;
  if((read(fd,&capacidad,sizeof(int))) == -1) return ERROR_FICHERO_READ;
  crea_sala(capacidad);
  if((read(fd,&capacidad,sizeof(int))) == -1) return ERROR_FICHERO_READ;
  num_asientos_ocupados = capacidad;
  ptr = ptr_ini_sala;
  capacidad = capacidad_sala();
    while((capacidad - block_size) >= 0)
    {
        if((read(fd, ptr, block_size*sizeof(int))) == -1) return ERROR_FICHERO_READ;
        capacidad-= block_size;
        ptr+= block_size;
    }
  if((read(fd, ptr, capacidad*sizeof(int))) == -1) return ERROR_FICHERO_READ;
  if(close(fd) == -1){perror("Error al cerrar el archivo");exit(-1);}
  return 0;
}
int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{//WIP
    int fd = open(ruta_fichero, O_RDONLY);
    if(fd == -1) return ERROR_FICHERO_OPEN;
    int block_size = calcular_blk_size(ruta_fichero);

    for(int i = 0;i<num_asientos;i++)
    {
        int id = id_asientos[i];
        if(lseek(fd,(id+1)*sizeof(int),SEEK_SET) == -1) return ERROR_FICHERO_LSEEK;
        id = estado_asiento(id);
        if((write(fd, &id, sizeof(int))) == -1) return ERROR_FICHERO_WRITE;
    }
    if(close(fd) == -1) return ERROR_FICHERO_CLOSE;
    return 0;

}
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{//WIP
    int fd = open(ruta_fichero, O_RDONLY);
    if(fd == -1){perror("Error al abrir el archivo");exit(-1);}
    int block_size = calcular_blk_size(ruta_fichero);
    for(int i = 0;i<num_asientos;i++)
    {
        int id = id_asientos[i];
        if(lseek(fd,(id+1)*sizeof(int),SEEK_SET) == -1){perror("Error al mover el puntero del archivo");exit(-1);}
        int id_persona;
        if((read(fd, &id_persona, sizeof(int))) == -1){perror("Error al escribir en el archivo");exit(-1);}
        ptr_ini_sala[id] = id_persona;
    }

    if(close(fd) == -1){perror("Error al cerrar el archivo");exit(-1);}
    return 0;
}

int calcular_blk_size(const char* ruta_fichero)
{
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    if(buf == NULL) return ERROR_MEMORIA;
    stat(ruta_fichero, buf);
    int block_size = (buf->st_blksize) / sizeof(int);
    free(buf);
    return block_size;
}