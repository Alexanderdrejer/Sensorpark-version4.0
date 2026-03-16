#include <Arduino.h>
#include "Maaling.h"
#include "payload.h"
#include "CO2.h"
#include "Temp.h"
#include <vector>
#include <Wire.h>
#include "WiFimanager.h"
#include "secrets.h"
#include "HttpSender.h"
#include <esp_sleep.h>

#define SDA 21
#define SCL 22

std::vector<Maaling*> sensors;
CO2 Carbon_;
Temp Temperature_humidity;
WifiManager Wifi_;
HttpSender HttpSend;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  delay(1000);
  Carbon_.begin();
  Temperature_humidity.begin();
  sensors.push_back(&Carbon_);
  sensors.push_back(&Temperature_humidity);
  Wifi_.connect(ssid, password);
  configTime(3600, 0, "pool.ntp.org");
}

void loop() {
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    int hour = timeinfo.tm_hour;

    if (hour == 1 || hour == 6 || hour == 12 || hour == 18 || hour == 0) {
        Payload Payload_;
        for (auto &sensor : sensors) {
            sensor->fillPayload(Payload_);
        }
        HttpSend.send("http://sensorpark-version40-production.up.railway.app/maaling",
                      Payload_.temperature, Payload_.humidity, Payload_.CO2);
    }

    esp_sleep_enable_timer_wakeup(3600ULL * 1000000ULL);
    esp_light_sleep_start();
}

