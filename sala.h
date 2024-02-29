#ifndef SALA_H
#define SALA_H
//Reserva asiento retorna el id del asiento o un -1 si hay algun error
int reserva_asiento(int id_persona);
//Libera asiento retorna el id de la persona o un -1 si hay algun error o estaba libre
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
int crear_sala(int capacidad);
//Elimina la sala devuelve 0 si todo a ido bien o un -1 si hay algun error
int elimina_sala();
#endif