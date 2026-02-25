/**
 * @file stdlib.hpp
 * @brief Standard library functions for Kaynat++
 * 
 * Provides 99 built-in functions across 10 modules:
 * - Math tools (20 functions)
 * - String tools (20 functions)
 * - List tools (20 functions)
 * - File tools (12 functions)
 * - Date tools (5 functions)
 * - Random tools (6 functions)
 * - Network tools (2 functions)
 * - JSON tools (3 functions)
 * - Crypto tools (5 functions)
 * - Pattern tools (6 functions)
 */

#pragma once

#include "../interpreter/runtime_value.hpp"
#include <vector>
#include <string>

namespace kaynat {
namespace stdlib {

// Math Tools (20 functions)
KaynatValue math_sqrt(const std::vector<KaynatValue>& args);
KaynatValue math_pow(const std::vector<KaynatValue>& args);
KaynatValue math_abs(const std::vector<KaynatValue>& args);
KaynatValue math_floor(const std::vector<KaynatValue>& args);
KaynatValue math_ceil(const std::vector<KaynatValue>& args);
KaynatValue math_round(const std::vector<KaynatValue>& args);
KaynatValue math_sin(const std::vector<KaynatValue>& args);
KaynatValue math_cos(const std::vector<KaynatValue>& args);
KaynatValue math_tan(const std::vector<KaynatValue>& args);
KaynatValue math_log(const std::vector<KaynatValue>& args);
KaynatValue math_log10(const std::vector<KaynatValue>& args);
KaynatValue math_exp(const std::vector<KaynatValue>& args);
KaynatValue math_min(const std::vector<KaynatValue>& args);
KaynatValue math_max(const std::vector<KaynatValue>& args);
KaynatValue math_factorial(const std::vector<KaynatValue>& args);
KaynatValue math_gcd(const std::vector<KaynatValue>& args);
KaynatValue math_lcm(const std::vector<KaynatValue>& args);
KaynatValue math_is_prime(const std::vector<KaynatValue>& args);
KaynatValue math_random(const std::vector<KaynatValue>& args);
KaynatValue math_pi(const std::vector<KaynatValue>& args);

// String Tools (20 functions)
KaynatValue string_uppercase(const std::vector<KaynatValue>& args);
KaynatValue string_lowercase(const std::vector<KaynatValue>& args);
KaynatValue string_length(const std::vector<KaynatValue>& args);
KaynatValue string_trim(const std::vector<KaynatValue>& args);
KaynatValue string_split(const std::vector<KaynatValue>& args);
KaynatValue string_join(const std::vector<KaynatValue>& args);
KaynatValue string_replace(const std::vector<KaynatValue>& args);
KaynatValue string_starts_with(const std::vector<KaynatValue>& args);
KaynatValue string_ends_with(const std::vector<KaynatValue>& args);
KaynatValue string_contains(const std::vector<KaynatValue>& args);
KaynatValue string_substring(const std::vector<KaynatValue>& args);
KaynatValue string_index_of(const std::vector<KaynatValue>& args);
KaynatValue string_reverse(const std::vector<KaynatValue>& args);
KaynatValue string_repeat(const std::vector<KaynatValue>& args);
KaynatValue string_pad_left(const std::vector<KaynatValue>& args);
KaynatValue string_pad_right(const std::vector<KaynatValue>& args);
KaynatValue string_to_number(const std::vector<KaynatValue>& args);
KaynatValue string_to_list(const std::vector<KaynatValue>& args);
KaynatValue string_is_empty(const std::vector<KaynatValue>& args);
KaynatValue string_capitalize(const std::vector<KaynatValue>& args);

// List Tools (20 functions)
KaynatValue list_length(const std::vector<KaynatValue>& args);
KaynatValue list_append(const std::vector<KaynatValue>& args);
KaynatValue list_prepend(const std::vector<KaynatValue>& args);
KaynatValue list_insert(const std::vector<KaynatValue>& args);
KaynatValue list_remove(const std::vector<KaynatValue>& args);
KaynatValue list_get(const std::vector<KaynatValue>& args);
KaynatValue list_set(const std::vector<KaynatValue>& args);
KaynatValue list_slice(const std::vector<KaynatValue>& args);
KaynatValue list_sort(const std::vector<KaynatValue>& args);
KaynatValue list_reverse(const std::vector<KaynatValue>& args);
KaynatValue list_contains(const std::vector<KaynatValue>& args);
KaynatValue list_index_of(const std::vector<KaynatValue>& args);
KaynatValue list_min(const std::vector<KaynatValue>& args);
KaynatValue list_max(const std::vector<KaynatValue>& args);
KaynatValue list_sum(const std::vector<KaynatValue>& args);
KaynatValue list_filter(const std::vector<KaynatValue>& args);
KaynatValue list_map(const std::vector<KaynatValue>& args);
KaynatValue list_reduce(const std::vector<KaynatValue>& args);
KaynatValue list_unique(const std::vector<KaynatValue>& args);
KaynatValue list_flatten(const std::vector<KaynatValue>& args);

// File Tools (12 functions)
KaynatValue file_read(const std::vector<KaynatValue>& args);
KaynatValue file_write(const std::vector<KaynatValue>& args);
KaynatValue file_append(const std::vector<KaynatValue>& args);
KaynatValue file_exists(const std::vector<KaynatValue>& args);
KaynatValue file_delete(const std::vector<KaynatValue>& args);
KaynatValue file_copy(const std::vector<KaynatValue>& args);
KaynatValue file_move(const std::vector<KaynatValue>& args);
KaynatValue file_size(const std::vector<KaynatValue>& args);
KaynatValue file_list_dir(const std::vector<KaynatValue>& args);
KaynatValue file_create_dir(const std::vector<KaynatValue>& args);
KaynatValue file_is_file(const std::vector<KaynatValue>& args);
KaynatValue file_is_dir(const std::vector<KaynatValue>& args);

// Date Tools (5 functions)
KaynatValue date_now(const std::vector<KaynatValue>& args);
KaynatValue date_format(const std::vector<KaynatValue>& args);
KaynatValue date_parse(const std::vector<KaynatValue>& args);
KaynatValue date_add_days(const std::vector<KaynatValue>& args);
KaynatValue date_diff_days(const std::vector<KaynatValue>& args);

// Random Tools (6 functions)
KaynatValue random_int(const std::vector<KaynatValue>& args);
KaynatValue random_float(const std::vector<KaynatValue>& args);
KaynatValue random_choice(const std::vector<KaynatValue>& args);
KaynatValue random_shuffle(const std::vector<KaynatValue>& args);
KaynatValue random_sample(const std::vector<KaynatValue>& args);
KaynatValue random_seed(const std::vector<KaynatValue>& args);

// Network Tools (2 functions)
KaynatValue network_http_get(const std::vector<KaynatValue>& args);
KaynatValue network_http_post(const std::vector<KaynatValue>& args);

// JSON Tools (3 functions)
KaynatValue json_parse(const std::vector<KaynatValue>& args);
KaynatValue json_stringify(const std::vector<KaynatValue>& args);
KaynatValue json_format(const std::vector<KaynatValue>& args);

// Crypto Tools (5 functions)
KaynatValue crypto_sha256(const std::vector<KaynatValue>& args);
KaynatValue crypto_md5(const std::vector<KaynatValue>& args);
KaynatValue crypto_base64_encode(const std::vector<KaynatValue>& args);
KaynatValue crypto_base64_decode(const std::vector<KaynatValue>& args);
KaynatValue crypto_random_token(const std::vector<KaynatValue>& args);

// Pattern Tools (6 functions)
KaynatValue pattern_match(const std::vector<KaynatValue>& args);
KaynatValue pattern_find_all(const std::vector<KaynatValue>& args);
KaynatValue pattern_replace(const std::vector<KaynatValue>& args);
KaynatValue pattern_split(const std::vector<KaynatValue>& args);
KaynatValue pattern_is_email(const std::vector<KaynatValue>& args);
KaynatValue pattern_is_url(const std::vector<KaynatValue>& args);

} // namespace stdlib
} // namespace kaynat
