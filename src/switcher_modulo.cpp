#include <const.h>
#include <gestorMenus.h>
#include <M5StickCPlus2.h>
#include "submenu.h"

int modulo;

void enrutador()
{
    M5.update();
    switch (modulo)
    {
    case (MENU_INICIAL):
        mainMenu();
        break;
    case (RELOJ):
        MODULO_RELOJ();
        break;
    case (BLUETOOTH):
        MODULO_BLUETOOTH();
        break;
    case (CRONOMETRO):
        MODULO_CRONOMETRO();
        break;
    case (MENU_SENSORES):
        MODULO_SENSORES();
        break;
    case (NIVEL_SENSOR):
        MODULO_SENSOR_NIVEL();
        break;
    case (MICROFONO):
        MODULO_MICROFONO();
        break;
    case (BAROMETRO):
        MODULO_BAROMETRO();
        break;
    case (I2C_SCAN):
        MODULO_I2C_SCANNER();
        break;
    case (NFC):
        MODULO_NFC();
        break;
    case (RADIOFRECUENCIA):
        MODULO_RADIOFRECUENCIA();
        break;
    default:
        MODULO_SENSORES();
        break;
    }
}