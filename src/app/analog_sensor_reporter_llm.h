#pragma once

#include "domain/voltage.h"
#include "ports/ISensor.h"

#include <llp.h>

namespace app {

/**
 * @brief Configuration object for alarm thresholds
 * 
 * Contains minimum and maximum threshold values of the same type.
 * Used to configure alarm conditions for monitoring sensors.
 * 
 * @tparam ValueType The type of value object for thresholds (must inherit from domain::Value)
 */

class VoltageSensorReporterLlp{
private:
    ports::ISensor<domain::Voltage>& sensor_;
public:
    VoltageSensorReporterLlp(ports::ISensor<domain::Voltage>& sensor) 
        : sensor_(sensor) {}
    void report(Stream& stream) {
        sensor_.read();
        domain::Voltage voltage = sensor_.getRead();

        DataPack doc;

        // VOLTAGE KEY: 0xAF
        int VOLTAGE_KEY = 0xAF;
        doc.addData(uint8_t(VOLTAGE_KEY), uint16_t(voltage.millivolts()));
        doc.write(stream);
    }
};

} // namespace app
