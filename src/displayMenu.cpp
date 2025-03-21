#include <M5StickCPlus2.h>
#include "submenu.h"
#include "const.h"

int cursor_Y = 0;

void displayMenu(itemMenu arrItems[], int index_actual, int length)
{
  M5.Lcd.setTextSize(1.1);
  M5.Lcd.setCursor(0, 0);
  for (int i = 0; i < length; i++)
  {
    cursor_Y = 1 + 11 * i;
    if (i == index_actual)
    {
      M5.Lcd.setTextColor(ORANGE, BLACK);
    }
    else
    {
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
    M5.Lcd.setCursor(1, cursor_Y);
    M5.Lcd.print(arrItems[i].nombre.c_str());
  }
  bateria();
}