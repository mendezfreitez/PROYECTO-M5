#include <M5StickCPlus2.h>
#include <Adafruit_PN532.h>
#include "submenu.h"
#include <const.h>
#include <Wire.h>

Adafruit_PN532 nfc(26, 25);
String tagId = "None", dispTag = "None";
// byte nuidPICC[4];

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

void leerPaginas()
{
  // uint8_t bufferPagina[4];
  // int paginas = 48;
  // for (int p = 0; p < paginas; p++)
  // {
  //   Serial.println(nfc.ntag2xx_ReadPage(p, bufferPagina));
  //   if (nfc.ntag2xx_ReadPage(p, bufferPagina) == 1)
  //   {
  //     Serial.print("P ");
  //     Serial.print(p);
  //     Serial.print("= ");
  //     for (int i = 0; i < sizeof(bufferPagina); i++)
  //     {
  //       Serial.print(bufferPagina[i], HEX);
  //       Serial.print(":");
  //     }
  //     Serial.println("");
  //   }
  // }
  uint8_t apdubuffer[255] = {}, apdulen = 0;
  // uint8_t ppse[] = {0x8E, 0x6F, 0x23, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x11, 0xBF, 0x0C, 0x0E, 0x61, 0x0C, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10, 0x87, 0x01, 0x01, 0x90, 0x00};
  nfc.AsTarget();
  (void)nfc.getDataTarget(apdubuffer, &apdulen); // Read initial APDU
  if (apdulen > 0)
  {
    for (uint8_t i = 0; i < apdulen; i++)
    {
      Serial.print(" 0x");
      Serial.print(apdubuffer[i], HEX);
    }
    Serial.println("");
  }
}

void lecturaTarjeta()
{
  bool success;
  uint8_t idTarjeta[] = {0, 0, 0, 0, 0, 0, 0};

  uint8_t idTarjetaLong;
  byte nuidPICC[idTarjetaLong];
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &idTarjeta[0], &idTarjetaLong);

  if (success)
  {
    destello(GREEN, 200);
    // Serial.print("Valor: ");
    // Serial.println(idTarjeta);
    Serial.print("Longitud: ");
    Serial.print(idTarjetaLong, DEC);
    Serial.println(" bytes");

    limpiarPantalla(0, 10);
    M5.Lcd.print("Longitud: ");
    M5.Lcd.print(idTarjetaLong, DEC);
    M5.Lcd.println(" bytes");
    // Serial.print("UID Value: "

    String tagId = "";

    Serial.println("-----------------");
    for (uint8_t i = 0; i < idTarjetaLong; i++)
    {
      Serial.println(idTarjeta[i], HEX);
      nuidPICC[i] = idTarjeta[i];
      // Serial.print(" "); Serial.print(idTarjeta[i], DEC);
      if ((i + 1) < idTarjetaLong)
        tagId += String(idTarjeta[i]) + ":";
      else
        tagId += String(idTarjeta[i]);
    }
    Serial.println("-----------------");
    // tagId = tagToString(nuidPICC);
    // dispTag = tagId;
    Serial.print(F("Etiqueta: "));
    Serial.println(tagId);
    Serial.println();

    M5.Lcd.print(F("Etiqueta: "));
    M5.Lcd.println(tagId);

    leerPaginas();
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