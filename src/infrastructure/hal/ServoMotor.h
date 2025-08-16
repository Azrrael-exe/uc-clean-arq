#include <ports/IMotor.h>
#include <domain/angle.h>
#include <Arduino.h>
#include <Servo.h>

namespace infrastructure {

class ServoMotor : public ports::IMotor {

private:
    Servo servo;

public:
    ServoMotor(int pin) {
        this->servo.attach(pin);
    };

    void rotate(domain::Angle angle) override {
        double degrees_value = angle.toDegrees();
        int angle_degrees = static_cast<int>(degrees_value);
        this->servo.write(angle_degrees);
    }
};

}