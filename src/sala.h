#ifndef SALA_H
#define SALA_H
//Reserva asiento retorna el id del asiento o un -1 si hay algun error
int reserva_asiento(int id_persona);
//Libera asiento retorna el id de la persona o un -1 si hay algun error o un 0 si estaba libre
int libera_asiento(int id_asiento);
//Estado asiento retorna el id de la persona, 0 si esta libre o un -1 si hay algun error
int estado_asiento(int id_asiento);
//Devuelve el nº de asientos libres
int asientos_libres();
//Devuelve el nº de asientos ocupados
int asientos_ocupados();
//Devuelve la capacidad maxima de la sala
int capacidad_sala();
//Crea la sala devuelve la capacidad de la sala o un -1 si hay algun error
int crea_sala(int capacidad);
//Elimina la sala devuelve 0 si todo a ido bien o un -1 si hay algun error
int elimina_sala();
int guarda_estado_sala(const char* ruta_fichero);
int recupera_estado_sala(const char* ruta_fichero);
int guarda_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos);
int recupera_estadoparcial_sala(const char* ruta_fichero, int num_asientos, int* id_asientos);
int calcular_blk_size(const char* ruta_fichero);
#endif
