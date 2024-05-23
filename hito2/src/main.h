#ifndef MAIN_H
#define MAIN_H

void* reserva_libera_hilos(void* arg);
void* estado_sala_hilo(void* arg);
int id_aleatorio(int tipo_id);
void estado_sala();

#endif