#pragma once

#include <ports/IStateSensor.h>
#include <Arduino.h>

namespace infrastructure {

/**
 * @brief Simple implementation of a limit switch sensor
 * 
 * This class implements a digital limit switch sensor that detects when a mechanical
 * component has reached its limit position. Commonly used in:
 * - Linear actuators to detect end positions
 * - Robotic arms to detect joint limits
 * - CNC machines for homing and limit detection
 * - Automated doors and gates
 * - Conveyor belt systems
 * 
 * The sensor reads a digital pin and can be configured for different trigger modes:
 * - Normal mode: HIGH = activated, LOW = not activated
 * - Inverted mode: LOW = activated, HIGH = not activated (useful for pull-up resistors)
 * 
 * Features:
 * - Debouncing support to avoid false readings from mechanical bounce
 * - Configurable trigger polarity
 * - Simple boolean state interface
 * 
 * Example usage:
 * @code
 * // Create limit switch on pin 2, normal polarity, 50ms debounce
 * LimitSwitchSensor limitSwitch(2, false, 50);
 * 
 * // In main loop:
 * if (limitSwitch.getState()) {
 *     Serial.println("Limit switch is activated!");
 *     // Stop motor or perform limit action
 * }
 * @endcode
 */
class LimitSwitchSensor : public ports::IStateSensor {
private:
    int pin_;                    ///< Digital pin number for the limit switch
    bool inverted_;             ///< True if switch logic is inverted (LOW = activated)
    unsigned long debounceTime_; ///< Debounce time in milliseconds
    unsigned long lastReadTime_; ///< Last time the pin was read
    bool lastRawState_;         ///< Last raw pin state (before debouncing)
    bool currentState_;         ///< Current debounced state

public:
    /**
     * @brief Constructs a limit switch sensor
     * 
     * @param pin Digital pin number where the limit switch is connected
     * @param inverted If true, LOW signal means activated (useful with pull-up resistors)
     * @param debounceMs Debounce time in milliseconds to avoid mechanical bounce (default: 20ms)
     */
    explicit LimitSwitchSensor(int pin, bool inverted = false, unsigned long debounceMs = 20)
        : pin_(pin),
          inverted_(inverted),
          debounceTime_(debounceMs),
          lastReadTime_(0),
          lastRawState_(false),
          currentState_(false) {
        
        // Configure pin as input with pull-up if using inverted logic
        pinMode(pin_, inverted_ ? INPUT_PULLUP : INPUT);
        
        // Initialize with current pin state
        updateState();
    }

    /**
     * @brief Get the current state of the limit switch
     * 
     * This method performs debounced reading of the digital pin and returns
     * the current logical state of the switch.
     * 
     * @return true if switch is activated, false if not activated
     */
    bool getState() override {
        updateState();
        return currentState_;
    }

private:
    /**
     * @brief Update the current state with debouncing
     * 
     * Internal method that reads the pin with debouncing logic and updates
     * the current state accordingly.
     */
    void updateState() {
        unsigned long currentTime = millis();
        bool currentRawState = digitalRead(pin_) == HIGH;
        
        // Check if enough time has passed for debouncing
        if (currentTime - lastReadTime_ >= debounceTime_) {
            // Only update if the raw state has actually changed
            if (currentRawState != lastRawState_) {
                lastRawState_ = currentRawState;
                lastReadTime_ = currentTime;
                
                // Apply inversion logic if configured
                currentState_ = inverted_ ? !currentRawState : currentRawState;
            }
        }
    }

public:

    /**
     * @brief Get the configured pin number
     * @return The digital pin number used by this sensor
     */
    int getPin() const noexcept {
        return pin_;
    }

    /**
     * @brief Check if the sensor is configured in inverted mode
     * @return true if inverted logic is used, false for normal logic
     */
    bool isInverted() const noexcept {
        return inverted_;
    }

    /**
     * @brief Get the configured debounce time
     * @return Debounce time in milliseconds
     */
    unsigned long getDebounceTime() const noexcept {
        return debounceTime_;
    }

    /**
     * @brief Set a new debounce time
     * @param debounceMs New debounce time in milliseconds
     */
    void setDebounceTime(unsigned long debounceMs) noexcept {
        debounceTime_ = debounceMs;
    }
};

} // namespace infrastructure
