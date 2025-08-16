#pragma once

namespace ports {

/**
 * @brief Interface for boolean state sensor implementations
 * 
 * Simple interface for sensors that provide binary information such as:
 * - Digital input pins (HIGH/LOW)
 * - Limit switches (pressed/released)
 * - Proximity sensors (detected/not detected)
 * - Button states (pressed/released)
 * - System flags (enabled/disabled)
 * - Motion detection (motion/no motion)
 * 
 * Example usage:
 * @code
 * class ButtonSensor : public IStateSensor {
 * private:
 *     int pin_;
 * 
 * public:
 *     explicit ButtonSensor(int pin) : pin_(pin) {}
 * 
 *     bool getState() override {
 *         return digitalRead(pin_) == HIGH;
 *     }
 * };
 * @endcode
 */
class IStateSensor {
public:
   /**
    * @brief Virtual destructor for proper cleanup of derived classes
    */
   virtual ~IStateSensor() = default;

   /**
    * @brief Get the current state as a boolean value
    * @return The current boolean state (true for active/HIGH, false for inactive/LOW)
    */
   virtual bool getState() = 0;
};

} // namespace ports
