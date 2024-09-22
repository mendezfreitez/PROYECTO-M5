#include <M5StickCPlus2.h>
#include <const.h>
#include <submenu.h>
#include <BluetoothSerial.h>

BluetoothSerial bt;

void verConexion()
{
   if (bt.hasClient())
   {
      limpiarPantalla(48, 60);
      M5.Lcd.print("Dispositivo conectado!!!");
      M5.Power.setLed(50);
      delay(350);
      M5.Power.setLed(0);
      delay(350);
      M5.Power.setLed(50);
      delay(350);
      M5.Power.setLed(0);
      delay(350);
      limpiarPantalla(0, 0);
      while (!btnAtras())
      {
         if (bt.available())
         {
            String cadena = bt.readString();
            limpiarPantalla(10, 10);
            M5.Lcd.println(cadena);
         }
      }
      bt.disconnect();
      limpiarPantalla(40, 60);
      M5.Lcd.print("Dispositivo desconectado!!!");
      delay(2000);
      bluetooth();
   }
}

void bluetooth()
{
   bt.begin("M5StickCPlus2");
   M5.Lcd.clear();
   M5.Lcd.setCursor(54, 60);
   M5.Lcd.print("Esperando conexion...");
   while (!btnAtras())
   {
      verConexion();
   }
   MODULO_SENSORES();
}