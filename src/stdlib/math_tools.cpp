/**
 * @file math_tools.cpp
 * @brief Math utility functions
 */

#include "stdlib.hpp"
#include "../errors/error_types.hpp"
#include <cmath>
#include <algorithm>
#include <random>

namespace kaynat {
namespace stdlib {

static double get_number(const KaynatValue& val) {
    if (auto i = val.as_int()) return static_cast<double>(*i);
    if (auto f = val.as_float()) return *f;
    throw TypeError("Number", val.type_name(), 0, 0);
}

static int64_t get_int(const KaynatValue& val) {
    if (auto i = val.as_int()) return *i;
    if (auto f = val.as_float()) return static_cast<int64_t>(*f);
    throw TypeError("Integer", val.type_name(), 0, 0);
}

KaynatValue math_sqrt(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("sqrt expects 1 argument", 0, 0);
    return KaynatValue(std::sqrt(get_number(args[0])));
}

KaynatValue math_pow(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("pow expects 2 arguments", 0, 0);
    return KaynatValue(std::pow(get_number(args[0]), get_number(args[1])));
}

KaynatValue math_abs(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("abs expects 1 argument", 0, 0);
    return KaynatValue(std::abs(get_number(args[0])));
}

KaynatValue math_floor(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("floor expects 1 argument", 0, 0);
    return KaynatValue(std::floor(get_number(args[0])));
}

KaynatValue math_ceil(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("ceil expects 1 argument", 0, 0);
    return KaynatValue(std::ceil(get_number(args[0])));
}

KaynatValue math_round(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("round expects 1 argument", 0, 0);
    return KaynatValue(std::round(get_number(args[0])));
}

KaynatValue math_sin(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("sin expects 1 argument", 0, 0);
    return KaynatValue(std::sin(get_number(args[0])));
}

KaynatValue math_cos(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("cos expects 1 argument", 0, 0);
    return KaynatValue(std::cos(get_number(args[0])));
}

KaynatValue math_tan(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("tan expects 1 argument", 0, 0);
    return KaynatValue(std::tan(get_number(args[0])));
}

KaynatValue math_log(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("log expects 1 argument", 0, 0);
    return KaynatValue(std::log(get_number(args[0])));
}

KaynatValue math_log10(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("log10 expects 1 argument", 0, 0);
    return KaynatValue(std::log10(get_number(args[0])));
}

KaynatValue math_exp(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("exp expects 1 argument", 0, 0);
    return KaynatValue(std::exp(get_number(args[0])));
}

KaynatValue math_min(const std::vector<KaynatValue>& args) {
    if (args.empty()) throw RuntimeError("min expects at least 1 argument", 0, 0);
    double min_val = get_number(args[0]);
    for (size_t i = 1; i < args.size(); ++i) {
        min_val = std::min(min_val, get_number(args[i]));
    }
    return KaynatValue(min_val);
}

KaynatValue math_max(const std::vector<KaynatValue>& args) {
    if (args.empty()) throw RuntimeError("max expects at least 1 argument", 0, 0);
    double max_val = get_number(args[0]);
    for (size_t i = 1; i < args.size(); ++i) {
        max_val = std::max(max_val, get_number(args[i]));
    }
    return KaynatValue(max_val);
}

KaynatValue math_factorial(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("factorial expects 1 argument", 0, 0);
    int64_t n = get_int(args[0]);
    if (n < 0) throw RuntimeError("factorial requires non-negative integer", 0, 0);
    int64_t result = 1;
    for (int64_t i = 2; i <= n; ++i) {
        result *= i;
    }
    return KaynatValue(result);
}

KaynatValue math_gcd(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("gcd expects 2 arguments", 0, 0);
    int64_t a = std::abs(get_int(args[0]));
    int64_t b = std::abs(get_int(args[1]));
    while (b != 0) {
        int64_t temp = b;
        b = a % b;
        a = temp;
    }
    return KaynatValue(a);
}

KaynatValue math_lcm(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("lcm expects 2 arguments", 0, 0);
    int64_t a = std::abs(get_int(args[0]));
    int64_t b = std::abs(get_int(args[1]));
    if (a == 0 || b == 0) return KaynatValue(static_cast<int64_t>(0));
    
    // Calculate GCD first
    int64_t gcd_val = a;
    int64_t temp_b = b;
    while (temp_b != 0) {
        int64_t temp = temp_b;
        temp_b = gcd_val % temp_b;
        gcd_val = temp;
    }
    
    return KaynatValue((a / gcd_val) * b);
}

KaynatValue math_is_prime(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("is_prime expects 1 argument", 0, 0);
    int64_t n = get_int(args[0]);
    if (n < 2) return KaynatValue(false);
    if (n == 2) return KaynatValue(true);
    if (n % 2 == 0) return KaynatValue(false);
    
    for (int64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return KaynatValue(false);
    }
    return KaynatValue(true);
}

KaynatValue math_random(const std::vector<KaynatValue>& args) {
    if (!args.empty()) throw RuntimeError("random expects 0 arguments", 0, 0);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return KaynatValue(dis(gen));
}

KaynatValue math_pi(const std::vector<KaynatValue>& args) {
    if (!args.empty()) throw RuntimeError("pi expects 0 arguments", 0, 0);
    return KaynatValue(M_PI);
}

} // namespace stdlib
} // namespace kaynat
