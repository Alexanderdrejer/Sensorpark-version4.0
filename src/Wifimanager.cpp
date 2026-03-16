#include "WifiManager.h"
#include <WiFi.h>

void WifiManager::connect(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    int forsogg = 0;
    while (WiFi.status() != WL_CONNECTED && forsogg < 20) {
        delay(500);
        forsogg++;
    }
    if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected!");
    Serial.println(WiFi.localIP());
    } else {
        Serial.println("WiFi failed.");
}

}

