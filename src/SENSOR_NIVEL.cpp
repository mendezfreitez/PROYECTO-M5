#include <M5StickCPlus2.h>
#include "submenu.h"
#include "const.h"

float gx, gy, gz;
int int_gx, int_gy;

const int numSamples = 5;  // Número de muestras para promediar
float gyroXSamples[numSamples];
float gyroYSamples[numSamples];
float gyroZSamples[numSamples];
int sampleIndex = 0;

void SENSOR_NIVEL() {
  capa++;
  M5.Lcd.clearDisplay();
  M5.Lcd.setColor(BLACK);

  for (int i = 0; i < numSamples; i++) {
    gyroXSamples[i] = 0;
    gyroYSamples[i] = 0;
    gyroZSamples[i] = 0;
  }

  while (capa == 2) {
    M5.Imu.getAccelData(&gx, &gy, &gz);
    int_gx = gx * 60;
    int_gy = gy * 112;
    delayMicroseconds(10);

    M5.Lcd.setCursor(0, 0);
    gyroXSamples[sampleIndex] = int_gx;
    gyroYSamples[sampleIndex] = int_gy;

    sampleIndex = (sampleIndex + 1) % numSamples;

    float avgGyroX = 0, avgGyroY = 0;
    for (int i = 0; i < numSamples; i++) {
      avgGyroX += gyroXSamples[i];
      avgGyroY += gyroYSamples[i];
    }
    avgGyroX /= numSamples;
    avgGyroY /= numSamples;

    M5.Lcd.fillRect(0, 0, 240, avgGyroX + 58);
    M5.Lcd.fillRect(0, avgGyroX + 74, 240, 135 - (avgGyroX + 63));

    M5.Lcd.fillRect(0, 0, avgGyroY + 111, 135);
    M5.Lcd.fillRect(avgGyroY + 126, 0, 240 - (avgGyroY + 122), 135);

    M5.Lcd.fillCircle(avgGyroY + 120, avgGyroX + 67, 5, ORANGE);
    for (int i = 0; i < 20; i++) {
      M5.Lcd.drawCircle(avgGyroY + 120, avgGyroX + 67, i + 5, BLACK);
    }

    mirarBtnIrAtras();
  }
  M5.Lcd.setRotation(1);
  MODULO_SENSORES();
}