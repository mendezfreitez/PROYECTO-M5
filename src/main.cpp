#include <M5StickCPlus2.h>
#include "gestorMenus.h"
#include "submenu.h"
#include "const.h"

const int BUTON_PIN_C = 35;
const int BUTON_PIN_A = 37;
int idx_capa0 = 0;
int idx_capa1 = 0;
int idx_capa2 = 0;
int capa = 0;

// m5::rtc_date_t fecha_str;
// m5::rtc_time_t tiempo_str;

void setup()
{
  modulo = MENU_INICIAL;
  M5.begin();
  M5.Speaker.begin();
  M5.Speaker.setVolume(120);
  M5.Lcd.setTextSize(1.1);
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setBrightness(30);
  pinMode(BUTON_PIN_C, INPUT_PULLDOWN);
  pinMode(BUTON_PIN_A, INPUT_PULLUP);
  // fecha_str.date = 1;
  // fecha_str.month = 1;
  // fecha_str.year = 2000;
  // M5.Rtc.setDate(&fecha_str);

  // tiempo_str.hours = 00;
  // tiempo_str.minutes = 00;
  // tiempo_str.seconds = 00;
  // M5.Rtc.setTime(&tiempo_str);
}

void selectOption()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(1, 1);
  displaySubMenu(idx_capa0);
}

void loop()
{
  M5.update();
  enrutador();
}