#include <ports/ISensor.h>
#include <domain/temperature.h>
#include <Arduino.h>

namespace infrastructure {

class TemperatureSensor_Dummy : public ports::ISensor<domain::Temperature> {

private:
    double minTemp;
    double maxTemp;

public:
    TemperatureSensor_Dummy(double minTemp = 25.0, double maxTemp = 30.0) 
        : ports::ISensor<domain::Temperature>(domain::Temperature(25.0)), 
          minTemp(minTemp), maxTemp(maxTemp) {
        // Initialize random seed
        randomSeed(analogRead(0));
    }

    void read() override {
        // Generate random temperature between minTemp and maxTemp
        double randomTemp = minTemp + (random(0, 1000) / 1000.0) * (maxTemp - minTemp);
        this->updateValue(domain::Temperature(randomTemp));
    }

};
}
