#include <Arduino.h>
#include <M5StickCPlus2.h>

void setup()
{
  M5.begin();
  M5.Lcd.setTextSize(1.1);
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setBrightness(30);
}

void loop()
{
  M5.Lcd.setCursor(3,30);
  M5.Lcd.println("Esto es una pruebaaaa");
  delay(3000);
}