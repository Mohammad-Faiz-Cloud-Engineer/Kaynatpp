/**
 * @file other_tools.cpp
 * @brief File, Date, Random, Network, JSON, Crypto, and Pattern tools
 */

#include "stdlib.hpp"
#include "../errors/error_types.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>
#include <iomanip>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

namespace kaynat {
namespace stdlib {

// ===== FILE TOOLS =====

KaynatValue file_read(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_read expects 1 argument", 0, 0);
    auto filename = args[0].as_string();
    if (!filename) throw TypeError("String", args[0].type_name(), 0, 0);
    
    std::ifstream file(*filename);
    if (!file) throw FileError(*filename, "cannot open file", 0, 0);
    
    std::ostringstream oss;
    oss << file.rdbuf();
    return KaynatValue(oss.str());
}

KaynatValue file_write(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("file_write expects 2 arguments", 0, 0);
    auto filename = args[0].as_string();
    if (!filename) throw TypeError("String", args[0].type_name(), 0, 0);
    
    std::ofstream file(*filename);
    if (!file) throw FileError(*filename, "cannot write file", 0, 0);
    
    file << args[1].to_string();
    return KaynatValue(true);
}

KaynatValue file_append(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("file_append expects 2 arguments", 0, 0);
    auto filename = args[0].as_string();
    if (!filename) throw TypeError("String", args[0].type_name(), 0, 0);
    
    std::ofstream file(*filename, std::ios::app);
    if (!file) throw FileError(*filename, "cannot append to file", 0, 0);
    
    file << args[1].to_string();
    return KaynatValue(true);
}

KaynatValue file_exists(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_exists expects 1 argument", 0, 0);
    auto filename = args[0].as_string();
    if (!filename) throw TypeError("String", args[0].type_name(), 0, 0);
    return KaynatValue(fs::exists(*filename));
}

KaynatValue file_delete(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_delete expects 1 argument", 0, 0);
    auto filename = args[0].as_string();
    if (!filename) throw TypeError("String", args[0].type_name(), 0, 0);
    return KaynatValue(fs::remove(*filename));
}

KaynatValue file_copy(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("file_copy expects 2 arguments", 0, 0);
    auto src = args[0].as_string();
    auto dst = args[1].as_string();
    if (!src || !dst) throw TypeError("String", "unknown", 0, 0);
    
    try {
        fs::copy(*src, *dst, fs::copy_options::overwrite_existing);
        return KaynatValue(true);
    } catch (...) {
        return KaynatValue(false);
    }
}

KaynatValue file_move(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("file_move expects 2 arguments", 0, 0);
    auto src = args[0].as_string();
    auto dst = args[1].as_string();
    if (!src || !dst) throw TypeError("String", "unknown", 0, 0);
    
    try {
        fs::rename(*src, *dst);
        return KaynatValue(true);
    } catch (...) {
        return KaynatValue(false);
    }
}

KaynatValue file_size(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_size expects 1 argument", 0, 0);
    auto filename = args[0].as_string();
    if (!filename) throw TypeError("String", args[0].type_name(), 0, 0);
    
    try {
        return KaynatValue(static_cast<int64_t>(fs::file_size(*filename)));
    } catch (...) {
        return KaynatValue(static_cast<int64_t>(-1));
    }
}

KaynatValue file_list_dir(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_list_dir expects 1 argument", 0, 0);
    auto dirname = args[0].as_string();
    if (!dirname) throw TypeError("String", args[0].type_name(), 0, 0);
    
    ListType result;
    try {
        for (const auto& entry : fs::directory_iterator(*dirname)) {
            result.push_back(KaynatValue(entry.path().filename().string()));
        }
    } catch (...) {
        // Return empty list on error
    }
    return KaynatValue(result);
}

KaynatValue file_create_dir(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_create_dir expects 1 argument", 0, 0);
    auto dirname = args[0].as_string();
    if (!dirname) throw TypeError("String", args[0].type_name(), 0, 0);
    return KaynatValue(fs::create_directories(*dirname));
}

KaynatValue file_is_file(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_is_file expects 1 argument", 0, 0);
    auto path = args[0].as_string();
    if (!path) throw TypeError("String", args[0].type_name(), 0, 0);
    return KaynatValue(fs::is_regular_file(*path));
}

KaynatValue file_is_dir(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("file_is_dir expects 1 argument", 0, 0);
    auto path = args[0].as_string();
    if (!path) throw TypeError("String", args[0].type_name(), 0, 0);
    return KaynatValue(fs::is_directory(*path));
}

// ===== DATE TOOLS =====

KaynatValue date_now(const std::vector<KaynatValue>& args) {
    if (!args.empty()) throw RuntimeError("date_now expects 0 arguments", 0, 0);
    auto now = std::time(nullptr);
    return KaynatValue(static_cast<int64_t>(now));
}

KaynatValue date_format(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("date_format expects 2 arguments", 0, 0);
    auto timestamp = args[0].as_int();
    auto format = args[1].as_string();
    if (!timestamp || !format) throw TypeError("Integer/String", "unknown", 0, 0);
    
    std::time_t time = static_cast<std::time_t>(*timestamp);
    std::tm* tm = std::localtime(&time);
    
    std::ostringstream oss;
    oss << std::put_time(tm, format->c_str());
    return KaynatValue(oss.str());
}

KaynatValue date_parse([[maybe_unused]] const std::vector<KaynatValue>& args) {
    // Simplified - returns current time
    return date_now({});
}

KaynatValue date_add_days(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("date_add_days expects 2 arguments", 0, 0);
    auto timestamp = args[0].as_int();
    auto days = args[1].as_int();
    if (!timestamp || !days) throw TypeError("Integer", "unknown", 0, 0);
    
    return KaynatValue(*timestamp + (*days * 86400));
}

KaynatValue date_diff_days(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("date_diff_days expects 2 arguments", 0, 0);
    auto time1 = args[0].as_int();
    auto time2 = args[1].as_int();
    if (!time1 || !time2) throw TypeError("Integer", "unknown", 0, 0);
    
    return KaynatValue((*time2 - *time1) / 86400);
}

// ===== RANDOM TOOLS =====

static std::random_device rd;
static std::mt19937 gen(rd());

KaynatValue random_int(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("random_int expects 2 arguments", 0, 0);
    auto min = args[0].as_int();
    auto max = args[1].as_int();
    if (!min || !max) throw TypeError("Integer", "unknown", 0, 0);
    
    std::uniform_int_distribution<int64_t> dis(*min, *max);
    return KaynatValue(dis(gen));
}

KaynatValue random_float(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("random_float expects 2 arguments", 0, 0);
    double min = args[0].as_float() ? *args[0].as_float() : static_cast<double>(*args[0].as_int());
    double max = args[1].as_float() ? *args[1].as_float() : static_cast<double>(*args[1].as_int());
    
    std::uniform_real_distribution<double> dis(min, max);
    return KaynatValue(dis(gen));
}

KaynatValue random_choice(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("random_choice expects 1 argument", 0, 0);
    auto list = args[0].as_list();
    if (!list || list->empty()) throw RuntimeError("random_choice requires non-empty list", 0, 0);
    
    std::uniform_int_distribution<size_t> dis(0, list->size() - 1);
    return (*list)[dis(gen)];
}

KaynatValue random_shuffle(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("random_shuffle expects 1 argument", 0, 0);
    auto list = args[0].as_list();
    if (!list) throw TypeError("List", args[0].type_name(), 0, 0);
    
    ListType result = *list;
    std::shuffle(result.begin(), result.end(), gen);
    return KaynatValue(result);
}

KaynatValue random_sample(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("random_sample expects 2 arguments", 0, 0);
    auto list = args[0].as_list();
    auto count = args[1].as_int();
    if (!list || !count) throw TypeError("List/Integer", "unknown", 0, 0);
    
    ListType shuffled = *list;
    std::shuffle(shuffled.begin(), shuffled.end(), gen);
    
    size_t n = std::min(static_cast<size_t>(*count), shuffled.size());
    return KaynatValue(ListType(shuffled.begin(), shuffled.begin() + n));
}

KaynatValue random_seed(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("random_seed expects 1 argument", 0, 0);
    auto seed = args[0].as_int();
    if (!seed) throw TypeError("Integer", args[0].type_name(), 0, 0);
    
    gen.seed(static_cast<unsigned int>(*seed));
    return KaynatValue();
}

// ===== NETWORK TOOLS (Simplified - no actual HTTP) =====

KaynatValue network_http_get(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("http_get expects 1 argument", 0, 0);
    // Simplified - would need libcurl
    return KaynatValue("HTTP GET not implemented - requires libcurl");
}

KaynatValue network_http_post(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("http_post expects 2 arguments", 0, 0);
    // Simplified - would need libcurl
    return KaynatValue("HTTP POST not implemented - requires libcurl");
}

// ===== JSON TOOLS (Simplified) =====

KaynatValue json_parse(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("json_parse expects 1 argument", 0, 0);
    // Simplified - would need nlohmann/json
    return KaynatValue("JSON parse not implemented - requires nlohmann/json");
}

KaynatValue json_stringify(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("json_stringify expects 1 argument", 0, 0);
    // Simplified - basic conversion
    return KaynatValue(args[0].to_string());
}

KaynatValue json_format(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("json_format expects 1 argument", 0, 0);
    return json_stringify(args);
}

// ===== CRYPTO TOOLS (Simplified) =====

KaynatValue crypto_sha256(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("sha256 expects 1 argument", 0, 0);
    // Simplified - would need OpenSSL
    return KaynatValue("SHA256 not implemented - requires OpenSSL");
}

KaynatValue crypto_md5(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("md5 expects 1 argument", 0, 0);
    // Simplified - would need OpenSSL
    return KaynatValue("MD5 not implemented - requires OpenSSL");
}

KaynatValue crypto_base64_encode(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("base64_encode expects 1 argument", 0, 0);
    auto str = args[0].as_string();
    if (!str) throw TypeError("String", args[0].type_name(), 0, 0);
    
    static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string result;
    int val = 0, valb = -6;
    
    for (unsigned char c : *str) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            result.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) result.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (result.size() % 4) result.push_back('=');
    
