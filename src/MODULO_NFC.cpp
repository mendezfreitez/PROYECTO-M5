#include <M5StickCPlus2.h>
#include <Adafruit_PN532.h>
#include <submenu.h>
#include <const.h>
#include <Wire.h>

void setup_nfc()
{
  Wire.begin(25, 26);
  Adafruit_PN532 nfc(25, 26);
  nfc.begin();
  Serial.begin(9600);
  int version = nfc.getFirmwareVersion();
  limpiarPantalla(42, 60);

  if (!version)
  {
    M5.Lcd.setTextSize(1.1);
    M5.Lcd.print("Dispositivo no encontrado");
    modulo = MENU_SENSORES;
    delay(4000);
  }
  else
  {
    M5.Lcd.print(version);
    Serial.print(version);
  }
}

void MODULO_NFC()
{
  setup_nfc();
  // limpiarPantalla(40, 60);
  // M5.Lcd.print("EN DESAROLLO");
  while (!mirarBtnIrAtras(MENU_SENSORES))
  {
  }
}