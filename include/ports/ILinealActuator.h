#pragma once

#include "domain/distance.h"

namespace ports {

class ILinealActuator {
    public:
        virtual void move(domain::Distance distance) = 0;
};

} 
