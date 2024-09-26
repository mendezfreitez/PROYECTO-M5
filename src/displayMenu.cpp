#include "submenu.h"
#include <M5StickCPlus2.h>
#include "const.h"

int cursor_Y = 0;

void displayMenu(itemMenu arrItems[], int index_actual, int length) {
  M5.Lcd.setTextSize(1.1);
  for (int i = 0; i < length; i++) {
    cursor_Y = 1 + 11 * i;
    M5.Lcd.fillRect(1, cursor_Y, M5.Lcd.width(), 8, BLACK);
    if (i == index_actual) {
      M5.Lcd.setTextColor(ORANGE, BLACK);
    } else {
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
    M5.Lcd.setCursor(1, cursor_Y);
    M5.Lcd.print(arrItems[i].nombre);
  }
  bateria();
}