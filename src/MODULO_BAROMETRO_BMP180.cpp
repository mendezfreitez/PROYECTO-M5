#include <M5StickCPlus2.h>
#include <Wire.h>
#include "submenu.h"
#include "const.h"

#define SDA_PIN 25
#define SCL_PIN 26
#define BYTES 2
#define BMP180_DIR 0x77

void inicializarBMP180()
{
    Wire.beginTransmission(BMP180_DIR);
    Wire.write(0xAA); // Dirección del primer registro de calibración
    Wire.endTransmission();

    Wire.requestFrom(BMP180_DIR, 22); // Leer 22 bytes de los registros de calibración

    if (Wire.available() == 22)
    {
        // Lectura de los registros de calibración
        int AC1 = (Wire.read() << 8) | Wire.read();
        int AC2 = (Wire.read() << 8) | Wire.read();
        int AC3 = (Wire.read() << 8) | Wire.read();
        unsigned int AC4 = (Wire.read() << 8) | Wire.read();
        unsigned int AC5 = (Wire.read() << 8) | Wire.read();
        unsigned int AC6 = (Wire.read() << 8) | Wire.read();
        int B_1 = (Wire.read() << 8) | Wire.read();
        int B2 = (Wire.read() << 8) | Wire.read();
        int MB = (Wire.read() << 8) | Wire.read();
        int MC = (Wire.read() << 8) | Wire.read();
        int MD = (Wire.read() << 8) | Wire.read();

        // Puedes guardar estos valores en variables globales o en una estructura
        Serial.println("Registros de calibración leídos:");
        Serial.print("AC1: ");
        Serial.println(AC1);
        Serial.print("AC2: ");
        Serial.println(AC2);
        Serial.print("AC3: ");
        Serial.println(AC3);
        Serial.print("AC4: ");
        Serial.println(AC4);
        Serial.print("AC5: ");
        Serial.println(AC5);
        Serial.print("AC6: ");
        Serial.println(AC6);
        Serial.print("B1: ");
        Serial.println(B_1);
        Serial.print("B2: ");
        Serial.println(B2);
        Serial.print("MB: ");
        Serial.println(MB);
        Serial.print("MC: ");
        Serial.println(MC);
        Serial.print("MD: ");
        Serial.println(MD);
    }
    else
    {
        Serial.println("Error al leer los registros de calibración.");
    }
}

void MODULO_BAROMETRO()
{
    Serial.begin(9600);
    Wire.begin(SDA_PIN, SCL_PIN);
    limpiarPantalla(10, 10);
    delay(1000);
    Serial.print("--- INICIANDO ---");

    inicializarBMP180();

    while (!mirarBtnIrAtras(MENU_SENSORES))
    {
        Wire.beginTransmission(BMP180_DIR);
        Wire.write(0x2E);
        Wire.endTransmission();
        delay(7);

            Wire.requestFrom(BMP180_DIR, 2);
        // if (Wire.available() == 2)
        // {
        int data = Wire.read();
        int data2 = Wire.read();

        Serial.print("Temp1= ");
        Serial.println(data);
        Serial.print("Temp2= ");
        Serial.println(data);
        // }
        // else
        // {
        // Serial.println("No se recibieron suficientes datos.");
        // }

        delay(3000); // Espera un segundo antes de la próxima lectura
    }
}
