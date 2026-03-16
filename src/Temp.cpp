#include "Temp.h"

void Temp::fillPayload(Payload &Payload_) {
    sensors_event_t humidity, temp;
    Temp_.getEvent(&humidity, &temp);
    Payload_.temperature = temp.temperature;
    Payload_.humidity = humidity.relative_humidity;
}


Temp::Temp() {}

void Temp::begin() {
    if (Temp_.begin()) {
        Serial.println("Temp sensor initialized!");
    } else {
        Serial.println("Temp sensor did not initialize.");
    }
}

