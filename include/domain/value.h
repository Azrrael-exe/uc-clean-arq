#pragma once

#include <cmath>
#include <type_traits>

namespace domain {

/**
 * @brief Base class for value objects
 * 
 * Provides common operations and operators for value objects that wrap
 * a numeric value. Uses CRTP (Curiously Recurring Template Pattern) to
 * enable proper return types for derived classes.
 * 
 * @tparam Derived The derived class type
 * @tparam T The underlying numeric type (default: double)
 */
template<typename Derived, typename T = double>
class Value {
protected:
    T value_;

public:
    /**
     * @brief Constructs a Value object with the given value
     * @param value The numeric value to store
     */
    explicit Value(T value) : value_(value) {
        // Simple validation - no exceptions to maintain Arduino compatibility
        if constexpr (std::is_floating_point_v<T>) {
            if (::std::isnan(value)) {
                value_ = T{0}; // Default to 0 for invalid input
            }
        }
    }

    /**
     * @brief Get the underlying value
     * @return The stored value
     */
    T value() const noexcept {
        return value_;
    }

    // Arithmetic operators
    Derived operator+(const Derived& other) const {
        return Derived(value_ + other.value_);
    }

    Derived operator-(const Derived& other) const {
        return Derived(value_ - other.value_);
    }

    Derived operator*(T scalar) const {
        return Derived(value_ * scalar);
    }

    Derived operator/(T scalar) const {
        // Protect against division by zero for floating point types
        if constexpr (std::is_floating_point_v<T>) {
            if (scalar == T{0}) {
                return Derived(T{0}); // Return 0 for division by zero
            }
        }
        return Derived(value_ / scalar);
    }

    // Assignment operators
    Derived& operator+=(const Derived& other) {
        value_ += other.value_;
        return static_cast<Derived&>(*this);
    }

    Derived& operator-=(const Derived& other) {
        value_ -= other.value_;
        return static_cast<Derived&>(*this);
    }

    Derived& operator*=(T scalar) {
        value_ *= scalar;
        return static_cast<Derived&>(*this);
    }

    Derived& operator/=(T scalar) {
        // Protect against division by zero for floating point types
        if constexpr (std::is_floating_point_v<T>) {
            if (scalar == T{0}) {
                value_ = T{0};
                return static_cast<Derived&>(*this);
            }
        }
        value_ /= scalar;
        return static_cast<Derived&>(*this);
    }

    // Unary operators
    Derived operator-() const {
        return Derived(-value_);
    }

    Derived operator+() const {
        return Derived(value_);
    }

    // Comparison operators
    bool operator==(const Derived& other) const noexcept {
        return value_ == other.value_;
    }

    bool operator!=(const Derived& other) const noexcept {
        return !(*this == other);
    }

    bool operator<(const Derived& other) const noexcept {
        return value_ < other.value_;
    }

    bool operator<=(const Derived& other) const noexcept {
        return value_ <= other.value_;
    }

    bool operator>(const Derived& other) const noexcept {
        return value_ > other.value_;
    }

    bool operator>=(const Derived& other) const noexcept {
        return value_ >= other.value_;
    }

protected:
    /**
     * @brief Protected destructor to prevent deletion through base pointer
     */
    ~Value() = default;
};

// Non-member arithmetic operator for scalar multiplication
template<typename Derived, typename T>
inline Derived operator*(T scalar, const Value<Derived, T>& value) {
    return value * scalar;
}

} // namespace domain
