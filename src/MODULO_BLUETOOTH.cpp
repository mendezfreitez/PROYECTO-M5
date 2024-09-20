#include <M5StickCPlus2.h>
#include <const.h>
#include <submenu.h>
#include <BluetoothSerial.h>

BluetoothSerial bt;

void bluetooth()
{
   bt.begin("M5StickCPlus2");
   M5.Lcd.clear();
   M5.Lcd.setCursor(10, 40);
   M5.Lcd.print("Bluetooth en desarrollo");
   while (!btnAtras())
   {
   }
   MODULO_SENSORES();
}