#pragma once
#include <Arduino.h>

class WifiManager {
public:
    void connect(const char* ssid, const char* password);
    bool isConnected();
};
