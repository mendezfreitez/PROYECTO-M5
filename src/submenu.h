#include "structs.h"

void displayMenu(itemMenu arrItems[], int index_actual, int length);
void displaySubMenu(int indx);
void funcionCronometro(void *parameter);
void irAtras();
bool mirarBtnIrAtras(int mod);
void detener();
void MODULO_CRONOMETRO();
void MODULO_MICROFONO();
void MODULO_SENSORES();
void MODULO_BAROMETRO();
void MODULO_RELOJ();
void MODULO_SENSOR_NIVEL();
void bateria();
void wifiConn(const char* uuid, const char* pass);
void alertaBorde(int color);
void MODULO_BLUETOOTH();
bool btnAtras();
void limpiarPantalla(int x, int y);