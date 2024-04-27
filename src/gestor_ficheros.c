#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "error_manager.h"
#include "gestor_ficheros.h"
#include "sala.h"

extern int* ptr_ini_sala;
extern int num_asientos_ocupados;

int guarda_estado_sala(const char* ruta_fichero, bool oflag)
{
    int fd;
    int error;
    if(oflag){
        fd = open(ruta_fichero, O_WRONLY | O_CREAT  |  O_TRUNC, 0666);
    }else{
        fd = open(ruta_fichero, O_WRONLY);
    }
    if(fd == -1){perror("Error al abrir el archivo");exit(-1);}
    
    int block_size = calcular_blk_size(ruta_fichero);
    int* ptr = ptr_ini_sala;
    int capacidad = capacidad_sala();
    int asientos_en_uso = asientos_ocupados();

    if((write(fd, &capacidad, sizeof(int))) == -1){perror("Error al escribir en el archivo");exit(-1);}
    if((write(fd, &asientos_en_uso, sizeof(int))) == -1){perror("Error al escribir en el archivo");exit(-1);}

    while((capacidad - block_size) >= 0)
    {
        if((write(fd, ptr, block_size*sizeof(int))) == -1){perror("Error al escribir en el archivo");exit(-1);}
        capacidad-= block_size;
        ptr+= block_size;
    }
    if((write(fd, ptr, capacidad*sizeof(int))) == -1){perror("Error al escribir en el archivo");exit(-1);}
    
    if(close(fd) == -1){perror("Error al cerrar el archivo");};
}
int recupera_estado_sala(const char* ruta_fichero)
{
    elimina_sala();
    int fd = open(ruta_fichero, O_RDONLY);
    if(fd == -1){perror("Error al abrir el archivo");exit(-1);}

    int block_size = calcular_blk_size(ruta_fichero);
    int capacidad;
    if((read(fd,&capacidad,sizeof(int))) == -1){perror("Error al leer el archivo");exit(-1);}
    crea_sala(capacidad);
    if((read(fd,&capacidad,sizeof(int))) == -1){perror("Error al leer el archivo");exit(-1);}
    num_asientos_ocupados = capacidad;
    
    int* ptr = ptr_ini_sala;
    capacidad = capacidad_sala();
    while((capacidad - block_size) >= 0)
    {
        if((read(fd, ptr, block_size*sizeof(int))) == -1){perror("Error al leer el archivo");exit(-1);}
        capacidad-= block_size;
        ptr+= block_size;
    }
    if((read(fd, ptr, capacidad*sizeof(int))) == -1){perror("Error al leer el archivo");exit(-1);}
    if(close(fd) == -1){perror("Error al cerrar el archivo");}
}

int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{
    int fd = open(ruta_fichero, O_RDONLY);
    if(fd == -1){perror("Error al abrir el archivo");exit(-1);}
    int block_size = calcular_blk_size(ruta_fichero);

    for(int i = 0;i<num_asientos;i++)
    {
        int id = id_asientos[i];
        if(lseek(fd,(id+1)*sizeof(int),SEEK_SET) == -1){perror("Error al mover el puntero del archivo");exit(-1);}
        id = estado_asiento(id);
        if((write(fd, &id, sizeof(int))) == -1){perror("Error al escribir en el archivo");exit(-1);}
    }
    if(close(fd) == -1){perror("Error al cerrar el archivo");}

}
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}

int calcular_blk_size(const char* ruta_fichero)
{
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    if(buf == NULL){perror("Error al reservar memoria"); exit(-1);}
    stat(ruta_fichero, buf);
    int block_size = (buf->st_blksize) / sizeof(int);
    free(buf);
    return block_size;
}