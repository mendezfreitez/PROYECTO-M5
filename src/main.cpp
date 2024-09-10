#include <M5StickCPlus2.h>
#include "submenu.h"
#include "const.h"

const int BUTON_PIN_C = 35;
const int BUTON_PIN_A = 37;
const char *MENU_PRINCIPAL_ITEMS[] = { "RELOJ", "CRONOMETRO", "SENSORES" };
const int menu_length = sizeof(MENU_PRINCIPAL_ITEMS) / sizeof(MENU_PRINCIPAL_ITEMS[0]);
int idx_capa0 = 0;
int idx_capa1 = 0;
int idx_capa2 = 0;
int capa = 0;

// m5::rtc_date_t fecha_str;
// m5::rtc_time_t tiempo_str;

void setup() {
  M5.begin();
  // fecha_str.date = 1;
  // fecha_str.month = 1;
  // fecha_str.year = 2000;
  // M5.Rtc.setDate(&fecha_str);

  // tiempo_str.hours = 00;
  // tiempo_str.minutes = 00;
  // tiempo_str.seconds = 00;
  // M5.Rtc.setTime(&tiempo_str);
  
  M5.Lcd.setTextSize(1.1);
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setBrightness(30);
  displayMenu(MENU_PRINCIPAL_ITEMS, idx_capa0, menu_length);
  pinMode(BUTON_PIN_C, INPUT_PULLDOWN);
  pinMode(BUTON_PIN_A, INPUT_PULLUP);
}

void selectOption() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(1, 1);
  displaySubMenu(idx_capa0);

  displayMenu(MENU_PRINCIPAL_ITEMS, idx_capa0, menu_length);
}

void loop() {
  M5.update();
  if (M5.BtnB.wasPressed()) {
    if (capa == 0) {
      idx_capa0 = (idx_capa0 + 1) % menu_length;
      displayMenu(MENU_PRINCIPAL_ITEMS, idx_capa0, menu_length);
    }
  }
  if (M5.BtnA.wasPressed()) {
    if (capa < 2) { capa++; }
    selectOption();
  }
}