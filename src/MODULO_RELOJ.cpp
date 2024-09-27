#include <vector>
// #include <ArduinoJson.h>
// #include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <string>
#include <M5StickCPlus2.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "submenu.h"
#include "const.h"

using namespace std;

TaskHandle_t fnHandle;
int capa_actual;
unsigned long prev_milis = 0;
vector<string> anioMesDia;
vector<string> horaMinSegs;
m5::rtc_date_t fecha_;
m5::rtc_time_t hora_;

vector<string> returnArrInfo(string infoDesglose, char charReff)
{
  int longInfo = infoDesglose.length();
  string acc = "";
  // std::vector<std::string> arrInfo;
  vector<string> arrInfo;

  for (int i = 0; i <= longInfo; i++)
  {
    if (infoDesglose[i] == charReff || i == longInfo)
    {
      arrInfo.push_back(acc);
      acc = "";
    }
    else
    {
      acc += infoDesglose[i];
    }
  }

  return arrInfo;
}

void nuevoFechaHora(JsonDocument doc)
{
  const char *fechaHora = doc["datetime"];
  string str = string(fechaHora);

  int pos_T = str.find('T');
  string fecha = str.substr(0, pos_T);
  string hora = str.substr(pos_T + 1, 8);

  anioMesDia = returnArrInfo(fecha, '-');
  horaMinSegs = returnArrInfo(hora, ':');
  fecha_.year = stoi(anioMesDia[0]);
  fecha_.month = stoi(anioMesDia[1]);
  fecha_.date = stoi(anioMesDia[2]);
  hora_.hours = stoi(horaMinSegs[0]);
  hora_.minutes = stoi(horaMinSegs[1]);
  hora_.seconds = stoi(horaMinSegs[2]);

  M5.Rtc.setDate(&fecha_);
  M5.Rtc.setTime(&hora_);
}

void setFechaHora(void *parameter)
{
  while (true)
  {
    if (digitalRead(BUTON_PIN_A) == 0)
    {
      int segundos = 0;
      int mili_segundos = 0;
      while (digitalRead(BUTON_PIN_A) == 0)
      {
        mili_segundos++;
        delay(1);
        if (mili_segundos >= 1000)
        {
          mili_segundos = 0;
          segundos++;
        }

        if (segundos >= 1)
        {
          wifiConn("Regina 2.4G", "lanamaria");

          HTTPClient http;
          http.setTimeout(20000);
          http.begin("https://worldtimeapi.org/api/timezone/America/Santiago");
          int rCode = http.GET();

          if (rCode > 0)
          {
            String resp = http.getString();

            JsonDocument doc;
            deserializeJson(doc, resp);
            nuevoFechaHora(doc);
          }
          else
          {
            alertaBorde(RED);
          }
        }
      }
    }
  }
}

void MODULO_RELOJ()
{
  xTaskCreatePinnedToCore(
      setFechaHora,   // Función que se ejecutará en el hilo
      "setFechaHora", // Nombre de la tarea (para depuración)
      10000,          // Tamaño de la pila para la tarea
      NULL,           // Parámetro pasado a la tarea (puedes usar NULL)
      1,              // Prioridad de la tarea (mayor número, mayor prioridad)
      &fnHandle,      // Puntero a la tarea manejada
      1               // Núcleo donde se ejecutará la tarea (0 o 1 en ESP32)
  );

  capa_actual = capa;
  M5.Lcd.clearDisplay();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(DARKGREY, BLACK);

  while (capa_actual == capa)
  {
    m5::rtc_date_t fecha = M5.Rtc.getDate();
    m5::rtc_time_t hora = M5.Rtc.getTime();

    M5.Lcd.setCursor(54, 48);
    M5.Lcd.printf("%02d:%02d:%02d", hora.hours, hora.minutes, hora.seconds);
    M5.Lcd.setCursor(54, 66);
    M5.Lcd.printf("%02d:%02d:%02d", fecha.date, fecha.month, fecha.year);

    bool resp = mirarBtnIrAtras(MENU_INICIAL);
    if (resp)
    {
      vTaskDelete(&fnHandle);
    }
  }
  M5.Lcd.clearDisplay();
  M5.Lcd.setTextSize(1.1);
}