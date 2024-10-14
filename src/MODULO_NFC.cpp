#include <M5StickCPlus2.h>
#include <Adafruit_PN532.h>
#include "submenu.h"
#include <const.h>
#include <Wire.h>

Adafruit_PN532 nfc(26, 25);
String tagId = "None", dispTag = "None";
uint8_t idTarjeta[] = {0, 0, 0, 0, 0, 0, 0};
uint8_t idTarjetaLong;
bool success;
bool resp;
int bloqueNro;

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

void imprimirHex(const byte *id, int dataLong)
{
  uint32_t szPos;
  for (szPos = 0; szPos < dataLong; szPos++)
  {
    if (id[szPos] <= 0xF)
    {
      Serial.print(F("0"));
      M5.Lcd.print(F("0"));
    }
    Serial.print(id[szPos], HEX);
    M5.Lcd.print(id[szPos], HEX);

    if ((dataLong > 1) && (szPos != dataLong - 1))
    {
      Serial.print(F(" "));
      M5.Lcd.print(F(" "));
    }
  }
  Serial.println();
  M5.Lcd.println();
}

void leerPaginas(int nroBytes)
{
  uint8_t keya[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t data[nroBytes];
  if (nroBytes == 16)
  {
    resp = nfc.mifareclassic_AuthenticateBlock(idTarjeta, idTarjetaLong, bloqueNro, 0, keya);
    if (resp)
    {
      nfc.mifareclassic_ReadDataBlock(bloqueNro, data);
    }
  }
  else
  {
    nfc.mifareultralight_ReadPage(bloqueNro, data);
  }

  Serial.printf("Bloque: %i\n", bloqueNro);
  imprimirHex(data, nroBytes);
  Serial.println("");
  delay(1000);
}

void lecturaTarjeta()
{
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &idTarjeta[0], &idTarjetaLong);

  if (success)
  {
    destello(GREEN, 200);
    Serial.print(idTarjetaLong, DEC);
    Serial.println(" bytes");

    limpiarPantalla(0, 10);
    M5.Lcd.print("");
    M5.Lcd.print(idTarjetaLong, DEC);
    M5.Lcd.println(" bytes");
    M5.Lcd.printf("%.0f posiciones\n", pow(2, idTarjetaLong));

    imprimirHex(idTarjeta, idTarjetaLong);

    M5.Lcd.setTextSize(1.1);
    leerPaginas(idTarjetaLong == 4 ? 16 : 32);
    delay(1000);
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