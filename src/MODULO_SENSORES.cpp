#include <M5StickCPlus2.h>
#include <math.h>
#include "submenu.h"
#include "const.h"

itemMenu MENU_SENSORES_ITEMS[] = {
    {"NFC", NFC},
    {"SENSOR DE NIVEL MPU6886", NIVEL_SENSOR},
    {"MICROFONO SPM1423", MICROFONO},
    {"BAROMETRO BMP180", BAROMETRO},
    {"-- I2C SCANNER --", I2C_SCAN}};

void microfono()
{
  M5.Lcd.clearDisplay();

  M5.Lcd.setCursor(10, 60);
  M5.Lcd.print("Aca se enciende el microfono...");
  M5.Mic.begin();
  while (modulo == MICROFONO)
  {
    mirarBtnIrAtras(MENU_SENSORES);
  }
  M5.Mic.end();
  M5.Lcd.setTextSize(1.1);
}

void MODULO_SENSORES()
{
  M5.Lcd.clearDisplay();
  displayMenu(MENU_SENSORES_ITEMS, idx_capa1, 5);
  while (modulo == MENU_SENSORES)
  {
    M5.update();
    if (M5.BtnA.wasPressed())
    {
      modulo = MENU_SENSORES_ITEMS[idx_capa1].modulo;
    }
    if (M5.BtnB.wasPressed())
    {
      idx_capa1 = (idx_capa1 + 1) % 5;
      displayMenu(MENU_SENSORES_ITEMS, idx_capa1, 5);
    }
    mirarBtnIrAtras(MENU_INICIAL);
  }
}

bool btnAtras()
{
  if (digitalRead(BUTON_PIN_C) == 0)
  {
    while (digitalRead(BUTON_PIN_C) == 0)
    {
    }
    return true;
  }
  return false;
}