    return KaynatValue(result);
}

KaynatValue crypto_base64_decode(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("base64_decode expects 1 argument", 0, 0);
    // Simplified
    return KaynatValue("Base64 decode not fully implemented");
}

KaynatValue crypto_random_token(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("random_token expects 1 argument", 0, 0);
    auto length = args[0].as_int();
    if (!length) throw TypeError("Integer", args[0].type_name(), 0, 0);
    
    static const char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<size_t> dis(0, 61);
    
    std::string result;
    for (int64_t i = 0; i < *length; ++i) {
        result += chars[dis(gen)];
    }
    return KaynatValue(result);
}

// ===== PATTERN TOOLS =====

KaynatValue pattern_match(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("pattern_match expects 2 arguments", 0, 0);
    auto pattern = args[0].as_string();
    auto text = args[1].as_string();
    if (!pattern || !text) throw TypeError("String", "unknown", 0, 0);
    
    try {
        std::regex re(*pattern);
        return KaynatValue(std::regex_search(*text, re));
    } catch (...) {
        throw RuntimeError("Invalid regex pattern", 0, 0);
    }
}

KaynatValue pattern_find_all(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("pattern_find_all expects 2 arguments", 0, 0);
    auto pattern = args[0].as_string();
    auto text = args[1].as_string();
    if (!pattern || !text) throw TypeError("String", "unknown", 0, 0);
    
    try {
        std::regex re(*pattern);
        ListType result;
        
        auto begin = std::sregex_iterator(text->begin(), text->end(), re);
        auto end = std::sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            result.push_back(KaynatValue(it->str()));
        }
        
        return KaynatValue(result);
    } catch (...) {
        throw RuntimeError("Invalid regex pattern", 0, 0);
    }
}

