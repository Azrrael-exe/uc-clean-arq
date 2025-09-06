#pragma once

#include <cmath>
#include "value.h"

namespace domain {

/**
 * @brief Distance value object
 * 
 * Represents a distance measurement with conversions between different units.
 * Stores distance internally in meters as the base unit.
 */
class Distance : public Value<Distance, double> {

public:
    /**
     * @brief Constructs a Distance object with the given value in meters
     * @param meters The distance value in meters
     */
    explicit Distance(double meters) : Value<Distance, double>(meters) {}

    /**
     * @brief Factory method to create Distance from millimeters
     * @param millimeters The distance value in millimeters
     * @return Distance object
     */
    static Distance fromMillimeters(double millimeters) {
        return Distance(millimeters / 1000.0);
    }

    /**
     * @brief Factory method to create Distance from centimeters
     * @param centimeters The distance value in centimeters
     * @return Distance object
     */
    static Distance fromCentimeters(double centimeters) {
        return Distance(centimeters / 100.0);
    }

    /**
     * @brief Factory method to create Distance from kilometers
     * @param kilometers The distance value in kilometers
     * @return Distance object
     */
    static Distance fromKilometers(double kilometers) {
        return Distance(kilometers * 1000.0);
    }

    /**
     * @brief Get the distance value in meters
     * @return Distance in meters
     */
    double meters() const noexcept {
        return value_;
    }

    /**
     * @brief Get the distance value in millimeters
     * @return Distance in millimeters
     */
    double millimeters() const noexcept {
        return value_ * 1000.0;
    }

    /**
     * @brief Get the distance value in centimeters
     * @return Distance in centimeters
     */
    double centimeters() const noexcept {
        return value_ * 100.0;
    }

    /**
     * @brief Get the distance value in kilometers
     * @return Distance in kilometers
     */
    double kilometers() const noexcept {
        return value_ / 1000.0;
    }

};

} // namespace domain
