#pragma once
#include <Arduino.h>

class HttpSender {
public:
    void send(const char* url, float temperature, float humidity, int co2);
};
