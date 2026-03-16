#pragma once
#include "Adafruit_CCS811.h"
#include "maaling.h"
#include "payload.h"

class CO2 : public Maaling {
    private:
        Adafruit_CCS811 Carbondioxid;
    public:
        CO2();
        void begin();
        void fillPayload(Payload &Payload_) override;
};