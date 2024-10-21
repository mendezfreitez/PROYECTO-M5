#include <M5StickCPlus2.h>
#include <submenu.h>
#include <const.h>
#include <CC1101_RF.h>

CC1101 radio;

void MODULO_RADIOFRECUENCIA()
{
    radio.begin(433);
    limpiarPantalla(10, 60);
    M5.Lcd.print("EN DESAROLLO");
    while (!mirarBtnIrAtras(MENU_SENSORES))
    {
    }
}