#include <ports/IMotor.h>
#include <domain/angle.h>
#include <ports/ILinealActuator.h>
#include <domain/distance.h>


namespace infrastructure {

class LinearActuatorFromMotor : public ports::ILinealActuator {

private:
    ports::IMotor& motor;
    float rotation_per_meter;
    domain::Angle calculateAngleFromDistance(domain::Distance distance);

public:
    LinearActuatorFromMotor(ports::IMotor& motor, float rotation_per_meter) : motor(motor), rotation_per_meter(rotation_per_meter) {
        this->rotation_per_meter = rotation_per_meter;
    }

    void move(domain::Distance distance) override {
        domain::Angle angle = calculateAngleFromDistance(distance);
        motor.rotate(angle);
    }
};

domain::Angle LinearActuatorFromMotor::calculateAngleFromDistance(domain::Distance distance) {
    return domain::Angle::fromDegrees(distance.meters() * rotation_per_meter);
}

}