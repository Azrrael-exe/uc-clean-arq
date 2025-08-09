#include <unity.h>
#include <domain/voltage.h>
#include <cmath>
#include <limits>

using namespace domain;

// setUp and tearDown are defined in the main test runner (test_value.cpp)

// === VOLTAGE SPECIFIC TESTS ===

// Basic construction tests - focusing on Voltage-specific behavior
void test_voltage_construction() {
    Voltage v1(3.3);
    TEST_ASSERT_EQUAL_FLOAT(3.3, v1.volts());
    TEST_ASSERT_EQUAL_FLOAT(3.3, v1.value()); // Test inherited method
    
    Voltage v2(-5.0);
    TEST_ASSERT_EQUAL_FLOAT(-5.0, v2.volts());
    
    // Test NaN handling through inheritance
    Voltage v3(std::numeric_limits<double>::quiet_NaN());
    TEST_ASSERT_EQUAL_FLOAT(0.0, v3.volts());
}

void test_factory_methods() {
    // fromMillivolts
    Voltage v1 = Voltage::fromMillivolts(3300.0);
    TEST_ASSERT_EQUAL_FLOAT(3.3, v1.volts());
    
    Voltage v2 = Voltage::fromMillivolts(-1500.0);
    TEST_ASSERT_EQUAL_FLOAT(-1.5, v2.volts());
}

void test_unit_conversions() {
    // Test volts() method
    Voltage v1(3.3);
    TEST_ASSERT_EQUAL_FLOAT(3.3, v1.volts());
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 3300.0, v1.millivolts());
    
    // Test with negative voltage
    Voltage v2(-2.5);
    TEST_ASSERT_EQUAL_FLOAT(-2.5, v2.volts());
    TEST_ASSERT_FLOAT_WITHIN(1e-6, -2500.0, v2.millivolts());
    
    // Test with zero
    Voltage v3(0.0);
    TEST_ASSERT_EQUAL_FLOAT(0.0, v3.volts());
    TEST_ASSERT_EQUAL_FLOAT(0.0, v3.millivolts());
    
    // Test precision with small values
    Voltage v4(0.001);
    TEST_ASSERT_EQUAL_FLOAT(0.001, v4.volts());
    TEST_ASSERT_FLOAT_WITHIN(1e-9, 1.0, v4.millivolts());
}

void test_voltage_inheritance_compatibility() {
    // Test that inherited operators work correctly with Voltage-specific methods
    Voltage v1(3.3);
    Voltage v2(1.7);
    
    // Test arithmetic operations return correct types and values
    Voltage sum = v1 + v2;
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 5.0, sum.volts());
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 5000.0, sum.millivolts());
    
    // Test scalar multiplication
    Voltage doubled = v1 * 2.0;
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 6.6, doubled.volts());
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 6600.0, doubled.millivolts());
    
    // Test that comparison works with voltage values
    Voltage higher = Voltage(5.0);
    Voltage lower = Voltage(3.0);
    TEST_ASSERT_TRUE(higher > lower);
    TEST_ASSERT_TRUE(lower < higher);
}

void test_voltage_factory_edge_cases() {
    // Test factory method with edge cases
    Voltage v1 = Voltage::fromMillivolts(0.0);
    TEST_ASSERT_EQUAL_FLOAT(0.0, v1.volts());
    
    Voltage v2 = Voltage::fromMillivolts(-1500.0);
    TEST_ASSERT_EQUAL_FLOAT(-1.5, v2.volts());
    
    // Test very small millivolt values
    Voltage v3 = Voltage::fromMillivolts(1.0);
    TEST_ASSERT_FLOAT_WITHIN(1e-9, 0.001, v3.volts());
    
    // Test large millivolt values
    Voltage v4 = Voltage::fromMillivolts(1000000.0);
    TEST_ASSERT_FLOAT_WITHIN(1e-3, 1000.0, v4.volts());
}

void test_voltage_real_world_scenarios() {
    // Test common voltage levels
    Voltage battery_aa = Voltage(1.5);  // AA battery
    Voltage usb_voltage = Voltage(5.0); // USB voltage
    Voltage household = Voltage(120.0); // US household voltage
    
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1500.0, battery_aa.millivolts());
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 5000.0, usb_voltage.millivolts());
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 120000.0, household.millivolts());
    
    // Test voltage drops and additions
    Voltage total = battery_aa + usb_voltage;
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 6.5, total.volts());
    
    // Test voltage divider scenario
    Voltage half_voltage = household / 2.0;
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 60.0, half_voltage.volts());
}

// Test runner for Voltage class tests
void run_voltage_tests() {
    RUN_TEST(test_voltage_construction);
    RUN_TEST(test_factory_methods);
    RUN_TEST(test_unit_conversions);
    RUN_TEST(test_voltage_inheritance_compatibility);
    RUN_TEST(test_voltage_factory_edge_cases);
    RUN_TEST(test_voltage_real_world_scenarios);
}
