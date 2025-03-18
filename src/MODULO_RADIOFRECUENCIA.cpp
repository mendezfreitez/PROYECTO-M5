#include <M5StickCPlus2.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <submenu.h>
#include <const.h>

ELECHOUSE_CC1101 cc;

void setup_Radio()
{
    // cc.setSpiPin(26, 33, 32, 25);

    cc.Init();

    if (cc.getCC1101())
    {
        Serial.println("Dispositivo encontrado");
    }
    else
    {
        Serial.println("No se encontro dispositivo");
        Serial.println(cc.getCC1101());
    }
}

void MODULO_RADIOFRECUENCIA()
{
    Serial.begin(9600);
    limpiarPantalla(10, 60);
    M5.Lcd.print("EN DESAROLLO");

    // cc.getCC1101();
    setup_Radio();

    while (!mirarBtnIrAtras(MENU_SENSORES))
    {
    }
}