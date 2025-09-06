#pragma once

#include "domain/voltage.h"
#include "ports/ISensor.h"

#include <ArduinoJson.h>

namespace app {

/**
 * @brief Configuration object for alarm thresholds
 * 
 * Contains minimum and maximum threshold values of the same type.
 * Used to configure alarm conditions for monitoring sensors.
 * 
 * @tparam ValueType The type of value object for thresholds (must inherit from domain::Value)
 */

class VoltageSensorReporter {
private:
    ports::ISensor<domain::Voltage>& sensor_;
public:
    VoltageSensorReporter(ports::ISensor<domain::Voltage>& sensor) 
        : sensor_(sensor) {}
    void report(Stream& stream) {
        sensor_.read();
        domain::Voltage voltage = sensor_.getRead();

        JsonDocument doc;

        doc["sensor"] = "voltage";
        doc["voltage"] = voltage.volts();

        serializeJson(doc, stream);
    }
};

} // namespace app
