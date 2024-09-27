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
#endif

#ifndef CONST_MODULO
#define CONST_MODULO

constexpr int NIVEL_SENSOR = 1;
constexpr int RELOJ = 2;
constexpr int BLUETOOTH = 3;
constexpr int CRONOMETRO = 4;
constexpr int MENU_SENSORES = 5;
constexpr int MICROFONO = 6;
constexpr int MENU_INICIAL = 0;
#endif
