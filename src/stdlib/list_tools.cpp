/**
 * @file list_tools.cpp
 * @brief List utility functions
 */

#include "stdlib.hpp"
#include "../errors/error_types.hpp"
#include <algorithm>
#include <numeric>

namespace kaynat {
namespace stdlib {

static ListType get_list(const KaynatValue& val) {
    auto list = val.as_list();
    if (!list) throw TypeError("List", val.type_name(), 0, 0);
    return *list;
}

KaynatValue list_length(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_length expects 1 argument", 0, 0);
    return KaynatValue(static_cast<int64_t>(get_list(args[0]).size()));
}

KaynatValue list_append(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("list_append expects 2 arguments", 0, 0);
    ListType list = get_list(args[0]);
    list.push_back(args[1]);
    return KaynatValue(list);
}

KaynatValue list_prepend(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("list_prepend expects 2 arguments", 0, 0);
    ListType list = get_list(args[0]);
    list.insert(list.begin(), args[1]);
    return KaynatValue(list);
}

KaynatValue list_insert(const std::vector<KaynatValue>& args) {
    if (args.size() != 3) throw RuntimeError("list_insert expects 3 arguments", 0, 0);
    ListType list = get_list(args[0]);
    auto idx = args[1].as_int();
    if (!idx) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t index = static_cast<size_t>(*idx);
    if (index > list.size()) index = list.size();
    list.insert(list.begin() + index, args[2]);
    return KaynatValue(list);
}

KaynatValue list_remove(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("list_remove expects 2 arguments", 0, 0);
    ListType list = get_list(args[0]);
    auto idx = args[1].as_int();
    if (!idx) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t index = static_cast<size_t>(*idx);
    if (index < list.size()) {
        list.erase(list.begin() + index);
    }
    return KaynatValue(list);
}

KaynatValue list_get(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("list_get expects 2 arguments", 0, 0);
    ListType list = get_list(args[0]);
    auto idx = args[1].as_int();
    if (!idx) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t index = static_cast<size_t>(*idx);
    if (index >= list.size()) throw IndexError(*idx, list.size(), 0, 0);
    return list[index];
}

KaynatValue list_set(const std::vector<KaynatValue>& args) {
    if (args.size() != 3) throw RuntimeError("list_set expects 3 arguments", 0, 0);
    ListType list = get_list(args[0]);
    auto idx = args[1].as_int();
    if (!idx) throw TypeError("Integer", args[1].type_name(), 0, 0);
    
    size_t index = static_cast<size_t>(*idx);
    if (index >= list.size()) throw IndexError(*idx, list.size(), 0, 0);
    list[index] = args[2];
    return KaynatValue(list);
}

KaynatValue list_slice(const std::vector<KaynatValue>& args) {
    if (args.size() != 3) throw RuntimeError("list_slice expects 3 arguments", 0, 0);
    ListType list = get_list(args[0]);
    auto start_opt = args[1].as_int();
    auto end_opt = args[2].as_int();
    if (!start_opt || !end_opt) throw TypeError("Integer", "unknown", 0, 0);
    
    size_t start = std::max(static_cast<int64_t>(0), *start_opt);
    size_t end = std::min(static_cast<size_t>(*end_opt), list.size());
    
    ListType result(list.begin() + start, list.begin() + end);
    return KaynatValue(result);
}

KaynatValue list_sort(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_sort expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    std::sort(list.begin(), list.end(), [](const KaynatValue& a, const KaynatValue& b) {
        return a < b;
    });
    return KaynatValue(list);
}

KaynatValue list_reverse(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_reverse expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    std::reverse(list.begin(), list.end());
    return KaynatValue(list);
}

KaynatValue list_contains(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("list_contains expects 2 arguments", 0, 0);
    ListType list = get_list(args[0]);
    return KaynatValue(std::find(list.begin(), list.end(), args[1]) != list.end());
}

KaynatValue list_index_of(const std::vector<KaynatValue>& args) {
    if (args.size() != 2) throw RuntimeError("list_index_of expects 2 arguments", 0, 0);
    ListType list = get_list(args[0]);
    auto it = std::find(list.begin(), list.end(), args[1]);
    return KaynatValue(it == list.end() ? static_cast<int64_t>(-1) : static_cast<int64_t>(it - list.begin()));
}

KaynatValue list_min(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_min expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    if (list.empty()) throw RuntimeError("Cannot find min of empty list", 0, 0);
    return *std::min_element(list.begin(), list.end());
}

KaynatValue list_max(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_max expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    if (list.empty()) throw RuntimeError("Cannot find max of empty list", 0, 0);
    return *std::max_element(list.begin(), list.end());
}

KaynatValue list_sum(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_sum expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    double sum = 0.0;
    for (const auto& val : list) {
        if (auto i = val.as_int()) sum += *i;
        else if (auto f = val.as_float()) sum += *f;
    }
    return KaynatValue(sum);
}

KaynatValue list_filter(const std::vector<KaynatValue>& args) {
    // Simplified - would need function support
    if (args.size() != 1) throw RuntimeError("list_filter expects 1 argument", 0, 0);
    return args[0];
}

KaynatValue list_map(const std::vector<KaynatValue>& args) {
    // Simplified - would need function support
    if (args.size() != 1) throw RuntimeError("list_map expects 1 argument", 0, 0);
    return args[0];
}

KaynatValue list_reduce(const std::vector<KaynatValue>& args) {
    // Simplified - would need function support
    if (args.size() != 1) throw RuntimeError("list_reduce expects 1 argument", 0, 0);
    return args[0];
}

KaynatValue list_unique(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_unique expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    ListType result;
    for (const auto& val : list) {
        if (std::find(result.begin(), result.end(), val) == result.end()) {
            result.push_back(val);
        }
    }
    return KaynatValue(result);
}

KaynatValue list_flatten(const std::vector<KaynatValue>& args) {
    if (args.size() != 1) throw RuntimeError("list_flatten expects 1 argument", 0, 0);
    ListType list = get_list(args[0]);
    ListType result;
    for (const auto& val : list) {
        if (auto nested = val.as_list()) {
            result.insert(result.end(), nested->begin(), nested->end());
        } else {
            result.push_back(val);
        }
    }
    return KaynatValue(result);
}

} // namespace stdlib
} // namespace kaynat
