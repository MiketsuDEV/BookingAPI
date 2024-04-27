#ifndef GESTOR_FICHEROS_H
#define GESTOR_FICHEROS_H
int guarda_estado_sala(const char* ruta_fichero, bool oflag);
int recupera_estado_sala(const char* ruta_fichero);
int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos);
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos);
int calcular_blk_size(const char* ruta_fichero);
#endif