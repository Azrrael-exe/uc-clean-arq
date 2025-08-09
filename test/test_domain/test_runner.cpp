/**
 * @file test_value.cpp
 * @brief Centralized test runner for all domain class tests
 * 
 * This file serves as the main entry point for running all domain tests.
 * Individual test implementations are organized in separate files:
 * - test_value_base.cpp: Tests for Value base class functionality
 * - test_voltage.cpp: Tests for Voltage class functionality
 */

#include <unity.h>

// Forward declarations of test runner functions
extern void run_value_base_tests();
extern void run_voltage_tests();
extern void run_isensor_tests();

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

int main(void) {
    UNITY_BEGIN();
    
    // Run all domain class tests
    run_value_base_tests();  // Value base class tests
    run_voltage_tests();     // Voltage class tests
    run_isensor_tests();     // ISensor class tests
    return UNITY_END();
}