KaynatValue pattern_replace(const std::vector<KaynatValue>& args) {
    if (args.size() != 3) throw RuntimeError("pattern_replace expects 3 arguments", 0, 0);
    auto pattern = args[0].as_string();
    auto replacement = args[1].as_string();
    auto text = args[2].as_string();
    if (!pattern || !replacement || !text) throw TypeError("String", "unknown", 0, 0);
    
    try {
        std::regex re(*pattern);
        return KaynatValue(std::regex_replace(*text, re, *replacement));
    } catch (...) {
        throw RuntimeError("Invalid regex pattern", 0, 0);
    }
}

KaynatValue pattern_split(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("pattern_split expects 2 arguments", 0, 0);
    auto pattern = args[0].as_string();
    auto text = args[1].as_string();
    if (!pattern || !text) throw TypeError("String", "unknown", 0, 0);
    
    try {
        std::regex re(*pattern);
        ListType result;
        
        std::sregex_token_iterator begin(text->begin(), text->end(), re, -1);
        std::sregex_token_iterator end;
        
        for (auto it = begin; it != end; ++it) {
            result.push_back(KaynatValue(it->str()));
        }
        
        return KaynatValue(result);
    } catch (...) {
        throw RuntimeError("Invalid regex pattern", 0, 0);
    }
}

KaynatValue pattern_is_email(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("is_email expects 1 argument", 0, 0);
    auto text = args[0].as_string();
    if (!text) throw TypeError("String", args[0].type_name(), 0, 0);
    
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return KaynatValue(std::regex_match(*text, email_pattern));
}

KaynatValue pattern_is_url(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("is_url expects 1 argument", 0, 0);
    auto text = args[0].as_string();
    if (!text) throw TypeError("String", args[0].type_name(), 0, 0);
    
    std::regex url_pattern(R"(https?://[^\s]+)");
    return KaynatValue(std::regex_match(*text, url_pattern));
}

} // namespace stdlib
} // namespace kaynat
