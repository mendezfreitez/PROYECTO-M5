#include <M5StickCPlus2.h>
#include <Wire.h>
#include "submenu.h"
#include "const.h"

#define SDA_PIN 25
#define SCL_PIN 26

void MODULO_BAROMETRO()
{
    Serial.begin(9600);
    Wire.begin(SDA_PIN, SCL_PIN);

    limpiarPantalla(10, 10);
    // M5.Lcd.print("este es el modulo BAROMETRICO");
    Wire.beginTransmission(0x77);
    // while (!mirarBtnIrAtras(MENU_INICIAL))
    //     if (Wire.endTransmission() != 0)
    //     {
    //         Serial.println("No se encontró el BMP180.");
    //     }
    //     Wire.read();
    // {
    // }

    byte error, address;
    int nDevices = 0;

    Serial.println("Scanning...");
    for (address = 1; address < 127; address++)
    {
        limpiarPantalla(10, 10);

        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println("  !");
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("Done\n");
    }
    delay(5000);
}
