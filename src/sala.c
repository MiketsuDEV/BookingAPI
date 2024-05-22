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
{//open
  int fd = open(ruta_fichero, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if(fd == -1) return gestor_errores(ERROR_FICHERO_OPEN);
//write capacidad y asientos ocupados
  if((write(fd, &num_asientos, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_WRITE);
  if((write(fd, &num_asientos_ocupados, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_WRITE);
//calcular tamaño de bloque
  int block_size = calcular_blk_size(ruta_fichero);
  if(block_size == ERROR_MEMORIA) return gestor_errores(ERROR_MEMORIA);
//escritura en bloques
  int capacidad = num_asientos;
  ptr = ptr_ini_sala;
  while((capacidad - block_size) >= 0)
  {
    if((write(fd, ptr, block_size*sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_WRITE);
    capacidad-= block_size;
    ptr+= block_size;
  }
  if((write(fd, ptr, capacidad*sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_WRITE);
  //close
  if(close(fd) == -1)return gestor_errores(ERROR_FICHERO_CLOSE);
  return 0;
}

int recupera_estado_sala(const char* ruta_fichero)
{//open
  int fd = open(ruta_fichero, O_RDONLY);
  if(fd == -1) return gestor_errores(ERROR_FICHERO_OPEN);
//comprobar sala compatible
  int capacidad;
  if((read(fd,&capacidad,sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
  if(capacidad != num_asientos) return gestor_errores(ERROR_SALA_COMPATIBLE);
//read asientos_ocupados
  if((read(fd,&num_asientos_ocupados, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
//calcular tamaño de bloque
  int block_size = calcular_blk_size(ruta_fichero);
  if(block_size == ERROR_MEMORIA) return gestor_errores(ERROR_MEMORIA);
//leer por bloques
  ptr = ptr_ini_sala;
  while((capacidad - block_size) >= 0)
  {
    if((read(fd, ptr, block_size*sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
    capacidad-= block_size;
    ptr+= block_size;
  }
  if((read(fd, ptr, capacidad*sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
//close
  if(close(fd) == -1) return gestor_errores(ERROR_FICHERO_CLOSE);
  return 0;
}

int guarda_estadoparcial_sala(const char* ruta_fichero, int numero_asientos, int* id_asientos)
{//open
  int fd = open(ruta_fichero, O_RDWR);
  if(fd == -1) return gestor_errores(ERROR_FICHERO_OPEN);
//read capacidad y asientos ocupados del fichero a guardar
  int capacidad_fichero;
  if((read(fd,&capacidad_fichero,sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
  int asientos_ocupados_fichero;
  if((read(fd,&asientos_ocupados_fichero,sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
//escritura de los asientos validos
  for(int i = 0;i<numero_asientos;i++)
  {
    int id_asiento = id_asientos[i];
    if(id_asiento <= 0 || id_asiento > num_asientos || id_asiento > capacidad_fichero)
    {
      fprintf(stderr,"El asiento [%d] no es valido, no se ha podido guardar.\n",id_asiento);

    }else
    {
      if(lseek(fd,(id_asiento+1)*sizeof(int),SEEK_SET) == -1) return gestor_errores(ERROR_FICHERO_LSEEK);
      int id_persona_fichero;
      if((read(fd, &id_persona_fichero, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
      int id_persona = estado_asiento(id_asiento);
      //logica asientos ocupados
      if(id_persona_fichero < 0 && id_persona > 0)
      {
        asientos_ocupados_fichero++;    
      }else if(id_persona_fichero > 0 && id_persona < 0)
      {
        asientos_ocupados_fichero--;
      }
      if(lseek(fd,(id_asiento+1)*sizeof(int),SEEK_SET) == -1) return gestor_errores(ERROR_FICHERO_LSEEK);
      if((write(fd, &id_persona, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_WRITE);
    }
  }
//actualizamos asientos ocupados
  if(lseek(fd,sizeof(int),SEEK_SET) == -1) return gestor_errores(ERROR_FICHERO_LSEEK);
  if((write(fd, &asientos_ocupados_fichero, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_WRITE);
//close
  if(close(fd) == -1) return gestor_errores(ERROR_FICHERO_CLOSE);
  return 0;

}

int recupera_estadoparcial_sala(const char* ruta_fichero, int numero_asientos, int* id_asientos)
{//open
  int fd = open(ruta_fichero, O_RDWR);
  if(fd == -1) return gestor_errores(ERROR_FICHERO_OPEN);   
//read capacidad del fichero a recuperar
  int capacidad_fichero;
  if((read(fd,&capacidad_fichero,sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
//comprobamos compatibilidad
  if(capacidad_fichero != num_asientos) return gestor_errores(ERROR_SALA_COMPATIBLE);
//lectura de los asientos validos
  for(int i = 0;i<numero_asientos;i++)
  {
    int id_asiento = id_asientos[i];
    if(id_asiento <= 0 || id_asiento > num_asientos || id_asiento > capacidad_fichero)
    {
      fprintf(stderr,"El asiento [%d] no es valido, no se ha podido recuperar.\n",id_asiento);
    }else
    {
      if(lseek(fd,(id_asiento+1)*sizeof(int),SEEK_SET) == -1) return gestor_errores(ERROR_FICHERO_LSEEK);
      int id_persona_fichero;
      if((read(fd, &id_persona_fichero, sizeof(int))) == -1) return gestor_errores(ERROR_FICHERO_READ);
      int id_persona = estado_asiento(id_asiento);
      //logica asientos ocupados
      if(id_persona_fichero < 0 && id_persona > 0)
      {
        num_asientos_ocupados--;    
      }else if(id_persona_fichero > 0 && id_persona < 0)
      {
        num_asientos_ocupados++;
      }
      ptr_ini_sala[id_asiento-1] = id_persona_fichero;
    }
  }
//close
    if(close(fd) == -1) return gestor_errores(ERROR_FICHERO_CLOSE);
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
int gestor_errores(int error)
{
  switch (error)
  {
  case ERROR_FICHERO_OPEN:
    perror("Error al abrir el archivo.\n");
    return error;   
    break;
  case ERROR_FICHERO_CLOSE:
    perror("Error al cerrar el archivo.\n");
    return error;   
    break;
  case ERROR_FICHERO_WRITE:
    perror("Error al escribir en el archivo.\n");
    return error;   
    break;
  case ERROR_FICHERO_READ:
    perror("Error al leer el archivo.\n");
    return error;   
    break;
  case ERROR_FICHERO_LSEEK:
    perror("Error al modificar el puntero del archivo.\n");
    return error;   
    break;
  case ERROR_SALA_COMPATIBLE:
    perror("Error de compatibilidad entre la sala en memoria y la sala del archivo.\n");
    return error;   
    break;
  case ERROR_MEMORIA:
    perror("Error al reservar memoria.\n");
    return error;   
    break;
  default:
    perror("Error no especificado.\n");
    return error;
    break;
  }
  return 0;
}
