#pragma once

#include "domain/distance.h"
#include "ports/ILinealActuator.h"
#include "ports/IStateSensor.h"

namespace app {


class CartesianMove {
    public:
        CartesianMove(
            ports::ILinealActuator& xLinearActuator,
            ports::ILinealActuator& yLinearActuator,
            ports::IStateSensor& xlimitSwitch,
            ports::IStateSensor& ylimitSwitch)
            : xLinearActuator(xLinearActuator),
              yLinearActuator(yLinearActuator),
              xlimitSwitch(xlimitSwitch),
              ylimitSwitch(ylimitSwitch) {};
        void move(domain::Distance xDistance, domain::Distance yDistance);
    private:
        ports::ILinealActuator& xLinearActuator;
        ports::ILinealActuator& yLinearActuator;
        ports::IStateSensor& xlimitSwitch;
        ports::IStateSensor& ylimitSwitch;
        void homeX();
        void homeY();
        void moveX(domain::Distance distance);
        void moveY(domain::Distance distance);

}; // namespace app

void CartesianMove::homeX() {
    while (xlimitSwitch.getState() == false) {
        xLinearActuator.move(domain::Distance::fromMillimeters(-1.0));
    }
}

void CartesianMove::homeY() {
    while (ylimitSwitch.getState() == false) {
        yLinearActuator.move(domain::Distance::fromMillimeters(-1.0));
    }
}

void CartesianMove::moveX(domain::Distance distance) {
    xLinearActuator.move(distance);
}

void CartesianMove::moveY(domain::Distance distance) {
    yLinearActuator.move(distance);
}

void CartesianMove::move(domain::Distance xDistance, domain::Distance yDistance) {
    homeX();
    homeY();
    moveX(xDistance);
    moveY(yDistance);
}

};