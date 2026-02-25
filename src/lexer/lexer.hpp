/**
 * @file lexer.hpp
 * @brief Lexical analyzer for Kaynat++
 * 
 * Tokenizes Kaynat++ source code into a stream of tokens.
 * Handles English keywords, identifiers, literals, and punctuation.
 */

#pragma once

#include "token_types.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <string_view>

namespace kaynat {

/**
 * @brief Lexical analyzer for Kaynat++ source code
 * 
 * Converts source text into tokens. Recognizes:
 * - English keywords (set, if, while, etc.)
 * - Identifiers (variable names)
 * - Literals (numbers, strings, booleans)
 * - Punctuation (period, comma)
 * 
 * Thread-safe for independent instances.
 */
class Lexer {
public:
    /**
     * @brief Construct lexer with source code
     * @param source Source code to tokenize
     */
    explicit Lexer(std::string source);
    
    /**
     * @brief Tokenize entire source
     * @return Vector of all tokens including EOF
     */
    std::vector<Token> tokenize();
    
private:
    std::string source_;
    size_t position_;
    uint32_t line_;
    uint32_t column_;
    
    static const std::unordered_map<std::string, TokenType> keywords_;
    
    /**
     * @brief Get next token from source
     */
    Token next_token();
    
    /**
     * @brief Peek at current character without consuming
     */
    char peek() const;
    
    /**
     * @brief Peek ahead n characters
     */
    char peek_ahead(size_t n) const;
    
    /**
     * @brief Consume and return current character
     */
    char advance();
    
    /**
     * @brief Check if at end of source
     */
    bool is_at_end() const;
    
    /**
     * @brief Skip whitespace and comments
     */
    void skip_whitespace();
    
    /**
     * @brief Tokenize a number (integer or float)
     */
    Token tokenize_number();
    
    /**
     * @brief Tokenize a string literal
     */
    Token tokenize_string();
    
    /**
     * @brief Tokenize an identifier or keyword
     */
    Token tokenize_identifier();
    
    /**
     * @brief Check if character is valid identifier start
     */
    static bool is_identifier_start(char c);
    
    /**
     * @brief Check if character is valid identifier continuation
     */
    static bool is_identifier_continue(char c);
    
    /**
     * @brief Create token at current position
     */
    Token make_token(TokenType type, std::string lexeme);
    
    /**
     * @brief Create error token
     */
    Token make_error_token(std::string message);
};

} // namespace kaynat
