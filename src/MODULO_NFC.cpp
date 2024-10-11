#include <M5StickCPlus2.h>
#include <Adafruit_PN532.h>
#include "submenu.h"
#include <const.h>
#include <Wire.h>

Adafruit_PN532 nfc(26, 25);
String tagId = "None", dispTag = "None";
byte nuidPICC[4];

bool setup_nfc()
{
  Wire.begin(26, 25);
  nfc.begin();
  Serial.begin(9600);
  uint32_t version = nfc.getFirmwareVersion();
  limpiarPantalla(42, 60);

  if (!version)
  {
    M5.Lcd.setTextSize(1.1);
    M5.Lcd.print("Dispositivo no encontrado");
    modulo = MENU_SENSORES;
    delay(4000);
    return false;
  }
  else
  {
    limpiarPantalla(0, 10);
    // M5.Lcd.print(version);
    Serial.print(version);
    Serial.print("Chip encontrado: PN5");
    Serial.println((version >> 24) & 0xFF, HEX);
    Serial.print("Version del firmware: ");
    Serial.print((version >> 16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((version >> 8) & 0xFF, DEC);

    M5.Lcd.print("Chip encontrado: PN5");
    M5.Lcd.println((version >> 24) & 0xFF, HEX);
    M5.Lcd.print("Version del firmware: ");
    M5.Lcd.print((version >> 16) & 0xFF, DEC);
    M5.Lcd.print('.');
    M5.Lcd.println((version >> 8) & 0xFF, DEC);
    return true;
  }
}

String tagToString(byte id[4])
{
  String tagId = "";
  for (byte i = 0; i < 4; i++)
  {
    if (i < 3)
      tagId += String(id[i]) + ".";
    else
      tagId += String(id[i]);
  }
  return tagId;
}

void lecturaTarjeta()
{
  bool success;
  uint8_t idTarjeta[] = {0, 0, 0, 0, 0, 0, 0};
  uint8_t idTarjetaLong;
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &idTarjeta[0], &idTarjetaLong);

  if (success)
  {
    buzzer(5000, 150);
    Serial.print("Longitud: ");
    Serial.print(idTarjetaLong, DEC);
    Serial.println(" bytes");

    limpiarPantalla(0, 10);
    M5.Lcd.print("Longitud: ");
    M5.Lcd.print(idTarjetaLong, DEC);
    M5.Lcd.println(" bytes");
    // Serial.print("UID Value: ");
    for (uint8_t i = 0; i < idTarjetaLong; i++)
    {
      nuidPICC[i] = idTarjeta[i];
      // Serial.print(" "); Serial.print(idTarjeta[i], DEC);
    }
    tagId = tagToString(nuidPICC);
    dispTag = tagId;
    Serial.print(F("Etiqueta: "));
    Serial.println(tagId);
    Serial.println();
    
    M5.Lcd.print(F("Etiqueta: "));
    M5.Lcd.println(tagId);
    delay(1000); // 1 second halt
  }
  else
  {
    Serial.println("Error al leer tarjeta");
    M5.Lcd.print("Error al leer tarjeta");
  }
}

void MODULO_NFC()
{
  if (setup_nfc())
  {
    while (!mirarBtnIrAtras(MENU_SENSORES))
    {
      lecturaTarjeta();
    }
  }
}