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
}

void loop() {
  Payload Payload_;

  for (auto &sensorer : sensors) {
    sensorer->fillPayload(Payload_);
  }

  Serial.print("Humidity: ");
  Serial.println(Payload_.humidity);

  Serial.print("Temp: ");
  Serial.println(Payload_.temperature);

  Serial.print("CO2: ");
  Serial.println(Payload_.CO2);

  delay(5000);

  HttpSend.send("http://192.168.0.117:8000/maaling", Payload_.temperature, Payload_.humidity, Payload_.CO2);

}
