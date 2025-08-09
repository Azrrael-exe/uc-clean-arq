#include <ports/ISensor.h>
#include <domain/temperature.h>
#include <Arduino.h>

namespace infrastructure {

class LM35_Sensor : public ports::ISensor<domain::Temperature> {

private:
    int pin;

public:
    LM35_Sensor(int pin) 
        : ports::ISensor<domain::Temperature>(domain::Temperature(25.0)), 
          pin(pin) {
    }

    void read() override {
        this->updateValue(domain::Temperature(analogRead(this->pin) / 1024.0 * 5.0 * 100));
    }
};
}