#include <unity.h>
#include <domain/value.h>
#include <cmath>
#include <limits>

using namespace domain;

// Test class that inherits from Value for testing the base class
class TestValue : public Value<TestValue, double> {
public:
    explicit TestValue(double value) : Value<TestValue, double>(value) {}
    
    // Helper method to access the protected value_ member for testing
    double getValue() const { return value_; }
};

// setUp and tearDown are defined in the main test runner (test_value.cpp)

// === VALUE BASE CLASS TESTS ===

void test_value_basic_operations() {
    TestValue v1(5.0);
    TestValue v2(3.0);
    
    // Test basic value access
    TEST_ASSERT_EQUAL_FLOAT(5.0, v1.value());
    TEST_ASSERT_EQUAL_FLOAT(3.0, v2.value());
    
    // Test arithmetic operations
    TestValue sum = v1 + v2;
    TEST_ASSERT_EQUAL_FLOAT(8.0, sum.value());
    
    TestValue diff = v1 - v2;
    TEST_ASSERT_EQUAL_FLOAT(2.0, diff.value());
    
    TestValue mult = v1 * 2.0;
    TEST_ASSERT_EQUAL_FLOAT(10.0, mult.value());
    
    TestValue div = v1 / 2.0;
    TEST_ASSERT_EQUAL_FLOAT(2.5, div.value());
}

void test_value_comparison_operations() {
    TestValue v1(5.0);
    TestValue v2(5.0);
    TestValue v3(3.0);
    
    // Test equality
    TEST_ASSERT_TRUE(v1 == v2);
    TEST_ASSERT_FALSE(v1 == v3);
    
    // Test inequality
    TEST_ASSERT_FALSE(v1 != v2);
    TEST_ASSERT_TRUE(v1 != v3);
    
    // Test ordering
    TEST_ASSERT_TRUE(v3 < v1);
    TEST_ASSERT_TRUE(v1 > v3);
    TEST_ASSERT_TRUE(v3 <= v1);
    TEST_ASSERT_TRUE(v1 >= v3);
}

void test_value_assignment_operations() {
    TestValue v1(10.0);
    TestValue v2(3.0);
    
    // Test assignment operators
    TestValue v3 = v1;
    v3 += v2;
    TEST_ASSERT_EQUAL_FLOAT(13.0, v3.value());
    
    TestValue v4 = v1;
    v4 -= v2;
    TEST_ASSERT_EQUAL_FLOAT(7.0, v4.value());
    
    TestValue v5 = v1;
    v5 *= 2.0;
    TEST_ASSERT_EQUAL_FLOAT(20.0, v5.value());
    
    TestValue v6 = v1;
    v6 /= 2.0;
    TEST_ASSERT_EQUAL_FLOAT(5.0, v6.value());
}

void test_value_unary_operations() {
    TestValue v1(5.0);
    
    // Test unary plus
    TestValue plus_result = +v1;
    TEST_ASSERT_EQUAL_FLOAT(5.0, plus_result.value());
    
    // Test unary minus
    TestValue minus_result = -v1;
    TEST_ASSERT_EQUAL_FLOAT(-5.0, minus_result.value());
}

void test_value_nan_handling() {
    // Test NaN handling in base class
    TestValue v(std::numeric_limits<double>::quiet_NaN());
    TEST_ASSERT_EQUAL_FLOAT(0.0, v.value());
}

void test_value_division_by_zero() {
    TestValue v1(10.0);
    
    // Test division by zero protection
    TestValue result = v1 / 0.0;
    TEST_ASSERT_EQUAL_FLOAT(0.0, result.value());
    
    // Test assignment division by zero
    TestValue v2(10.0);
    v2 /= 0.0;
    TEST_ASSERT_EQUAL_FLOAT(0.0, v2.value());
}

void test_value_scalar_multiplication() {
    TestValue v1(3.0);
    
    // Test scalar multiplication from left
    TestValue result1 = 2.0 * v1;
    TEST_ASSERT_EQUAL_FLOAT(6.0, result1.value());
    
    // Test scalar multiplication from right
    TestValue result2 = v1 * 2.0;
    TEST_ASSERT_EQUAL_FLOAT(6.0, result2.value());
}

// Test runner for Value base class tests
void run_value_base_tests() {
    RUN_TEST(test_value_basic_operations);
    RUN_TEST(test_value_comparison_operations);
    RUN_TEST(test_value_assignment_operations);
    RUN_TEST(test_value_unary_operations);
    RUN_TEST(test_value_nan_handling);
    RUN_TEST(test_value_division_by_zero);
    RUN_TEST(test_value_scalar_multiplication);
}
