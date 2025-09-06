#pragma once

#include <cmath>
#include "value.h"

namespace domain {

/**
 * @brief Temperature value object
 * 
 * Represents a temperature measurement with conversions between Celsius and Fahrenheit.
 * Stores temperature internally in Celsius as the base unit.
 */
class Temperature : public Value<Temperature, double> {

public:
    /**
     * @brief Constructs a Temperature object with the given value in Celsius
     * @param celsius The temperature value in degrees Celsius
     */
    explicit Temperature(double celsius) : Value<Temperature, double>(celsius) {}

    /**
     * @brief Factory method to create Temperature from Fahrenheit
     * @param fahrenheit The temperature value in degrees Fahrenheit
     * @return Temperature object
     */
    static Temperature fromFahrenheit(double fahrenheit) {
        return Temperature((fahrenheit - 32.0) * 5.0 / 9.0);
    }

    /**
     * @brief Get the temperature value in Celsius
     * @return Temperature in degrees Celsius
     */
    double celsius() const noexcept {
        return value_;
    }

    /**
     * @brief Get the temperature value in Fahrenheit
     * @return Temperature in degrees Fahrenheit
     */
    double fahrenheit() const noexcept {
        return (value_ * 9.0 / 5.0) + 32.0;
    }

};

} // namespace domain
