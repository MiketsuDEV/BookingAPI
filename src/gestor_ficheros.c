#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "error_manager.h"
#include "gestor_ficheros.h"
#include "sala.h"

extern int* ptr_ini_sala;
extern int num_asientos_ocupados;

int guarda_estado_sala(const char* ruta_fichero, bool oflag)
{
    int fd;
    if(oflag){
        fd = open(ruta_fichero, O_WRONLY | O_CREAT | O_TRUNC, 644);
    }else{
        fd = open(ruta_fichero, O_WRONLY | O_CREAT | O_EXCL);
    }
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    stat(ruta_fichero, buf);
    unsigned long block_size = buf->st_blksize;
    block_size /= sizeof(int);
    free(buf);
    int capacidad = capacidad_sala();
    int* ptr = ptr_ini_sala;
    write(fd, capacidad_sala(), sizeof(int));
    write(fd, asientos_ocupados(), sizeof(int));
    while((capacidad - block_size) >= 0)
    {
        write(fd, ptr, block_size*sizeof(int));
        capacidad-= block_size;
        ptr+= block_size;
    }
    write(fd, ptr, capacidad*sizeof(int));
    
    close(ruta_fichero);
}
int recupera_estado_sala(const char* ruta_fichero)
{
    elimina_sala();
    int fd = open(ruta_fichero, O_RDONLY);
    int* capacidad_ptr = (int)malloc(sizeof(int));
    read(fd,capacidad_ptr,sizeof(int));
    crea_sala(*capacidad_ptr);
    read(fd,capacidad_ptr,sizeof(int));
    num_asientos_ocupados = *capacidad_ptr;
    free(capacidad_ptr);
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    stat(ruta_fichero, buf);
    unsigned long block_size = buf->st_blksize;
    block_size /= sizeof(int);
    free(buf);
    int* ptr = ptr_ini_sala;
    int capacidad = capacidad_sala();
    while((capacidad - block_size) >= 0)
    {
        read(fd, ptr, block_size*sizeof(int));
        capacidad-= block_size;
        ptr+= block_size;
    }
    read(fd, ptr, capacidad*sizeof(int));
    close(ruta_fichero);
}
int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}