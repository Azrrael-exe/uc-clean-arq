#pragma once

#include "domain/value.h"

namespace ports {

/**
 * @brief Interface for sensor implementations
 * 
 * Defines the contract for all sensor types in the system following Clean Architecture.
 * Sensors provide readings through value objects and manage their ready state.
 * 
 * @tparam ValueType The type of value object this sensor produces (must inherit from domain::Value)
 */
template<typename ValueType>
class ISensor {
protected:
    ValueType value_;      ///< Current sensor reading value
    bool isReady_;        ///< Flag indicating if a new reading is available

public:
    /**
     * @brief Constructs a sensor with an initial value
     * @param initialValue The initial value for the sensor
     */
    explicit ISensor(const ValueType& initialValue) 
        : value_(initialValue), isReady_(false) {}

    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~ISensor() = default;

    /**
     * @brief Get the current sensor reading and mark as consumed
     * 
     * After calling this method, isReady becomes false until the next read() call.
     * 
     * @return The current sensor value
     */
    ValueType getRead() {
        isReady_ = false;
        return value_;
    }

    /**
     * @brief Check if a new reading is available
     * @return true if a new reading is ready, false otherwise
     */
    bool isReady() const noexcept {
        return isReady_;
    }

    /**
     * @brief Get the current value without consuming the ready state
     * @return The current sensor value
     */
    const ValueType& value() const noexcept {
        return value_;
    }

    /**
     * @brief Abstract method to perform sensor reading
     * 
     * Implementations should:
     * 1. Perform the actual sensor reading
     * 2. Update the value_ with the new reading
     * 3. Set isReady_ to true if reading was successful
     * 
     * This method must be implemented by all concrete sensor classes.
     */
    virtual void read() = 0;

protected:
    /**
     * @brief Update the sensor value and set ready state
     * 
     * Protected method for derived classes to update the sensor state
     * after a successful reading.
     * 
     * @param newValue The new sensor reading
     */
    void updateValue(const ValueType& newValue) {
        value_ = newValue;
        isReady_ = true;
    }
};

} // namespace ports
