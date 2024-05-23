#ifndef MAIN_H
#define MAIN_H

void* reserva_hilo(void* arg);
void* libera_hilo(void* arg);
void* estado_sala_hilo(void* arg);
int id_aleatorio(int tipo_id);
void estado_sala();

#endif