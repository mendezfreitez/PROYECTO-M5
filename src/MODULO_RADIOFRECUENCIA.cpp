#include <M5StickCPlus2.h>
#include <submenu.h>
#include <const.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>


void MODULO_RADIOFRECUENCIA()
{
    limpiarPantalla(10, 60);
    M5.Lcd.print("EN DESAROLLO");
    while (!mirarBtnIrAtras(MENU_SENSORES))
    {
    }
}