#include <M5StickCPlus2.h>
#include <submenu.h>
#include <const.h>

void MODULO_TRANSCEPTOR(){
  limpiarPantalla(40,60);
  M5.Lcd.print("EN DESAROLLO");
  while (!mirarBtnIrAtras(MENU_SENSORES))
  {
  }
}