#include "Arduino.h"
#include <cstring>
#include <M5StickCPlus2.h>
#include "submenu.h"
#include "const.h"

itemMenu MENU_INICIAR_ITEMS[] = {{"REANUDAR", 0}, {"DETENER", 0}};
int hrs = 0;
int mins = 0;
int segs = 0;
int milisegs = 0;
int iniciar = 0;
itemMenu opt[] = {{"INICIAR", 0}, {" ", 0}};

unsigned long previousMillis = 0;
const long interval = 10; // Intervalo de 10 milisegundos

void IRAM_ATTR isr()
{
  iniciar = 0;
}

void reiniciarCronometro()
{
  milisegs = 0;
  segs = 0;
  mins = 0;
  iniciar = 0;
  idx_capa1 = 0;
  M5.Lcd.clearDisplay();
  detachInterrupt(digitalPinToInterrupt(BUTON_PIN_A));
}

void printCronometro()
{
  M5.Lcd.setCursor(70, 56); // PARA UBICARLO EN EL CENTRO
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("%02d:%02d:%02d", mins, segs, milisegs);
}

void funcionCronometro()
{
  opt[0].nombre = "PAUSAR";
  displayMenu(opt, idx_capa1, 2);
  M5.Lcd.setTextColor(DARKGREY, BLACK);
  if (idx_capa1 == 1)
  {
    reiniciarCronometro();
    MODULO_CRONOMETRO();
  }
  while (iniciar == 1)
  {
    unsigned long currentMillis = millis();
    if (iniciar == 1)
    {
      if (currentMillis - previousMillis >= interval)
      {
        previousMillis = currentMillis;
        milisegs++;
        if (milisegs == 100)
        {
          milisegs = 0;
          segs++;
        }
        if (segs == 60)
        {
          segs = 0;
          mins++;
        }
        printCronometro();
      }
    }
  }
  displayMenu(MENU_INICIAR_ITEMS, idx_capa1, 2);
}

void MODULO_CRONOMETRO()
{
  attachInterrupt(digitalPinToInterrupt(BUTON_PIN_A), isr, FALLING);
  opt[0].nombre = "INICIAR";
  displayMenu(opt, idx_capa1, 2);
  printCronometro();
  while (capa == 1)
  {
    M5.update();
    if (M5.BtnA.wasPressed())
    {
      iniciar = 1;
      M5.Lcd.setTextColor(WHITE, BLACK);
      funcionCronometro();
    }
    if (M5.BtnB.wasPressed() && strcmp(opt[0].nombre.c_str(),"PAUSAR") == 0)
    {
      idx_capa1 = (idx_capa1 + 1) % 2;
      displayMenu(MENU_INICIAR_ITEMS, idx_capa1, 2);
    }
    if (digitalRead(BUTON_PIN_C) == 0 && iniciar == 0)
    {
      reiniciarCronometro();
      irAtras();
    }
  }
}