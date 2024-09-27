#include <M5StickCPlus2.h>
#include <math.h>
#include "submenu.h"
#include "const.h"

itemMenu MENU_SENSORES_ITEMS[] = {
    {"SENSOR DE NIVEL MPU6886", NIVEL_SENSOR},
    {"MICROFONO SPM1423", MICROFONO},
    {"SENSOR 4", 0}};

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
  displayMenu(MENU_SENSORES_ITEMS, idx_capa1, 3);
  while (modulo == MENU_SENSORES)
  {
    M5.update();
    if (M5.BtnA.wasPressed())
    {
      modulo = MENU_SENSORES_ITEMS[idx_capa1].modulo;
    }
    if (M5.BtnB.wasPressed())
    {
      idx_capa1 = (idx_capa1 + 1) % 3;
      displayMenu(MENU_SENSORES_ITEMS, idx_capa1, 3);
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