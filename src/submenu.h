#include <string>
void displayMenu(const char* const* arrItems, int index_actual, int length);
void displaySubMenu(int indx);
void funcionCronometro(void *parameter);
void irAtras();
bool mirarBtnIrAtras();
void detener();
void MODULO_CRONOMETRO();
void MODULO_SENSORES();
void MODULO_RELOJ();
void SENSOR_NIVEL();
void bateria();
void wifiConn(const char* uuid, const char* pass);
void alertaBorde(int color);
void bluetooth();
bool btnAtras();