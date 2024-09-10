#include <M5StickCPlus2.h>
#include "submenu.h"
#include "const.h"

int cont_global = 0;

void displaySubMenu(int indx) {
  M5.Lcd.clear();
  M5.Lcd.setCursor(1, 1);
  switch (indx) {
    case 0:
      MODULO_RELOJ();
      break;
    case 1:
      MODULO_CRONOMETRO();
      break;
    case 2:
      MODULO_SENSORES();
      break;
  }
}