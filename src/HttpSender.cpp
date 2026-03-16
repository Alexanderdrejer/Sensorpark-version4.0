#include "HttpSender.h"
#include <HTTPClient.h>

void HttpSender::send(const char* url, float temperature, float humidity, int co2) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String body = "{\"temperature\":" + String(temperature) +
                  ",\"humidity\":" + String(humidity) +
                  ",\"co2\":" + String(co2) + "}";

    int responseCode = http.POST(body);
    Serial.println(responseCode);

    http.end();
}
