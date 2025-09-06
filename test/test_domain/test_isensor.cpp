#include <unity.h>
#include <ports/ISensor.h>
#include <domain/voltage.h>

using namespace ports;
using namespace domain;

// Example concrete sensor implementation for testing
class MockVoltageSensor : public ISensor<Voltage> {
private:
    double simulatedReading_;

public:
    explicit MockVoltageSensor(double initialVoltage = 0.0) 
        : ISensor<Voltage>(Voltage(initialVoltage)), simulatedReading_(initialVoltage) {}

    void setSimulatedReading(double voltage) {
        simulatedReading_ = voltage;
    }

    void read() override {
        // Simulate sensor reading
        updateValue(Voltage(simulatedReading_));
    }
};

// === ISensor Interface Tests ===

void test_isensor_initial_state() {
    MockVoltageSensor sensor(3.3);
    
    // Initial state should not be ready
    TEST_ASSERT_FALSE(sensor.isReady());
    TEST_ASSERT_EQUAL_FLOAT(3.3, sensor.value().volts());
}

void test_isensor_read_cycle() {
    MockVoltageSensor sensor(0.0);
    sensor.setSimulatedReading(5.0);
    
    // Initially not ready
    TEST_ASSERT_FALSE(sensor.isReady());
    
    // Perform read operation
    sensor.read();
    
    // Should now be ready with new value
    TEST_ASSERT_TRUE(sensor.isReady());
    TEST_ASSERT_EQUAL_FLOAT(5.0, sensor.value().volts());
}

void test_isensor_getread_consumes_ready_state() {
    MockVoltageSensor sensor(0.0);
    sensor.setSimulatedReading(2.5);
    
    // Perform read and verify ready state
    sensor.read();
    TEST_ASSERT_TRUE(sensor.isReady());
    
    // Get the reading - this should consume the ready state
    Voltage reading = sensor.getRead();
    TEST_ASSERT_EQUAL_FLOAT(2.5, reading.volts());
    TEST_ASSERT_FALSE(sensor.isReady()); // Should no longer be ready
    
    // Value should still be accessible but ready state remains false
    TEST_ASSERT_EQUAL_FLOAT(2.5, sensor.value().volts());
    TEST_ASSERT_FALSE(sensor.isReady());
}

void test_isensor_multiple_reads() {
    MockVoltageSensor sensor(0.0);
    
    // First reading
    sensor.setSimulatedReading(1.0);
    sensor.read();
    TEST_ASSERT_TRUE(sensor.isReady());
    Voltage reading1 = sensor.getRead();
    TEST_ASSERT_EQUAL_FLOAT(1.0, reading1.volts());
    TEST_ASSERT_FALSE(sensor.isReady());
    
    // Second reading
    sensor.setSimulatedReading(2.0);
    sensor.read();
    TEST_ASSERT_TRUE(sensor.isReady());
    Voltage reading2 = sensor.getRead();
    TEST_ASSERT_EQUAL_FLOAT(2.0, reading2.volts());
    TEST_ASSERT_FALSE(sensor.isReady());
}

void test_isensor_value_access_without_consuming() {
    MockVoltageSensor sensor(0.0);
    sensor.setSimulatedReading(4.2);
    sensor.read();
    
    TEST_ASSERT_TRUE(sensor.isReady());
    
    // Access value multiple times without consuming ready state
    TEST_ASSERT_EQUAL_FLOAT(4.2, sensor.value().volts());
    TEST_ASSERT_TRUE(sensor.isReady()); // Should still be ready
    
    TEST_ASSERT_EQUAL_FLOAT(4.2, sensor.value().volts());
    TEST_ASSERT_TRUE(sensor.isReady()); // Should still be ready
    
    // Only getRead() should consume the ready state
    Voltage reading = sensor.getRead();
    TEST_ASSERT_EQUAL_FLOAT(4.2, reading.volts());
    TEST_ASSERT_FALSE(sensor.isReady()); // Now consumed
}

void run_isensor_tests() {
    RUN_TEST(test_isensor_initial_state);
    RUN_TEST(test_isensor_read_cycle);
    RUN_TEST(test_isensor_getread_consumes_ready_state);
    RUN_TEST(test_isensor_multiple_reads);
    RUN_TEST(test_isensor_value_access_without_consuming);
    
}
