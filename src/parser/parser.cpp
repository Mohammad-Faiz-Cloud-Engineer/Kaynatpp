/**
 * @file parser.cpp
 * @brief Parser implementation for Kaynat++
 */

#include "parser.hpp"
#include "../errors/error_types.hpp"
#include <algorithm>

namespace kaynat {

Parser::Parser(std::vector<Token> tokens)
    : tokens_(std::move(tokens)), current_(0) {}

std::shared_ptr<ProgramNode> Parser::parse() {
    auto program = std::make_shared<ProgramNode>();
    program->line = 1;
    
    // Skip optional "begin program."
    if (match(TokenType::BEGIN)) {
        match(TokenType::PROGRAM);
        match(TokenType::PERIOD);
    }
    
    while (!is_at_end()) {
        // Skip "end program."
        if (check(TokenType::END) && current_ + 1 < tokens_.size() && 
            tokens_[current_ + 1].type == TokenType::PROGRAM) {
            break;
        }
        
        program->statements.push_back(parse_statement());
    }
    
    return program;
}

Token Parser::peek() const {
    return tokens_[current_];
}

Token Parser::previous() const {
    return tokens_[current_ - 1];
}

Token Parser::advance() {
    if (!is_at_end()) current_++;
    return previous();
}

bool Parser::check(TokenType type) const {
    if (is_at_end()) return false;
    return peek().type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::match_any(const std::vector<TokenType>& types) {
    for (TokenType type : types) {
        if (match(type)) return true;
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    
    Token current = peek();
    throw ParserError(message, current.line, current.column);
}

bool Parser::is_at_end() const {
    return peek().type == TokenType::END_OF_FILE;
}

ASTNode Parser::parse_statement() {
    // Comments: note. text. or note text.
    if (match(TokenType::NOTE)) {
        // Skip everything until we find a period
        while (!is_at_end() && !check(TokenType::PERIOD)) {
            advance();
        }
        consume(TokenType::PERIOD, "Expected '.' at end of comment");
        // Return empty statement
        return ASTNode();
    }
    
    // GUI commands: set the title of... (check before regular set)
    if (check(TokenType::SET) && peek_ahead_for_gui()) {
        return parse_gui_set_command();
    }
    
    // Variable assignment: set x to 5.
    if (match(TokenType::SET) || match(TokenType::LET)) {
        return parse_assignment();
    }
    
    // Constant: always pi to 3.14.
    if (match(TokenType::ALWAYS)) {
        return parse_assignment();
    }
    
    // If statement
    if (match(TokenType::IF)) {
        return parse_if_statement();
    }
    
    // While loop
    if (match(TokenType::WHILE)) {
        return parse_while_loop();
    }
    
    // Repeat loop
    if (match(TokenType::REPEAT)) {
        return parse_repeat_loop();
    }
    
    // For loop
    if (match(TokenType::LOOP)) {
        return parse_for_loop();
    }
    
    // Function definition
    if (match(TokenType::DEFINE)) {
        return parse_function_def();
    }
    
    // Return statement
    if (match(TokenType::GIVE)) {
        return parse_return();
    }
    
    // GUI commands: create a window called...
    if (match(TokenType::CREATE)) {
        return parse_gui_command();
    }
    
    // GUI commands: show window
    if (match(TokenType::SHOW)) {
        return parse_gui_show();
    }
    
    // GUI commands: place widget at...
    if (match(TokenType::PLACE)) {
        return parse_gui_place();
    }
    
    // Expression statement (function call, etc.)
    return parse_expression_statement();
}

ASTNode Parser::parse_assignment() {
    bool is_constant = previous().type == TokenType::ALWAYS;
    
    Token name_token = consume(TokenType::IDENTIFIER, "Expected variable name");
    consume(TokenType::TO, "Expected 'to' after variable name");
    
    ASTNode value = parse_expression();
    consume(TokenType::PERIOD, "Expected '.' at end of statement");
    
    auto node = std::make_shared<AssignmentNode>();
    node->name = name_token.lexeme;
    node->value = value;
    node->is_constant = is_constant;
    node->line = name_token.line;
    
    return node;
}

ASTNode Parser::parse_if_statement() {
    ASTNode condition = parse_expression();
    consume(TokenType::THEN, "Expected 'then' after condition");
    consume(TokenType::PERIOD, "Expected '.' after 'then'");
    
    std::vector<ASTNode> then_branch;
    while (!check(TokenType::OTHERWISE) && !check(TokenType::END) && !is_at_end()) {
        then_branch.push_back(parse_statement());
    }
    
    std::vector<ASTNode> else_branch;
    if (match(TokenType::OTHERWISE)) {
        consume(TokenType::PERIOD, "Expected '.' after 'otherwise'");
        while (!check(TokenType::END) && !is_at_end()) {
            else_branch.push_back(parse_statement());
        }
    }
    
    consume(TokenType::END, "Expected 'end' to close if statement");
    consume(TokenType::PERIOD, "Expected '.' after 'end'");
    
    auto node = std::make_shared<IfNode>();
    node->condition = condition;
    node->then_branch = then_branch;
    node->else_branch = else_branch;
    node->line = previous().line;
    
    return node;
}

ASTNode Parser::parse_while_loop() {
    ASTNode condition = parse_expression();
    consume(TokenType::PERIOD, "Expected '.' after condition");
    
    std::vector<ASTNode> body;
    while (!check(TokenType::END) && !is_at_end()) {
        body.push_back(parse_statement());
    }
    
    consume(TokenType::END, "Expected 'end' to close while loop");
    consume(TokenType::PERIOD, "Expected '.' after 'end'");
    
    auto node = std::make_shared<WhileNode>();
    node->condition = condition;
    node->body = body;
    node->line = previous().line;
    
    return node;
}

ASTNode Parser::parse_repeat_loop() {
    ASTNode count = parse_expression();
    consume(TokenType::TIMES, "Expected 'times' after count");
    consume(TokenType::PERIOD, "Expected '.' after 'times'");
    
    std::vector<ASTNode> body;
    while (!check(TokenType::END) && !is_at_end()) {
        body.push_back(parse_statement());
    }
    
    consume(TokenType::END, "Expected 'end' to close repeat loop");
    consume(TokenType::PERIOD, "Expected '.' after 'end'");
    
    auto node = std::make_shared<RepeatNode>();
    node->count = count;
    node->body = body;
    node->line = previous().line;
    
    return node;
}

ASTNode Parser::parse_for_loop() {
    consume(TokenType::FROM, "Expected 'from' in for loop");
    ASTNode start = parse_expression();
    consume(TokenType::TO, "Expected 'to' in for loop");
    ASTNode end = parse_expression();
    consume(TokenType::PERIOD, "Expected '.' after range");
    
    std::vector<ASTNode> body;
    while (!check(TokenType::END) && !is_at_end()) {
        body.push_back(parse_statement());
    }
    
    consume(TokenType::END, "Expected 'end' to close for loop");
    consume(TokenType::PERIOD, "Expected '.' after 'end'");
    
    auto node = std::make_shared<WhileNode>();
    node->body = body;
    node->line = previous().line;
    
    return node;
}

ASTNode Parser::parse_function_def() {
    match(TokenType::A);
    consume(TokenType::FUNCTION, "Expected 'function'");
    consume(TokenType::CALLED, "Expected 'called'");
    
    Token name_token = consume(TokenType::IDENTIFIER, "Expected function name");
    
    std::vector<std::string> params;
    if (match(TokenType::THAT)) {
        consume(TokenType::TAKES, "Expected 'takes' after 'that'");
        
        do {
            Token param = consume(TokenType::IDENTIFIER, "Expected parameter name");
            params.push_back(param.lexeme);
        } while (match(TokenType::COMMA_PUNCT) || match(TokenType::AND));
    }
    
    consume(TokenType::PERIOD, "Expected '.' after function signature");
    
    std::vector<ASTNode> body;
    while (!check(TokenType::END) && !is_at_end()) {
        body.push_back(parse_statement());
    }
    
    consume(TokenType::END, "Expected 'end' to close function");
    consume(TokenType::PERIOD, "Expected '.' after 'end'");
    
    auto node = std::make_shared<FunctionDefNode>();
    node->name = name_token.lexeme;
    node->parameters = params;
    node->body = body;
    node->line = name_token.line;
    
    return node;
}

ASTNode Parser::parse_return() {
    consume(TokenType::BACK, "Expected 'back' after 'give'");
    
    ASTNode value = parse_expression();
    consume(TokenType::PERIOD, "Expected '.' after return value");
    
    auto node = std::make_shared<ReturnNode>();
    node->value = value;
    node->line = previous().line;
    
    return node;
}

ASTNode Parser::parse_expression_statement() {
    ASTNode expr = parse_expression();
    consume(TokenType::PERIOD, "Expected '.' at end of statement");
    return expr;
}

ASTNode Parser::parse_expression() {
    return parse_logical_or();
}

ASTNode Parser::parse_logical_or() {
    ASTNode left = parse_logical_and();
    
    while (match(TokenType::OR)) {
        ASTNode right = parse_logical_and();
        
        auto node = std::make_shared<BinaryOpNode>();
        node->op = BinaryOpNode::Op::OR;
        node->left = left;
        node->right = right;
        node->line = previous().line;
        
        left = node;
    }
    
    return left;
}

ASTNode Parser::parse_logical_and() {
    ASTNode left = parse_equality();
    
    while (match(TokenType::AND)) {
        ASTNode right = parse_equality();
        
        auto node = std::make_shared<BinaryOpNode>();
        node->op = BinaryOpNode::Op::AND;
        node->left = left;
        node->right = right;
        node->line = previous().line;
        
        left = node;
    }
    
    return left;
}

ASTNode Parser::parse_equality() {
    ASTNode left = parse_comparison();
    
    // "is equal to", "is not equal to"
    if (match(TokenType::IS)) {
        if (match(TokenType::NOT)) {
            match(TokenType::EQUAL);
            match(TokenType::TO);
            ASTNode right = parse_comparison();
            
            auto node = std::make_shared<BinaryOpNode>();
            node->op = BinaryOpNode::Op::NOT_EQUAL;
            node->left = left;
            node->right = right;
            node->line = previous().line;
            
            return node;
        } else {
            match(TokenType::EQUAL);
            match(TokenType::TO);
            ASTNode right = parse_comparison();
            
            auto node = std::make_shared<BinaryOpNode>();
            node->op = BinaryOpNode::Op::EQUAL;
            node->left = left;
            node->right = right;
            node->line = previous().line;
            
            return node;
        }
    }
    
    return left;
}

ASTNode Parser::parse_comparison() {
    ASTNode left = parse_addition();
    
    // "is greater than", "is less than"
    if (match(TokenType::IS)) {
        if (match(TokenType::GREATER)) {
            match(TokenType::THAN);
            ASTNode right = parse_addition();
            
            auto node = std::make_shared<BinaryOpNode>();
            node->op = BinaryOpNode::Op::GREATER_THAN;
            node->left = left;
            node->right = right;
            node->line = previous().line;
            
            return node;
        } else if (match(TokenType::LESS)) {
            match(TokenType::THAN);
            ASTNode right = parse_addition();
            
            auto node = std::make_shared<BinaryOpNode>();
            node->op = BinaryOpNode::Op::LESS_THAN;
            node->left = left;
            node->right = right;
            node->line = previous().line;
            
            return node;
        }
    }
    
    return left;
}

ASTNode Parser::parse_addition() {
    ASTNode left = parse_multiplication();
    
    while (match(TokenType::ADD) || match(TokenType::SUBTRACT)) {
        TokenType op_type = previous().type;
        ASTNode right = parse_multiplication();
        
        auto node = std::make_shared<BinaryOpNode>();
        node->op = (op_type == TokenType::ADD) ? BinaryOpNode::Op::ADD : BinaryOpNode::Op::SUBTRACT;
        node->left = left;
        node->right = right;
        node->line = previous().line;
        
        left = node;
    }
    
    return left;
}

ASTNode Parser::parse_multiplication() {
    ASTNode left = parse_unary();
    
    while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
        TokenType op_type = previous().type;
        ASTNode right = parse_unary();
        
        auto node = std::make_shared<BinaryOpNode>();
        node->op = (op_type == TokenType::MULTIPLY) ? BinaryOpNode::Op::MULTIPLY : BinaryOpNode::Op::DIVIDE;
        node->left = left;
        node->right = right;
        node->line = previous().line;
        
        left = node;
    }
    
    return left;
}

ASTNode Parser::parse_unary() {
    if (match(TokenType::NOT)) {
        ASTNode operand = parse_unary();
        
        auto node = std::make_shared<UnaryOpNode>();
        node->op = UnaryOpNode::Op::NOT;
        node->operand = operand;
        node->line = previous().line;
        
        return node;
    }
    
    if (match(TokenType::NEGATIVE)) {
        ASTNode operand = parse_unary();
        
        auto node = std::make_shared<UnaryOpNode>();
        node->op = UnaryOpNode::Op::NEGATE;
        node->operand = operand;
        node->line = previous().line;
        
        return node;
    }
    
    return parse_call();
}

ASTNode Parser::parse_call() {
    // Function call: call func with arg1, arg2.
    if (match(TokenType::CALL)) {
        Token name_token = consume(TokenType::IDENTIFIER, "Expected function name");
        
        std::vector<ASTNode> args;
        if (match(TokenType::WITH)) {
            do {
                args.push_back(parse_primary());
            } while (match(TokenType::COMMA_PUNCT) || match(TokenType::AND));
        }
        
        // Optional: "and store as result"
        if (match(TokenType::AND)) {
            match(TokenType::STORE);
            match(TokenType::AS);
            match(TokenType::IDENTIFIER);
        }
        
        auto node = std::make_shared<FunctionCallNode>();
        node->name = name_token.lexeme;
        node->arguments = args;
        node->line = name_token.line;
        
        return node;
    }
    
    // Say statement: say x.
    if (match(TokenType::SAY) || match(TokenType::PRINT) || match(TokenType::SHOW)) {
        std::vector<ASTNode> args;
        
        do {
            args.push_back(parse_primary());
        } while (match(TokenType::COMMA_PUNCT));
        
        auto node = std::make_shared<FunctionCallNode>();
        node->name = "say";
        node->arguments = args;
        node->line = previous().line;
        
        return node;
    }
    
    return parse_primary();
}

ASTNode Parser::parse_primary() {
    // Literals
    if (match(TokenType::TRUE)) {
        auto node = std::make_shared<LiteralNode>();
        node->type = LiteralNode::Type::BOOLEAN;
        node->value = "true";
        node->line = previous().line;
        return node;
    }
    
    if (match(TokenType::FALSE)) {
        auto node = std::make_shared<LiteralNode>();
        node->type = LiteralNode::Type::BOOLEAN;
        node->value = "false";
        node->line = previous().line;
        return node;
    }
    
    if (match(TokenType::NOTHING)) {
        auto node = std::make_shared<LiteralNode>();
        node->type = LiteralNode::Type::NULL_VALUE;
        node->value = "null";
        node->line = previous().line;
        return node;
    }
    
    if (match(TokenType::INTEGER)) {
        auto node = std::make_shared<LiteralNode>();
        node->type = LiteralNode::Type::INTEGER;
        node->value = previous().lexeme;
        node->line = previous().line;
        return node;
    }
    
    if (match(TokenType::FLOAT)) {
        auto node = std::make_shared<LiteralNode>();
        node->type = LiteralNode::Type::FLOAT;
        node->value = previous().lexeme;
        node->line = previous().line;
        return node;
    }
    
    if (match(TokenType::STRING)) {
        auto node = std::make_shared<LiteralNode>();
        node->type = LiteralNode::Type::STRING;
        node->value = previous().lexeme;
        node->line = previous().line;
        return node;
    }
    
    // Identifier
    if (match(TokenType::IDENTIFIER)) {
        auto node = std::make_shared<IdentifierNode>();
        node->name = previous().lexeme;
        node->line = previous().line;
        return node;
    }
    
    // List literal
    if (match(TokenType::A) || match(TokenType::AN)) {
        if (match(TokenType::LIST)) {
            return parse_list_literal();
        }
    }
    
    Token current = peek();
    throw ParserError("Unexpected token: " + current.lexeme, current.line, current.column);
}

ASTNode Parser::parse_list_literal() {
    consume(TokenType::CONTAINING, "Expected 'containing' in list literal");
    
    std::vector<ASTNode> elements;
    do {
        elements.push_back(parse_primary());
    } while (match(TokenType::COMMA_PUNCT) || match(TokenType::AND));
    
    auto node = std::make_shared<ListNode>();
    node->elements = elements;
    node->line = previous().line;
    
    return node;
}

bool Parser::peek_ahead_for_gui() {
    // Check if this is a GUI set command like "set the title of..."
    size_t saved = current_;
    match(TokenType::SET);
    bool is_gui = match(TokenType::THE) && 
                  (check(TokenType::TITLE) || check(TokenType::WIDTH) || 
                   check(TokenType::HEIGHT) || check(TokenType::BACKGROUND) ||
                   check(TokenType::TEXT) || check(TokenType::PLACEHOLDER));
    current_ = saved;
    return is_gui;
}

ASTNode Parser::parse_gui_command() {
    // create a window/label/button/input called name
    match(TokenType::A);
    
    auto node = std::make_shared<GUINode>();
    node->line = previous().line;
    
    if (match(TokenType::WINDOW)) {
        node->command = GUINode::Command::CREATE_WINDOW;
        consume(TokenType::CALLED, "Expected 'called' after 'window'");
        Token name = consume(TokenType::IDENTIFIER, "Expected window name");
        node->target = name.lexeme;
    }
    else if (match(TokenType::LABEL)) {
        node->command = GUINode::Command::CREATE_LABEL;
        consume(TokenType::CALLED, "Expected 'called' after 'label'");
        Token name = consume(TokenType::IDENTIFIER, "Expected label name");
        node->target = name.lexeme;
    }
    else if (match(TokenType::BUTTON)) {
        node->command = GUINode::Command::CREATE_BUTTON;
        consume(TokenType::CALLED, "Expected 'called' after 'button'");
        Token name = consume(TokenType::IDENTIFIER, "Expected button name");
        node->target = name.lexeme;
    }
    else if (check(TokenType::TEXT)) {
        match(TokenType::TEXT);
        match(TokenType::INPUT);
        node->command = GUINode::Command::CREATE_INPUT;
        consume(TokenType::CALLED, "Expected 'called' after 'input'");
        Token name = consume(TokenType::IDENTIFIER, "Expected input name");
        node->target = name.lexeme;
    }
    
    consume(TokenType::PERIOD, "Expected '.' at end of statement");
    return node;
}

ASTNode Parser::parse_gui_set_command() {
    // set the title/width/height/text/placeholder of widget to value
    consume(TokenType::SET, "Expected 'set'");
    consume(TokenType::THE, "Expected 'the'");
    
    auto node = std::make_shared<GUINode>();
    node->line = previous().line;
    
    if (match(TokenType::TITLE)) {
        node->command = GUINode::Command::SET_TITLE;
    }
    else if (match(TokenType::WIDTH)) {
        node->command = GUINode::Command::SET_WIDTH;
    }
    else if (match(TokenType::HEIGHT)) {
        node->command = GUINode::Command::SET_HEIGHT;
    }
    else if (match(TokenType::BACKGROUND)) {
        node->command = GUINode::Command::SET_BACKGROUND;
    }
    else if (match(TokenType::TEXT)) {
        node->command = GUINode::Command::SET_TEXT;
    }
    else if (match(TokenType::PLACEHOLDER)) {
        node->command = GUINode::Command::SET_PLACEHOLDER;
    }
    
    consume(TokenType::OF, "Expected 'of'");
    Token target = consume(TokenType::IDENTIFIER, "Expected widget name");
    node->target = target.lexeme;
    
    consume(TokenType::TO, "Expected 'to'");
    node->arguments.push_back(parse_expression());
    
    consume(TokenType::PERIOD, "Expected '.' at end of statement");
    return node;
}

ASTNode Parser::parse_gui_show() {
    // show window_name
    Token name = consume(TokenType::IDENTIFIER, "Expected window name");
    
    auto node = std::make_shared<GUINode>();
    node->command = GUINode::Command::SHOW_WINDOW;
    node->target = name.lexeme;
    node->line = previous().line;
    
    consume(TokenType::PERIOD, "Expected '.' at end of statement");
    return node;
}

ASTNode Parser::parse_gui_place() {
    // place widget at row X and column Y in window
    Token widget = consume(TokenType::IDENTIFIER, "Expected widget name");
    
    auto node = std::make_shared<GUINode>();
    node->command = GUINode::Command::PLACE_WIDGET;
    node->target = widget.lexeme;
    node->line = previous().line;
    
    consume(TokenType::AT, "Expected 'at'");
    consume(TokenType::ROW, "Expected 'row'");
    node->arguments.push_back(parse_primary());
    
    consume(TokenType::AND, "Expected 'and'");
    consume(TokenType::COLUMN, "Expected 'column'");
    node->arguments.push_back(parse_primary());
    
    consume(TokenType::IN, "Expected 'in'");
    Token window = consume(TokenType::IDENTIFIER, "Expected window name");
    
    auto window_lit = std::make_shared<LiteralNode>();
    window_lit->type = LiteralNode::Type::STRING;
    window_lit->value = window.lexeme;
    window_lit->line = window.line;
    node->arguments.push_back(window_lit);
    
    consume(TokenType::PERIOD, "Expected '.' at end of statement");
    return node;
}

} // namespace kaynat
