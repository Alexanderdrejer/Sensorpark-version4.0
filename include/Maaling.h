#pragma once
#include "payload.h"

class Maaling {

    public:
        virtual void fillPayload(Payload &payload) = 0;
        ~Maaling() = default;
        
};