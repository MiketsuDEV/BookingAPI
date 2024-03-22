#ifndef TEST_SALA_H
#define TEST_SALA_H
void INICIO_TEST(const char *titulo_test);
void FIN_TEST(const char *titulo_test);
void test_reserva_basica();
void test_integridad_sala_creada();
void test_reserva_multiple();
void estado_sala();
void sentarse(int id_persona);
void levantarse(int id_asiento);
void reserva_multiple(int npersonas, int *lista_id);
void liberar_multiple(int nasientos, int *lista_id_asiento);
void ejecuta_tests();
#endif