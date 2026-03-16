#include "CO2.h"

CO2::CO2() {}

void CO2::begin() {
    if (!Carbondioxid.begin()) {
        Serial.println("CO2 sensor did not initialize.");
    }
}


void CO2::fillPayload(Payload &Payload_)
{
    if (Carbondioxid.available()) {
        if (!Carbondioxid.readData()) {
            Payload_.CO2 = Carbondioxid.geteCO2();
        }
    }
}
