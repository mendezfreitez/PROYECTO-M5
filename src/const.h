#include <string>

#ifndef CONST_H
#define CONST_H

// extern const char *MENU_INICIAR_ITEMS[];
// extern const char *MENU_PRINCIPAL_ITEMS[];
extern char MENU_ITEMS[];
extern int idx_capa0;
extern int idx_capa1;
extern int idx_capa2;
extern int cursor_Y;
extern int capa;
extern const int BUTON_PIN_C;
extern const int BUTON_PIN_A;
extern int iniciar;
extern int porc_bateria;
extern int modulo;
// using namespace std;

struct itemMenu
{
    std::string nombre;
    int modulo;
};

#endif

#ifndef CONST_MODULO
#define CONST_MODULO

extern const int NIVEL_SENSOR = 1;
extern const int RELOJ = 2;
extern const int BLUETOOTH = 3;
extern const int CRONOMETRO = 4;
extern const int MENU_SENSORES = 5;
extern const int MICROFONO = 6;
extern const int MENU_INICIAL = 0;
#endif
