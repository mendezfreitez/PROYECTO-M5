#include <M5StickCPlus2.h>
#include <BluetoothSerial.h>
#include <string>
#include <vector>
#include "submenu.h"
#include "const.h"

using namespace std;
BluetoothSerial bt;
int x;
int y;
int separadorIdx;
int caracterTerminador;
int y_0 = 0;
int x0 = 0;

void comando(string com)
{
   if (com == "d")
   {
      M5.Lcd.clearDisplay(BLACK);
   }
   if (com == "r")
   {
      x0 = 0;
      y_0 = 0;
   }
}

void verConexion()
{
   if (bt.hasClient())
   {

      limpiarPantalla(20, 110);
      M5.Lcd.print("Dispositivo\nConectado!!!");
      M5.Power.setLed(50);
      delay(350);
      M5.Power.setLed(0);
      delay(350);
      M5.Power.setLed(50);
      delay(350);
      M5.Power.setLed(0);
      delay(350);
      limpiarPantalla(0, 0);
      while (!mirarBtnIrAtras(MENU_INICIAL) && bt.hasClient())
      {
         if (bt.available())
         {
            String cadenaLlegada = bt.readStringUntil('.');
            string cadena = (cadenaLlegada).c_str();

            if (cadenaLlegada == "d" || cadenaLlegada == "r")
            {
               comando(cadena);
            }
            else
            {
               x = stoi(cadena.substr(0, cadena.find('-')));
               y = stoi(cadena.substr(cadena.find('-') + 1, cadena.find('.')));
               if (x0 == 0)
               {
                  x0 = x;
                  y_0 = y;
               }
               else
               {
                  M5.Lcd.drawLine(x0, y_0, x, y, ORANGE);
                  x0 = x;
                  y_0 = y;
               }
            }
         }
      }
      bt.disconnect();
      limpiarPantalla(0, 110);
      M5.Lcd.print("Dispositivo\nDesconectado!!!");
      delay(2000);
   }
}

void MODULO_BLUETOOTH()
{
   Serial.begin(9600);
   M5.Lcd.setRotation(0);
   bt.begin("M5StickCPlus2");
   M5.Lcd.clear();
   M5.Lcd.setCursor(0, 110);
   M5.Lcd.print("Esperando\nConexion...");
   while (!mirarBtnIrAtras(MENU_INICIAL))
   {
      verConexion();
   }
   M5.Lcd.clearDisplay();
}