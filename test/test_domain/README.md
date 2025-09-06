# Domain Tests

This directory contains organized unit tests for all domain classes, following a clean architecture pattern.

## Test Structure

### Main Test Runner
- **`test_value.cpp`** - Centralized test runner that executes all domain tests

### Individual Test Files
- **`test_value_base.cpp`** - Tests for the `Value<T>` base class template
  - Basic arithmetic operations (+, -, *, /)
  - Comparison operations (==, !=, <, >, <=, >=)
  - Assignment operations (+=, -=, *=, /=)
  - Unary operations (+, -)
  - Error handling (NaN, division by zero)
  - Scalar multiplication

- **`test_voltage.cpp`** - Tests for the `Voltage` class
  - Construction and factory methods
  - Unit conversions (volts ↔ millivolts)
  - Inheritance compatibility with Value base class
  - Real-world voltage scenarios
  - Edge cases and validation

## Running Tests

To run all domain tests, compile and execute `test_value.cpp`:

```bash
# Using PlatformIO
pio test -f test_domain/test_value.cpp

# Or run individual test files
pio test -f test_domain/test_value_base.cpp
pio test -f test_domain/test_voltage.cpp
```

## Test Organization Principles

1. **Separation of Concerns**: Each domain class has its own dedicated test file
2. **Centralized Execution**: Single entry point for running all tests
3. **Clear Naming**: Test files follow `test_<class_name>.cpp` convention
4. **Focused Testing**: Each file tests only the specific functionality of its corresponding class
5. **Inheritance Testing**: Base class functionality is tested separately from derived class features

## Adding New Domain Classes

When adding a new domain class:

1. Create `test_<new_class>.cpp` with class-specific tests
2. Implement a `run_<new_class>_tests()` function
3. Add the function declaration and call to `test_value.cpp`
4. Update this README with the new test file description
