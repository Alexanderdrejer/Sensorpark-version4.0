#include <Adafruit_BME280.h>
#include "Maaling.h"
#include "payload.h"
#include <Adafruit_AHTX0.h>

#pragma once

class Temp : public Maaling {
    private: 
        Adafruit_AHTX0 Temp_;

    public:
        void fillPayload(Payload &Payload_) override;
        Temp();
        void begin();
};