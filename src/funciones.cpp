#include <M5StickCPlus2.h>
#include <WiFi.h>
#include "submenu.h"
#include "const.h"

int porc_bateria;

void bateria()
{
  porc_bateria = M5.Power.getBatteryLevel();
  M5.Lcd.setTextColor(ORANGE, BLACK);
  M5.Lcd.setCursor(M5.Lcd.width() - 19, M5.Lcd.height() - 10);
  M5.Lcd.print(porc_bateria);
  M5.Lcd.setTextColor(WHITE, BLACK);
}

void wifiConn(const char *uuid, const char *pass)
{
  M5.Lcd.drawRect(0, 0, 240, 135, GREEN);
  M5.Lcd.drawRect(1, 1, 239, 134, GREEN);
  delay(700);
  WiFi.begin(uuid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
  }
  M5.Lcd.drawRect(0, 0, 240, 135, BLACK);
  M5.Lcd.drawRect(1, 1, 239, 134, BLACK);
}

void limpiarPantalla(int x, int y)
{
  M5.Lcd.clear();
  M5.Lcd.setCursor(x, y);
}

void buzzer(int freq, int ms)
{
  M5.Speaker.tone(freq, ms);
}
void destello(int color, int ms)
{
  // M5.Lcd.clear(color);
  // delay(ms);
  // M5.Lcd.clear(BLACK);
  M5.Power.setLed(50);
  delay(ms);
  M5.Power.setLed(0);
}

void alertaBorde(int color)
{
  for (int i = 0; i <= 6; i++)
  {
    M5.Lcd.drawRect(i, i, 239 - i, 134 - i, color);
  }
  delay(1000);
  for (int i = 0; i <= 6; i++)
  {
    M5.Lcd.drawRect(i, i, 239 - i, 134 - i, BLACK);
  }
}

void irAtras()
{
  if (capa == 2)
  {
    idx_capa2 = 0;
  }
  if (capa == 1)
  {
    idx_capa1 = 0;
  }
  if (capa > 0)
  {
    capa--;
  }
}

bool mirarBtnIrAtras(int mod = MENU_INICIAL)
{
  if (digitalRead(BUTON_PIN_C) == 0)
  {
    while (digitalRead(BUTON_PIN_C) == 0)
    {
    }
    modulo = mod;
    return true;
  }
  return false;
}

void detener()
{
  if (M5.BtnB.wasPressed())
  {
    iniciar = 0;
  }
}