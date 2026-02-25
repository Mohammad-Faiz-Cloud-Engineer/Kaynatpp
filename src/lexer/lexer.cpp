/**
 * @file lexer.cpp
 * @brief Lexer implementation for Kaynat++
 */

#include "lexer.hpp"
#include "../errors/error_types.hpp"
#include <cctype>
#include <sstream>

namespace kaynat {

// Initialize keyword map
const std::unordered_map<std::string, TokenType> Lexer::keywords_ = {
    // Program structure
    {"begin", TokenType::BEGIN},
    {"program", TokenType::PROGRAM},
    {"end", TokenType::END},
    {"note", TokenType::NOTE},
    
    // Variables
    {"set", TokenType::SET},
    {"let", TokenType::LET},
    {"define", TokenType::DEFINE},
    {"always", TokenType::ALWAYS},
    {"change", TokenType::CHANGE},
    {"forget", TokenType::FORGET},
    {"check", TokenType::CHECK},
    {"exists", TokenType::EXISTS},
    
    // Arithmetic
    {"add", TokenType::ADD},
    {"subtract", TokenType::SUBTRACT},
    {"multiply", TokenType::MULTIPLY},
    {"divide", TokenType::DIVIDE},
    {"find", TokenType::FIND},
    {"raise", TokenType::RAISE},
    {"power", TokenType::POWER},
    {"square", TokenType::SQUARE},
    {"root", TokenType::ROOT},
    {"absolute", TokenType::ABSOLUTE},
    {"value", TokenType::VALUE},
    {"round", TokenType::ROUND},
    {"ceiling", TokenType::CEILING},
    {"floor", TokenType::FLOOR},
    {"logarithm", TokenType::LOGARITHM},
    {"sine", TokenType::SINE},
    {"cosine", TokenType::COSINE},
    {"tangent", TokenType::TANGENT},
    {"product", TokenType::PRODUCT},
    {"remainder", TokenType::REMAINDER},
    
    // String operations
    {"join", TokenType::JOIN},
    {"length", TokenType::LENGTH},
    {"uppercase", TokenType::UPPERCASE},
    {"lowercase", TokenType::LOWERCASE},
    {"trim", TokenType::TRIM},
    {"whitespace", TokenType::WHITESPACE},
    {"starts", TokenType::STARTS},
    {"ends", TokenType::ENDS},
    {"replace", TokenType::REPLACE},
    {"split", TokenType::SPLIT},
    {"position", TokenType::POSITION},
    {"take", TokenType::TAKE},
    {"characters", TokenType::CHARACTERS},
    {"reverse", TokenType::REVERSE},
    {"repeat", TokenType::REPEAT},
    {"contains", TokenType::CONTAINS},
    
    // Comparison
    {"is", TokenType::IS},
    {"equal", TokenType::EQUAL},
    {"not", TokenType::NOT},
    {"greater", TokenType::GREATER},
    {"less", TokenType::LESS},
    {"than", TokenType::THAN},
    {"or", TokenType::OR},
    {"and", TokenType::AND},
    {"empty", TokenType::EMPTY},
    
    // Types
    {"number", TokenType::NUMBER},
    {"text", TokenType::TEXT},
    {"list", TokenType::LIST},
    {"map", TokenType::MAP},
    {"big", TokenType::BIG},
    {"type", TokenType::TYPE},
    {"convert", TokenType::CONVERT},
    {"turn", TokenType::TURN},
    {"into", TokenType::INTO},
    
    // Control flow
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"otherwise", TokenType::OTHERWISE},
    {"when", TokenType::WHEN},
    {"do", TokenType::DO},
    {"by", TokenType::BY},
    {"default", TokenType::DEFAULT},
    
    // Loops
    {"repeat", TokenType::REPEAT},
    {"times", TokenType::TIMES},
    {"while", TokenType::WHILE},
    {"until", TokenType::UNTIL},
    {"for", TokenType::FOR},
    {"each", TokenType::EACH},
    {"in", TokenType::IN},
    {"loop", TokenType::LOOP},
    {"from", TokenType::FROM},
    {"to", TokenType::TO},
    {"stepping", TokenType::STEPPING},
    {"stop", TokenType::STOP},
    {"skip", TokenType::SKIP},
    
