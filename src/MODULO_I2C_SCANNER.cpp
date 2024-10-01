#include <M5StickCPlus2.h>
#include <Wire.h>
#include "submenu.h"
#include "const.h"

byte err, add;

void MODULO_I2C_SCANNER()
{
    int dispositivos = 0;
    Wire.begin(25, 26);
    Serial.begin(9600);
    limpiarPantalla(10, 10);
    for (add = 1; add < 127; add++)
    {
        Wire.beginTransmission(add);
        err = Wire.endTransmission();

        if (err == 0)
        {
            M5.Lcd.print("Dispositivo en -> 0x");
            if (add < 16)
            {
                M5.Lcd.print("0");
            }
            M5.Lcd.print(add, HEX);
            dispositivos++;
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
    if (dispositivos == 0)
    {
        limpiarPantalla(28, 60);
        M5.Lcd.print("No se encontraron dispositivos");
    }

    while (!mirarBtnIrAtras(MENU_SENSORES))
    {
    }
    M5.Lcd.clearDisplay();
}