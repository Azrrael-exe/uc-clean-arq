#pragma once

#include "domain/value.h"
#include "ports/ISensor.h"

namespace app {

/**
 * @brief Configuration object for alarm thresholds
 * 
 * Contains minimum and maximum threshold values of the same type.
 * Used to configure alarm conditions for monitoring sensors.
 * 
 * @tparam ValueType The type of value object for thresholds (must inherit from domain::Value)
 */
template<typename ValueType>
class AlarmConfig {
private:
    ValueType minThreshold_;
    ValueType maxThreshold_;

public:
    /**
     * @brief Constructs an AlarmConfig with min and max thresholds
     * 
     * Ensures that minThreshold <= maxThreshold by swapping if necessary.
     * 
     * @param minThreshold The minimum threshold value
     * @param maxThreshold The maximum threshold value
     */
    AlarmConfig(const ValueType& minThreshold, const ValueType& maxThreshold) 
        : minThreshold_(minThreshold), maxThreshold_(maxThreshold) {
        
        // Ensure min <= max, swap if necessary
        if (maxThreshold_ < minThreshold_) {
            ValueType temp = minThreshold_;
            minThreshold_ = maxThreshold_;
            maxThreshold_ = temp;
        }
    }

    /**
     * @brief Get the minimum threshold value
     * @return The minimum threshold
     */
    const ValueType& minThreshold() const noexcept {
        return minThreshold_;
    }

    /**
     * @brief Get the maximum threshold value
     * @return The maximum threshold
     */
    const ValueType& maxThreshold() const noexcept {
        return maxThreshold_;
    }
};

/**
 * @brief Alarm states
 */
enum class AlarmState {
    NORMAL,     ///< Value is within normal range [min, max]
    LOW,        ///< Value is below minimum threshold
    HIGH,       ///< Value is above maximum threshold
};

/**
 * @brief Use case for monitoring sensor values against alarm thresholds
 * 
 * This use case orchestrates the monitoring of sensor readings against
 * configured thresholds to determine alarm conditions.
 * 
 * @tparam ValueType The type of value being monitored (must inherit from domain::Value)
 */
template<typename ValueType>
class AlarmUseCase {
private:
    AlarmConfig<ValueType> config_;
    ports::ISensor<ValueType>& sensor_;

public:
    /**
     * @brief Constructs an AlarmUseCase with configuration and sensor
     * 
     * @param config The alarm configuration with thresholds
     * @param sensor Reference to the sensor to monitor
     */
    AlarmUseCase(const AlarmConfig<ValueType>& config, ports::ISensor<ValueType>& sensor)
        : config_(config), sensor_(sensor) {}

    /**
     * @brief Execute the alarm check
     * 
     * Reads the current sensor value and compares it against the configured
     * thresholds to determine the alarm state.
     * 
     * @return AlarmState indicating the alarm condition
     */
    AlarmState execute() {
        // Try to get a fresh reading
        sensor_.read();
        
        // Check if sensor has a valid reading
        if (!sensor_.isReady()) {
            // Return normal state if sensor not ready
            return AlarmState::NORMAL;
        }

        // Get the current reading
        ValueType currentValue = sensor_.getRead();

        // Determine alarm state based on thresholds
        AlarmState state;
        if (currentValue < config_.minThreshold()) {
            state = AlarmState::LOW;
        } else if (currentValue > config_.maxThreshold()) {
            state = AlarmState::HIGH;
        } else {
            state = AlarmState::NORMAL;
        }

        return state;
    }
};

} // namespace app