    // Functions
    {"function", TokenType::FUNCTION},
    {"called", TokenType::CALLED},
    {"that", TokenType::THAT},
    {"takes", TokenType::TAKES},
    {"give", TokenType::GIVE},
    {"back", TokenType::BACK},
    {"call", TokenType::CALL},
    {"with", TokenType::WITH},
    {"inline", TokenType::INLINE},
    {"gives", TokenType::GIVES},
    
    // Collections
    {"containing", TokenType::CONTAINING},
    {"create", TokenType::CREATE},
    {"insert", TokenType::INSERT},
    {"at", TokenType::AT},
    {"remove", TokenType::REMOVE},
    {"get", TokenType::GET},
    {"item", TokenType::ITEM},
    {"sort", TokenType::SORT},
    {"ascending", TokenType::ASCENDING},
    {"descending", TokenType::DESCENDING},
    {"filter", TokenType::FILTER},
    {"where", TokenType::WHERE},
    {"reduce", TokenType::REDUCE},
    {"using", TokenType::USING},
    {"copy", TokenType::COPY},
    {"flatten", TokenType::FLATTEN},
    {"key", TokenType::KEY},
    
    // I/O
    {"ask", TokenType::ASK},
    {"user", TokenType::USER},
    {"read", TokenType::READ},
    {"say", TokenType::SAY},
    {"print", TokenType::PRINT},
    {"show", TokenType::SHOW},
    
    // File operations
    {"file", TokenType::FILE},
    {"line", TokenType::LINE},
    {"write", TokenType::WRITE},
    {"append", TokenType::APPEND},
    {"delete", TokenType::DELETE},
    
    // Error handling
    {"attempt", TokenType::ATTEMPT},
    {"it", TokenType::IT},
    {"fails", TokenType::FAILS},
    {"message", TokenType::MESSAGE},
    {"after", TokenType::AFTER},
    {"error", TokenType::ERROR},
    {"saying", TokenType::SAYING},
    
    // Scope
    {"global", TokenType::GLOBAL},
    {"bring", TokenType::BRING},
    {"use", TokenType::USE},
    {"module", TokenType::MODULE},
    {"named", TokenType::NAMED},
    {"export", TokenType::EXPORT},
    
    // Literals
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"nothing", TokenType::NOTHING},
    {"negative", TokenType::NEGATIVE},
    
    // Common words
    {"as", TokenType::AS},
    {"the", TokenType::THE},
    {"a", TokenType::A},
    {"an", TokenType::AN},
    {"of", TokenType::OF},
    {"store", TokenType::STORE},
    {"current", TokenType::CURRENT},
    {"result", TokenType::RESULT},
    {"decimal", TokenType::DECIMAL},
    {"places", TokenType::PLACES},
    {"base", TokenType::BASE},
    {"my", TokenType::MY},
    
    // OOP
    {"blueprint", TokenType::BLUEPRINT},
    {"has", TokenType::HAS},
    {"initialize", TokenType::INITIALIZE},
    {"new", TokenType::NEW},
    {"on", TokenType::ON},
    {"extends", TokenType::EXTENDS},
    {"parent", TokenType::PARENT},
    {"abstract", TokenType::ABSTRACT},
    {"this", TokenType::THIS},
    {"must", TokenType::MUST},
    {"be", TokenType::BE},
    {"implemented", TokenType::IMPLEMENTED},
    {"contract", TokenType::CONTRACT},
    {"requires", TokenType::REQUIRES},
    {"private", TokenType::PRIVATE},
    
    // GUI keywords
    {"window", TokenType::WINDOW},
    {"title", TokenType::TITLE},
    {"width", TokenType::WIDTH},
    {"height", TokenType::HEIGHT},
    {"background", TokenType::BACKGROUND},
    {"label", TokenType::LABEL},
    {"button", TokenType::BUTTON},
    {"input", TokenType::INPUT},
    {"placeholder", TokenType::PLACEHOLDER},
    {"place", TokenType::PLACE},
    {"row", TokenType::ROW},
    {"column", TokenType::COLUMN},
};

