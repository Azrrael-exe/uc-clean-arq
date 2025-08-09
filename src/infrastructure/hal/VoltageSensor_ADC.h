#include <ports/ISensor.h>
#include <domain/voltage.h>
#include <Arduino.h>

namespace infrastructure {

class VoltageSensor_ADC : public ports::ISensor<domain::Voltage> {

private:
    int pin;

public:
    VoltageSensor_ADC(int pin) : ports::ISensor<domain::Voltage>(domain::Voltage(0.0)) {
        this->pin = pin;
    }

    void read() override {
        this->updateValue(domain::Voltage(analogRead(this->pin) / 1024.0 * 5.0));
    }

};


}