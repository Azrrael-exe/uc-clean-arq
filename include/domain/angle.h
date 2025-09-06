#pragma once

#include <cmath>
#include "value.h"

namespace domain {

/**
 * @brief Angle value object
 * 
 * Represents an angle measurement with conversions between different units.
 * Stores angle internally in radians as the base unit.
 */
class Angle : public Value<Angle, double> {

public:
    /**
     * @brief Constructs an Angle object with the given value in radians
     * @param radians The angle value in radians
     */
    explicit Angle(double radians) : Value<Angle, double>(radians) {}

    /**
     * @brief Factory method to create Angle from degrees
     * @param degrees The angle value in degrees
     * @return Angle object
     */
    static Angle fromDegrees(double degrees) {
        return Angle(degrees * M_PI / 180.0);
    }

    /**
     * @brief Factory method to create Angle from gradians
     * @param gradians The angle value in gradians (gon)
     * @return Angle object
     */
    static Angle fromGradians(double gradians) {
        return Angle(gradians * M_PI / 200.0);
    }

    /**
     * @brief Factory method to create Angle from revolutions (full turns)
     * @param revolutions The angle value in revolutions
     * @return Angle object
     */
    static Angle fromRevolutions(double revolutions) {
        return Angle(revolutions * 2.0 * M_PI);
    }

    /**
     * @brief Get the angle value in radians
     * @return Angle in radians
     */
    double toRadians() const noexcept {
        return value_;
    }

    /**
     * @brief Get the angle value in degrees
     * @return Angle in degrees
     */
    double toDegrees() const noexcept {
        return value_ * 180.0 / M_PI;
    }

    /**
     * @brief Get the angle value in gradians (gon)
     * @return Angle in gradians
     */
    double toGradians() const noexcept {
        return value_ * 200.0 / M_PI;
    }

    /**
     * @brief Get the angle value in revolutions (full turns)
     * @return Angle in revolutions
     */
    double toRevolutions() const noexcept {
        return value_ / (2.0 * M_PI);
    }

    /**
     * @brief Normalize angle to range [0, 2π) radians
     * @return Normalized angle
     */
    Angle normalized() const {
        double normalized_value = std::fmod(value_, 2.0 * M_PI);
        if (normalized_value < 0) {
            normalized_value += 2.0 * M_PI;
        }
        return Angle(normalized_value);
    }

    /**
     * @brief Get sine of the angle
     * @return Sine value
     */
    double sin() const noexcept {
        return std::sin(value_);
    }

    /**
     * @brief Get cosine of the angle
     * @return Cosine value
     */
    double cos() const noexcept {
        return std::cos(value_);
    }

    /**
     * @brief Get tangent of the angle
     * @return Tangent value
     */
    double tan() const noexcept {
        return std::tan(value_);
    }

};

} // namespace domain