Lexer::Lexer(std::string source)
    : source_(std::move(source)), position_(0), line_(1), column_(1) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    tokens.reserve(source_.length() / 4);
    
    while (!is_at_end()) {
        skip_whitespace();
        if (is_at_end()) break;
        
        Token token = next_token();
        if (token.type != TokenType::INVALID) {
            tokens.push_back(token);
        }
    }
    
    tokens.push_back(make_token(TokenType::END_OF_FILE, ""));
    return tokens;
}

Token Lexer::next_token() {
    const char c = peek();
    
    // Period
    if (c == '.') {
        advance();
        return make_token(TokenType::PERIOD, ".");
    }
    
    // Comma
    if (c == ',') {
        advance();
        return make_token(TokenType::COMMA_PUNCT, ",");
    }
    
    // String literals
    if (c == '"') {
        return tokenize_string();
    }
    
    // Numbers
    if (std::isdigit(c)) {
        return tokenize_number();
    }
    
    // Identifiers and keywords
    if (is_identifier_start(c)) {
        return tokenize_identifier();
    }
    
    // Invalid character
    advance();
    return make_error_token(std::string("Unexpected character '") + c + "'");
}

char Lexer::peek() const {
    if (is_at_end()) return '\0';
    return source_[position_];
}

char Lexer::peek_ahead(size_t n) const {
    if (position_ + n >= source_.length()) return '\0';
    return source_[position_ + n];
}

char Lexer::advance() {
    if (is_at_end()) return '\0';
    
    const char c = source_[position_++];
    
    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }
    
    return c;
}

bool Lexer::is_at_end() const {
    return position_ >= source_.length();
}

void Lexer::skip_whitespace() {
    while (!is_at_end()) {
        const char c = peek();
        
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
        } else {
            break;
        }
    }
}

Token Lexer::tokenize_number() {
    const uint32_t start_line = line_;
    const uint32_t start_column = column_;
    std::string num_str;
    
    while (!is_at_end() && std::isdigit(peek())) {
        num_str += advance();
    }
    
    // Check for decimal point
    if (!is_at_end() && peek() == '.' && std::isdigit(peek_ahead(1))) {
        num_str += advance(); // consume '.'
        
        while (!is_at_end() && std::isdigit(peek())) {
            num_str += advance();
        }
        
        return Token(TokenType::FLOAT, num_str, start_line, start_column);
    }
    
    return Token(TokenType::INTEGER, num_str, start_line, start_column);
}

Token Lexer::tokenize_string() {
    const uint32_t start_line = line_;
    const uint32_t start_column = column_;
    std::string str_value;
    
    advance(); // consume opening quote
    
    while (!is_at_end() && peek() != '"') {
        if (peek() == '\\') {
            advance(); // consume backslash
            if (is_at_end()) {
                return make_error_token("Unterminated string literal");
            }
            
            const char escaped = advance();
            switch (escaped) {
                case 'n': str_value += '\n'; break;
                case 't': str_value += '\t'; break;
                case 'r': str_value += '\r'; break;
                case '\\': str_value += '\\'; break;
                case '"': str_value += '"'; break;
                default:
                    str_value += '\\';
                    str_value += escaped;
            }
        } else {
            str_value += advance();
        }
    }
    
    if (is_at_end()) {
        return make_error_token("Unterminated string literal");
    }
    
    advance(); // consume closing quote
    return Token(TokenType::STRING, str_value, start_line, start_column);
}

Token Lexer::tokenize_identifier() {
    const uint32_t start_line = line_;
    const uint32_t start_column = column_;
    std::string id_str;
    
    while (!is_at_end() && is_identifier_continue(peek())) {
        id_str += advance();
    }
    
    // Check if it's a keyword
    auto it = keywords_.find(id_str);
    if (it != keywords_.end()) {
        return Token(it->second, id_str, start_line, start_column);
    }
    
    // It's an identifier
    return Token(TokenType::IDENTIFIER, id_str, start_line, start_column);
}

bool Lexer::is_identifier_start(char c) {
    return std::isalpha(c) || c == '_';
}

bool Lexer::is_identifier_continue(char c) {
    return std::isalnum(c) || c == '_';
}

Token Lexer::make_token(TokenType type, std::string lexeme) {
    return Token(type, std::move(lexeme), line_, column_);
}

Token Lexer::make_error_token(std::string message) {
    throw LexerError(std::move(message), line_, column_);
}

} // namespace kaynat
