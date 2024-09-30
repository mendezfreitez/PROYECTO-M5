#include <M5StickCPlus2.h>
#include <Wire.h>
#include "submenu.h"
#include "const.h"

#define SDA_PIN 25
#define SCL_PIN 26

void MODULO_BAROMETRO()
{
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN, 115200);
    limpiarPantalla(10, 10);
    M5.Lcd.print("este es el modulo BAROMETRICO");
    Wire.beginTransmission(0x77);
    if (Wire.endTransmission() != 0)
    {
        Serial.println("No se encontró el BMP180.");
        // while (1);
    }
    while (!mirarBtnIrAtras(MENU_INICIAL))
    {
    }
}