#include <M5StickCPlus2.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include "submenu.h"
#include "const.h"

#define SDA_PIN 25
#define SCL_PIN 26
#define BYTES 2
#define BMP180_DIR 0x77

SFE_BMP180 bmp;
double temp;

void inicializarBMP180()
{
    M5.Lcd.setTextSize(2);
    Serial.begin(9600);
    limpiarPantalla(10, 10);
    Wire.begin(SDA_PIN, SCL_PIN);
    delay(500);
    if (!bmp.begin())
    {
        limpiarPantalla(42, 60);
        M5.Lcd.setTextSize(1.1);
        M5.Lcd.print("Dispositivo no encontrado");
        modulo = MENU_SENSORES;
        delay(4000);
    }
}

void printTemperatura()
{
    limpiarPantalla(0, 10);
    M5.Lcd.println("Temp");
    M5.Lcd.print(temp, 2);
    M5.Lcd.println(" C");
    M5.Lcd.print((9.0 / 5.0) * temp + 32.0, 2);
    M5.Lcd.print(" F");
    delay(100);
}

void MODULO_BAROMETRO()
{
    inicializarBMP180();

    while (modulo == BAROMETRO)
    {
        int status = bmp.startTemperature();

        if (status != 0)
        {
            delay(10);

            status = bmp.getTemperature(temp);
            if (status != 0)
            {
                printTemperatura();
            }
        }
        mirarBtnIrAtras(MENU_SENSORES);
    }
    M5.Lcd.setTextSize(1.1);
}
