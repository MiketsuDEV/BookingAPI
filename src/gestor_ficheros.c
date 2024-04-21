#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "error_manager.h"
#include "gestor_ficheros.h"

int guarda_estado_sala(const char* ruta_fichero, bool oflag)
{
    if(oflag){
        int fd = open(ruta_fichero, O_WRONLY | O_CREAT | O_TRUNC, 644);
    }else{
        int fd = open(ruta_fichero, O_WRONLY | O_CREAT | O_EXCL);
    }
    struct stat *buf;
    buf = malloc(sizeof(struct stat));
    stat(ruta_fichero, buf);
    unsigned long block_size = buf->st_blksize;
    block_size /= sizeof(int);
    free(buf);
    close(ruta_fichero);
}
int recupera_estado_sala(const char* ruta_fichero)
{
    
}
int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos)
{

}