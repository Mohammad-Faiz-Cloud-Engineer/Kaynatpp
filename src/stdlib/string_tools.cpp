/**
 * @file string_tools.cpp
 * @brief String utility functions
 */

#include "stdlib.hpp"
#include "../errors/error_types.hpp"
#include <algorithm>
#include <sstream>
#include <cctype>

namespace kaynat {
namespace stdlib {

static std::string get_string(const KaynatValue& val) {
    if (auto s = val.as_string()) return *s;
    return val.to_string();
}

KaynatValue string_uppercase(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("uppercase expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return KaynatValue(str);
}

KaynatValue string_lowercase(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("lowercase expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return KaynatValue(str);
}

KaynatValue string_length(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("length expects 1 argument", 0, 0);
    return KaynatValue(static_cast<int64_t>(get_string(args[0]).length()));
}

KaynatValue string_trim(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("trim expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    
    // Trim left
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    
    // Trim right
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    
    return KaynatValue(str);
}

KaynatValue string_split(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("split expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    std::string delimiter = get_string(args[1]);
    
    ListType result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        result.push_back(KaynatValue(str.substr(start, end - start)));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(KaynatValue(str.substr(start)));
    
    return KaynatValue(result);
}

KaynatValue string_join(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("join expects 2 arguments", 0, 0);
    auto list = args[0].as_list();
    if (!list) throw TypeError("List", args[0].type_name(), 0, 0);
    std::string delimiter = get_string(args[1]);
    
    std::ostringstream oss;
    for (size_t i = 0; i < list->size(); ++i) {
        if (i > 0) oss << delimiter;
        oss << (*list)[i].to_string();
    }
    return KaynatValue(oss.str());
}

KaynatValue string_replace(const std::vector<KaynatValue>& args) {
    if (args.size() != 3) throw RuntimeError("replace expects 3 arguments", 0, 0);
    std::string str = get_string(args[0]);
    std::string from = get_string(args[1]);
    std::string to = get_string(args[2]);
    
    if (from.empty()) return KaynatValue(str);
    
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return KaynatValue(str);
}

KaynatValue string_starts_with(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("starts_with expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    std::string prefix = get_string(args[1]);
    return KaynatValue(str.find(prefix) == 0);
}

KaynatValue string_ends_with(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("ends_with expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    std::string suffix = get_string(args[1]);
    if (suffix.length() > str.length()) return KaynatValue(false);
    return KaynatValue(str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0);
}

KaynatValue string_contains(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("contains expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    std::string substr = get_string(args[1]);
    return KaynatValue(str.find(substr) != std::string::npos);
}

KaynatValue string_substring(const std::vector<KaynatValue>& args) {
    if (args.size() < 2 || args.size() > 3) throw RuntimeError("substring expects 2 or 3 arguments", 0, 0);
    std::string str = get_string(args[0]);
    auto start_opt = args[1].as_int();
    if (!start_opt) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t start = static_cast<size_t>(*start_opt);
    if (start >= str.length()) return KaynatValue("");
    
    if (args.size() == 3) {
        auto len_opt = args[2].as_int();
        if (!len_opt) throw TypeError("Integer", args[2].type_name(), 0, 0);
        return KaynatValue(str.substr(start, static_cast<size_t>(*len_opt)));
    }
    
    return KaynatValue(str.substr(start));
}

KaynatValue string_index_of(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("index_of expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    std::string substr = get_string(args[1]);
    size_t pos = str.find(substr);
    return KaynatValue(pos == std::string::npos ? static_cast<int64_t>(-1) : static_cast<int64_t>(pos));
}

KaynatValue string_reverse(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("reverse expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    std::reverse(str.begin(), str.end());
    return KaynatValue(str);
}

KaynatValue string_repeat(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("repeat expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    auto count_opt = args[1].as_int();
    if (!count_opt) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    std::ostringstream oss;
    for (int64_t i = 0; i < *count_opt; ++i) {
        oss << str;
    }
    return KaynatValue(oss.str());
}

KaynatValue string_pad_left(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("pad_left expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    auto width_opt = args[1].as_int();
    if (!width_opt) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t width = static_cast<size_t>(*width_opt);
    if (str.length() >= width) return KaynatValue(str);
    return KaynatValue(std::string(width - str.length(), ' ') + str);
}

KaynatValue string_pad_right(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("pad_right expects 2 arguments", 0, 0);
    std::string str = get_string(args[0]);
    auto width_opt = args[1].as_int();
    if (!width_opt) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t width = static_cast<size_t>(*width_opt);
    if (str.length() >= width) return KaynatValue(str);
    return KaynatValue(str + std::string(width - str.length(), ' '));
}

KaynatValue string_to_number(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("to_number expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    try {
        if (str.find('.') != std::string::npos) {
            return KaynatValue(std::stod(str));
        } else {
            return KaynatValue(static_cast<int64_t>(std::stoll(str)));
        }
    } catch (...) {
        throw RuntimeError("Invalid number format", 0, 0);
    }
}

KaynatValue string_to_list(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("to_list expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    ListType result;
    for (char c : str) {
        result.push_back(KaynatValue(std::string(1, c)));
    }
    return KaynatValue(result);
}

KaynatValue string_is_empty(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("is_empty expects 1 argument", 0, 0);
    return KaynatValue(get_string(args[0]).empty());
}

KaynatValue string_capitalize(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("capitalize expects 1 argument", 0, 0);
    std::string str = get_string(args[0]);
    if (!str.empty()) {
        str[0] = std::toupper(str[0]);
    }
    return KaynatValue(str);
}

} // namespace stdlib
} // namespace kaynat
