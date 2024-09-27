#include "const.h"
#include <M5StickCPlus2.h>
#include <math.h>
#include "submenu.h"

itemMenu MENU_SENSORES_ITEMS[] = {
    {"SENSOR DE NIVEL MPU6886", NIVEL_SENSOR},
    {"MICROFONO SPM1423", MICROFONO},
    {"SENSOR 4", 0}};

void microfono()
{
  capa++;
  M5.Lcd.clearDisplay();
  // M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(10, 60);
  M5.Lcd.print("Aca se enciende el microfono...");
  M5.Mic.begin();
  while (capa == 2)
  {
    mirarBtnIrAtras();
  }
  M5.Mic.end();
  M5.Lcd.setTextSize(1.1);
  MODULO_SENSORES();
}

void displaySensor(int idx)
{
  switch (idx)
  {
  case 0:
    SENSOR_NIVEL();
    break;
  case 1:
    microfono();
    break;
  case 2:
    bluetooth();
    break;
  }
}

void MODULO_SENSORES()
{
  M5.Lcd.clearDisplay();
  displayMenu(MENU_SENSORES_ITEMS, idx_capa1, 4);
  while (capa == 1)
  {
    M5.update();
    if (M5.BtnA.wasPressed())
    {
      displaySensor(idx_capa1);
    }
    if (M5.BtnB.wasPressed())
    {
      idx_capa1 = (idx_capa1 + 1) % 4;
      displayMenu(MENU_SENSORES_ITEMS, idx_capa1, 4);
    }
    mirarBtnIrAtras();
  }
  M5.Lcd.clearDisplay();
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