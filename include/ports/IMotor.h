#pragma once

#include "domain/angle.h"

namespace ports {

class IMotor {
    public:
        virtual void rotate(domain::Angle angle) = 0;
    private:
};

} 
