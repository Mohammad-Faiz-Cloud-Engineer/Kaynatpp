/**
 * @file parser.hpp
 * @brief Recursive descent parser for Kaynat++
 * 
 * Parses token stream into Abstract Syntax Tree.
 */

#pragma once

#include "nodes.hpp"
#include "../lexer/token_types.hpp"
#include <vector>
#include <memory>

namespace kaynat {

/**
 * @brief Recursive descent parser for Kaynat++
 * 
 * Converts token stream from lexer into AST.
 * Uses predictive parsing with one token lookahead.
 */
class Parser {
public:
    /**
     * @brief Construct parser with token stream
     * @param tokens Vector of tokens from lexer
     */
    explicit Parser(std::vector<Token> tokens);
    
    /**
     * @brief Parse tokens into AST
     * @return Root program node
     */
    std::shared_ptr<ProgramNode> parse();
    
private:
    std::vector<Token> tokens_;
    size_t current_;
    
    // Utility methods
    Token peek() const;
    Token previous() const;
    Token advance();
    bool check(TokenType type) const;
    bool match(TokenType type);
    bool match_any(const std::vector<TokenType>& types);
    Token consume(TokenType type, const std::string& message);
    bool is_at_end() const;
    
    // Parsing methods
    ASTNode parse_statement();
    ASTNode parse_assignment();
    ASTNode parse_if_statement();
    ASTNode parse_while_loop();
    ASTNode parse_repeat_loop();
    ASTNode parse_for_loop();
    ASTNode parse_function_def();
    ASTNode parse_return();
    ASTNode parse_expression_statement();
    
    // Expression parsing
    ASTNode parse_expression();
    ASTNode parse_logical_or();
    ASTNode parse_logical_and();
    ASTNode parse_equality();
    ASTNode parse_comparison();
    ASTNode parse_addition();
    ASTNode parse_multiplication();
    ASTNode parse_unary();
    ASTNode parse_call();
    ASTNode parse_primary();
    
    // Helper methods
    ASTNode parse_list_literal();
    bool peek_ahead_for_gui();
    ASTNode parse_gui_command();
    ASTNode parse_gui_set_command();
    ASTNode parse_gui_show();
    ASTNode parse_gui_place();
};

} // namespace kaynat
