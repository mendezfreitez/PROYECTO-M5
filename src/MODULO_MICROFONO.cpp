#include <M5StickCPlus2.h>
#include "const.h"
#include "submenu.h"

void MODULO_MICROFONO()
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