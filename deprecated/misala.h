#ifndef MISALA_H
#define MISALA_H

int verifica_ruta(const char *ruta, const char *proceso);
int procesar_orden(int argc, char *argv[]);
int procesar_crea(char* ruta, int capacidad);
int procesar_reserva(char* ruta, int argc, char *argv[]);
int procesar_anula(char* ruta, int argc, char *argv[]);
int procesar_estado(char* ruta);

#endif