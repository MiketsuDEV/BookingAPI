#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "error_manager.h"
#include "gestor_ficheros.h"
#include "sala.h"

extern int* ptr_ini_sala;
extern int num_asientos_ocupados;

int guarda_estado_sala(const char* ruta_fichero, bool oflag)
{
    int fd;
    if(oflag){
        fd = open(ruta_fichero, O_WRONLY | O_CREAT  |  O_TRUNC, 0666);
    }else{
        fd = open(ruta_fichero, O_WRONLY);
    }
    //calculamos tamaño de bloque
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    stat(ruta_fichero, buf);
    int block_size = (buf->st_blksize) / sizeof(int);
    free(buf);

    int* ptr = ptr_ini_sala;
    int capacidad = capacidad_sala();
    int asientos_en_uso = asientos_ocupados();

    write(fd, &capacidad, sizeof(int));
    write(fd, &asientos_en_uso, sizeof(int));
    while((capacidad - block_size) >= 0)
    {
        write(fd, ptr, block_size*sizeof(int));
        capacidad-= block_size;
        ptr+= block_size;
    }
    write(fd, ptr, capacidad*sizeof(int));
    
    close(fd);
}
int recupera_estado_sala(const char* ruta_fichero)
{
    elimina_sala();
    int fd = open(ruta_fichero, O_RDONLY);
    //calculamos tamaño de bloque
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    stat(ruta_fichero, buf);
    int block_size = (buf->st_blksize) / sizeof(int);
    free(buf);

    int capacidad;
    read(fd,&capacidad,sizeof(int));
    crea_sala(capacidad);
    read(fd,&capacidad,sizeof(int));
    num_asientos_ocupados = capacidad;
    
    int* ptr = ptr_ini_sala;
    capacidad = capacidad_sala();
    while((capacidad - block_size) >= 0)
    {
        read(fd, ptr, block_size*sizeof(int));
        capacidad-= block_size;
        ptr+= block_size;
    }
    read(fd, ptr, capacidad*sizeof(int));
    close(fd);
}
int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}