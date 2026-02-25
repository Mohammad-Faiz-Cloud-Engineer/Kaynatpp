/**
 * @file runtime_value.cpp
 * @brief Runtime value implementation
 */

#include "runtime_value.hpp"
#include <sstream>
#include <iomanip>

namespace kaynat {

// BigInt implementation
BigInt::BigInt() : negative_(false) {
    digits_.push_back(0);
}

BigInt::BigInt(int64_t value) : negative_(value < 0) {
    if (value == 0) {
        digits_.push_back(0);
        return;
    }
    
    uint64_t abs_value = negative_ ? -value : value;
    while (abs_value > 0) {
        digits_.push_back(abs_value % BASE);
        abs_value /= BASE;
    }
}

BigInt::BigInt(const std::string& str) : negative_(false) {
    if (str.empty() || str == "0") {
        digits_.push_back(0);
        return;
    }
    
    size_t start = 0;
    if (str[0] == '-') {
        negative_ = true;
        start = 1;
    }
    
    // Parse in chunks of 9 digits
    for (size_t i = str.length(); i > start; i -= 9) {
        size_t chunk_start = (i >= start + 9) ? (i - 9) : start;
        std::string chunk = str.substr(chunk_start, i - chunk_start);
        digits_.push_back(std::stoi(chunk));
    }
    
    normalize();
}

void BigInt::normalize() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }
    
    if (digits_.size() == 1 && digits_[0] == 0) {
        negative_ = false;
    }
}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;
    result.digits_.clear();
    
    int carry = 0;
    size_t max_size = std::max(digits_.size(), other.digits_.size());
    
    for (size_t i = 0; i < max_size || carry; ++i) {
        int sum = carry;
        if (i < digits_.size()) sum += digits_[i];
        if (i < other.digits_.size()) sum += other.digits_[i];
        
        result.digits_.push_back(sum % BASE);
        carry = sum / BASE;
    }
    
    result.normalize();
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
    // Simplified implementation
    (void)other;  // Suppress unused warning
    BigInt result;
    result.digits_ = digits_;
    result.normalize();
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.digits_.assign(digits_.size() + other.digits_.size(), 0);
    
    for (size_t i = 0; i < digits_.size(); ++i) {
        int64_t carry = 0;
        for (size_t j = 0; j < other.digits_.size() || carry; ++j) {
            if (i + j >= result.digits_.size()) {
                result.digits_.push_back(0);
            }
            int64_t cur = result.digits_[i + j] + 
                         digits_[i] * 1LL * (j < other.digits_.size() ? other.digits_[j] : 0) + carry;
            result.digits_[i + j] = cur % BASE;
            carry = cur / BASE;
        }
    }
    
    result.negative_ = negative_ != other.negative_;
    result.normalize();
    return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
    // Simplified implementation
    (void)other;  // Suppress unused warning
    BigInt result;
    result.digits_ = {0};
    return result;
}

BigInt BigInt::operator%(const BigInt& other) const {
    // Simplified implementation
    (void)other;  // Suppress unused warning
    BigInt result;
    result.digits_ = {0};
    return result;
}

bool BigInt::operator==(const BigInt& other) const {
    return negative_ == other.negative_ && digits_ == other.digits_;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative_ != other.negative_) {
        return negative_;
    }
    
    if (digits_.size() != other.digits_.size()) {
        return negative_ ? digits_.size() > other.digits_.size() : digits_.size() < other.digits_.size();
    }
    
    for (int i = digits_.size() - 1; i >= 0; --i) {
        if (digits_[i] != other.digits_[i]) {
            return negative_ ? digits_[i] > other.digits_[i] : digits_[i] < other.digits_[i];
        }
    }
    
    return false;
}

bool BigInt::operator<=(const BigInt& other) const {
    return *this < other || *this == other;
}

bool BigInt::operator>(const BigInt& other) const {
    return !(*this <= other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

std::string BigInt::to_string() const {
    if (digits_.empty() || (digits_.size() == 1 && digits_[0] == 0)) {
        return "0";
    }
    
    std::ostringstream oss;
    if (negative_) oss << '-';
    
    oss << digits_.back();
    for (int i = digits_.size() - 2; i >= 0; --i) {
        oss << std::setw(9) << std::setfill('0') << digits_[i];
    }
    
    return oss.str();
}

// KaynatValue implementation
KaynatValue::KaynatValue() : value_(NullType{}) {}
KaynatValue::KaynatValue(NullType) : value_(NullType{}) {}
KaynatValue::KaynatValue(int64_t value) : value_(value) {}
KaynatValue::KaynatValue(double value) : value_(value) {}
KaynatValue::KaynatValue(bool value) : value_(value) {}
KaynatValue::KaynatValue(char32_t value) : value_(value) {}
KaynatValue::KaynatValue(const std::string& value) : value_(value) {}
KaynatValue::KaynatValue(const char* value) : value_(std::string(value)) {}
KaynatValue::KaynatValue(const BigInt& value) : value_(value) {}
KaynatValue::KaynatValue(const ListType& value) : value_(value) {}
KaynatValue::KaynatValue(const DictType& value) : value_(value) {}
KaynatValue::KaynatValue(std::shared_ptr<KaynatInstance> value) : value_(value) {}
KaynatValue::KaynatValue(CallableType value) : value_(value) {}

std::string KaynatValue::type_name() const {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, NullType>) return "Null";
        else if constexpr (std::is_same_v<T, int64_t>) return "Integer";
        else if constexpr (std::is_same_v<T, double>) return "Float";
        else if constexpr (std::is_same_v<T, bool>) return "Boolean";
        else if constexpr (std::is_same_v<T, char32_t>) return "Character";
        else if constexpr (std::is_same_v<T, std::string>) return "String";
        else if constexpr (std::is_same_v<T, BigInt>) return "BigInteger";
        else if constexpr (std::is_same_v<T, ListType>) return "List";
        else if constexpr (std::is_same_v<T, DictType>) return "Dictionary";
        else if constexpr (std::is_same_v<T, std::shared_ptr<KaynatInstance>>) return "Instance";
        else if constexpr (std::is_same_v<T, CallableType>) return "Function";
        
        return "Unknown";
    }, value_);
}

