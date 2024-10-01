#include <M5StickCPlus2.h>
#include <Wire.h>
#include "submenu.h"
#include "const.h"

byte err, add;

void MODULO_I2C_SCANNER()
{
    Wire.begin(25, 26);
    Serial.begin(9600);
    limpiarPantalla(10, 10);
    for (add = 1; add < 127; add++)
    {
        Wire.beginTransmission(add);
        err = Wire.endTransmission();

        if (err == 0)
        {
            M5.Lcd.print("Dispositivo encontrado en: 0x");
            if (add < 16)
            {
                M5.Lcd.print("0");
            }
            M5.Lcd.print(add, HEX);
        }
        else if (err == 4)
        {
            M5.Lcd.print("Error desconocido en 0x");
            if (add < 16)
            {
                M5.Lcd.print("0");
            }
            M5.Lcd.println(add, HEX);
        }
    }
    delay(5000);
    while (!mirarBtnIrAtras(MENU_INICIAL))
    {
    }
    M5.Lcd.clearDisplay();
}