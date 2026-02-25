/**
 * @file messages.cpp
 * @brief Error message formatting implementation
 */

#include "error_types.hpp"
#include <sstream>

namespace kaynat {

std::string KaynatError::formatted_message() const {
    std::ostringstream oss;
    oss << "Error at line " << line_ << ", column " << column_ << ": " << what();
    return oss.str();
}

std::string LexerError::formatted_message() const {
    std::ostringstream oss;
    oss << "Lexer error at line " << line_ << ", column " << column_ << ": " << what();
    return oss.str();
}

std::string ParserError::formatted_message() const {
    std::ostringstream oss;
    oss << "Parser error at line " << line_ << ", column " << column_ << ": " << what();
    return oss.str();
}

std::string RuntimeError::formatted_message() const {
    std::ostringstream oss;
    oss << "Runtime error at line " << line_ << ", column " << column_ << ": " << what();
    return oss.str();
}

TypeError::TypeError(const std::string& expected, const std::string& got,
                     uint32_t line, uint32_t column)
    : RuntimeError("Type mismatch: expected " + expected + ", got " + got, line, column),
      expected_(expected), got_(got) {}

std::string TypeError::formatted_message() const {
    std::ostringstream oss;
    oss << "Type error at line " << line_ << ", column " << column_ 
        << ": expected " << expected_ << ", but got " << got_;
    return oss.str();
}

UndefinedError::UndefinedError(const std::string& name, uint32_t line, uint32_t column)
    : RuntimeError("Undefined variable '" + name + "'", line, column),
      name_(name) {}

std::string UndefinedError::formatted_message() const {
    std::ostringstream oss;
    oss << "Undefined variable at line " << line_ << ", column " << column_ 
        << ": '" << name_ << "' has not been defined";
    return oss.str();
}

DivisionByZeroError::DivisionByZeroError(uint32_t line, uint32_t column)
    : RuntimeError("Division by zero", line, column) {}

std::string DivisionByZeroError::formatted_message() const {
    std::ostringstream oss;
    oss << "Division by zero at line " << line_ << ", column " << column_;
    return oss.str();
}

IndexError::IndexError(int64_t index, size_t size, uint32_t line, uint32_t column)
    : RuntimeError("Index out of bounds", line, column),
      index_(index), size_(size) {}

std::string IndexError::formatted_message() const {
    std::ostringstream oss;
    oss << "Index error at line " << line_ << ", column " << column_ 
        << ": index " << index_ << " is out of bounds for size " << size_;
    return oss.str();
}

FileError::FileError(const std::string& filename, const std::string& reason,
                     uint32_t line, uint32_t column)
    : RuntimeError("File error: " + reason, line, column),
      filename_(filename), reason_(reason) {}

std::string FileError::formatted_message() const {
    std::ostringstream oss;
    oss << "File error at line " << line_ << ", column " << column_ 
        << ": cannot access '" << filename_ << "' - " << reason_;
    return oss.str();
}

} // namespace kaynat