bool KaynatValue::is_null() const {
    return std::holds_alternative<NullType>(value_);
}

bool KaynatValue::is_truthy() const {
    return std::visit([](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, NullType>) return false;
        else if constexpr (std::is_same_v<T, bool>) return arg;
        else if constexpr (std::is_same_v<T, int64_t>) return arg != 0;
        else if constexpr (std::is_same_v<T, double>) return arg != 0.0;
        else if constexpr (std::is_same_v<T, std::string>) return !arg.empty();
        else if constexpr (std::is_same_v<T, ListType>) return !arg.empty();
        else if constexpr (std::is_same_v<T, DictType>) return !arg.empty();
        
        return true;
    }, value_);
}

std::string KaynatValue::to_string() const {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, NullType>) {
            return "nothing";
        }
        else if constexpr (std::is_same_v<T, int64_t>) {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<T, double>) {
            std::ostringstream oss;
            oss << arg;
            return oss.str();
        }
        else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "true" : "false";
        }
        else if constexpr (std::is_same_v<T, char32_t>) {
            // Convert UTF-32 to UTF-8 (simplified)
            return std::string(1, static_cast<char>(arg));
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            return arg;
        }
        else if constexpr (std::is_same_v<T, BigInt>) {
            return arg.to_string();
        }
        else if constexpr (std::is_same_v<T, ListType>) {
            std::ostringstream oss;
            oss << "[";
            for (size_t i = 0; i < arg.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << arg[i].to_string();
            }
            oss << "]";
            return oss.str();
        }
        else if constexpr (std::is_same_v<T, DictType>) {
            std::ostringstream oss;
            oss << "{";
            size_t i = 0;
            for (const auto& [key, value] : arg) {
                if (i++ > 0) oss << ", ";
                oss << key << ": " << value.to_string();
            }
            oss << "}";
            return oss.str();
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<KaynatInstance>>) {
            return "<instance>";
        }
        else if constexpr (std::is_same_v<T, CallableType>) {
            return "<function>";
        }
        
        return "<unknown>";
    }, value_);
}

std::optional<int64_t> KaynatValue::as_int() const {
    if (auto* val = std::get_if<int64_t>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<double> KaynatValue::as_float() const {
    if (auto* val = std::get_if<double>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<bool> KaynatValue::as_bool() const {
    if (auto* val = std::get_if<bool>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<char32_t> KaynatValue::as_char() const {
    if (auto* val = std::get_if<char32_t>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<std::string> KaynatValue::as_string() const {
    if (auto* val = std::get_if<std::string>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<BigInt> KaynatValue::as_bigint() const {
    if (auto* val = std::get_if<BigInt>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<ListType> KaynatValue::as_list() const {
    if (auto* val = std::get_if<ListType>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<DictType> KaynatValue::as_dict() const {
    if (auto* val = std::get_if<DictType>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<std::shared_ptr<KaynatInstance>> KaynatValue::as_instance() const {
    if (auto* val = std::get_if<std::shared_ptr<KaynatInstance>>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

std::optional<CallableType> KaynatValue::as_callable() const {
    if (auto* val = std::get_if<CallableType>(&value_)) {
        return *val;
    }
    return std::nullopt;
}

bool KaynatValue::operator==(const KaynatValue& other) const {
    if (value_.index() != other.value_.index()) {
        return false;
    }
    
    return std::visit([&other](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, std::shared_ptr<KaynatInstance>> ||
                      std::is_same_v<T, CallableType>) {
            return false; // Can't compare instances or functions
        } else {
            auto* other_val = std::get_if<T>(&other.value_);
            return other_val && arg == *other_val;
        }
    }, value_);
}

bool KaynatValue::operator!=(const KaynatValue& other) const {
    return !(*this == other);
}

bool KaynatValue::operator<(const KaynatValue& other) const {
    if (value_.index() != other.value_.index()) {
        return false;
    }
    
    return std::visit([&other](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, int64_t> || std::is_same_v<T, double> ||
                      std::is_same_v<T, std::string> || std::is_same_v<T, BigInt>) {
            auto* other_val = std::get_if<T>(&other.value_);
            return other_val && arg < *other_val;
        }
        
        return false;
    }, value_);
}

bool KaynatValue::operator<=(const KaynatValue& other) const {
    return *this < other || *this == other;
}

bool KaynatValue::operator>(const KaynatValue& other) const {
    return !(*this <= other);
}

bool KaynatValue::operator>=(const KaynatValue& other) const {
    return !(*this < other);
}

} // namespace kaynat
