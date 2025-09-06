#pragma once

#include <cmath>
#include "value.h"

namespace domain {

/**
 * @brief Simplified voltage value object
 * 
 * Represents an electrical voltage measurement with basic operations.
 * Stores voltage in volts as the base unit.
 */
class Voltage : public Value<Voltage, double> {

public:
    /**
     * @brief Constructs a Voltage object with the given value in volts
     * @param volts The voltage value in volts
     */
    explicit Voltage(double volts) : Value<Voltage, double>(volts) {}

    /**
     * @brief Factory method to create Voltage from millivolts
     * @param millivolts The voltage value in millivolts
     * @return Voltage object
     */
    static Voltage fromMillivolts(double millivolts) {
        return Voltage(millivolts / 1000.0);
    }

    /**
     * @brief Get the voltage value in volts
     * @return Voltage in volts
     */
    double volts() const noexcept {
        return value_;
    }

    /**
     * @brief Get the voltage value in millivolts
     * @return Voltage in millivolts
     */
    double millivolts() const noexcept {
        return value_ * 1000.0;
    }

};

} // namespace domain
