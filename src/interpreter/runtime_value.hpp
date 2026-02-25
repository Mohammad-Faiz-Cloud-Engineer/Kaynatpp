/**
 * @file runtime_value.hpp
 * @brief Core runtime value type for Kaynat++ interpreter
 * 
 * Defines KaynatValue as a std::variant holding all possible runtime types.
 * Supports integers, floats, booleans, strings, lists, dictionaries, and more.
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <variant>
#include <optional>

namespace kaynat {

// Forward declarations
class KaynatValue;
class BigInt;
class KaynatInstance;

/**
 * @brief Null type representation
 */
struct NullType {
    bool operator==(const NullType&) const { return true; }
};

/**
 * @brief Callable function type
 * Takes vector of arguments, returns a value
 */
using CallableType = std::function<KaynatValue(std::vector<KaynatValue>)>;

/**
 * @brief List type - vector of values
 */
using ListType = std::vector<KaynatValue>;

/**
 * @brief Dictionary type - string keys to values
 */
using DictType = std::unordered_map<std::string, KaynatValue>;

/**
 * @brief Big integer implementation using base 10^9 representation
 * 
 * Stores large integers as vector of 9-digit chunks for efficient arithmetic.
 * Thread-safe for read operations, not thread-safe for modifications.
 */
class BigInt {
public:
    BigInt();
    explicit BigInt(int64_t value);
    explicit BigInt(const std::string& str);
    
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;
    
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    
    std::string to_string() const;
    
private:
    static constexpr int32_t BASE = 1000000000; // 10^9
    std::vector<int32_t> digits_;
    bool negative_;
    
    void normalize();
};

/**
 * @brief Main runtime value type
 * 
 * Variant holding all possible Kaynat++ runtime types.
 * Immutable by design - operations create new values.
 */
class KaynatValue {
public:
    using ValueVariant = std::variant<
        NullType,
        int64_t,
        double,
        bool,
        char32_t,
        std::string,
        BigInt,
        ListType,
        DictType,
        std::shared_ptr<KaynatInstance>,
        CallableType
    >;
    
    KaynatValue();
    KaynatValue(NullType);
    KaynatValue(int64_t value);
    KaynatValue(double value);
    KaynatValue(bool value);
    KaynatValue(char32_t value);
    KaynatValue(const std::string& value);
    KaynatValue(const char* value);
    KaynatValue(const BigInt& value);
    KaynatValue(const ListType& value);
    KaynatValue(const DictType& value);
    KaynatValue(std::shared_ptr<KaynatInstance> value);
    KaynatValue(CallableType value);
    
    /**
     * @brief Get the type name as a string
     * @return Type name (e.g., "Integer", "String", "List")
     */
    std::string type_name() const;
    
    /**
     * @brief Check if value is null
     */
    bool is_null() const;
    
    /**
     * @brief Check if value is truthy (for conditionals)
     */
    bool is_truthy() const;
    
    /**
     * @brief Convert value to display string
     */
    std::string to_string() const;
    
    /**
     * @brief Get underlying variant
     */
    const ValueVariant& get_variant() const { return value_; }
    ValueVariant& get_variant() { return value_; }
    
    /**
     * @brief Type-safe getters with optional return
     */
    std::optional<int64_t> as_int() const;
    std::optional<double> as_float() const;
    std::optional<bool> as_bool() const;
    std::optional<char32_t> as_char() const;
    std::optional<std::string> as_string() const;
    std::optional<BigInt> as_bigint() const;
    std::optional<ListType> as_list() const;
    std::optional<DictType> as_dict() const;
    std::optional<std::shared_ptr<KaynatInstance>> as_instance() const;
    std::optional<CallableType> as_callable() const;
    
    /**
     * @brief Comparison operators
     */
    bool operator==(const KaynatValue& other) const;
    bool operator!=(const KaynatValue& other) const;
    bool operator<(const KaynatValue& other) const;
    bool operator<=(const KaynatValue& other) const;
    bool operator>(const KaynatValue& other) const;
    bool operator>=(const KaynatValue& other) const;
    
private:
    ValueVariant value_;
};

} // namespace kaynat
