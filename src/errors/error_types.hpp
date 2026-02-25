/**
 * @file error_types.hpp
 * @brief Error type definitions for Kaynat++
 * 
 * Defines all error types that can occur during compilation and runtime.
 */

#pragma once

#include <string>
#include <stdexcept>
#include <cstdint>

namespace kaynat {

/**
 * @brief Base class for all Kaynat++ errors
 */
class KaynatError : public std::runtime_error {
public:
    KaynatError(const std::string& message, uint32_t line, uint32_t column)
        : std::runtime_error(message), line_(line), column_(column) {}
    
    uint32_t line() const { return line_; }
    uint32_t column() const { return column_; }
    
    virtual std::string formatted_message() const;
    
protected:
    uint32_t line_;
    uint32_t column_;
};

/**
 * @brief Lexical analysis error
 */
class LexerError : public KaynatError {
public:
    using KaynatError::KaynatError;
    std::string formatted_message() const override;
};

/**
 * @brief Syntax parsing error
 */
class ParserError : public KaynatError {
public:
    using KaynatError::KaynatError;
    std::string formatted_message() const override;
};

/**
 * @brief Runtime execution error
 */
class RuntimeError : public KaynatError {
public:
    using KaynatError::KaynatError;
    std::string formatted_message() const override;
};

/**
 * @brief Type mismatch error
 */
class TypeError : public RuntimeError {
public:
    TypeError(const std::string& expected, const std::string& got, 
              uint32_t line, uint32_t column);
    std::string formatted_message() const override;
    
private:
    std::string expected_;
    std::string got_;
};

/**
 * @brief Undefined variable error
 */
class UndefinedError : public RuntimeError {
public:
    UndefinedError(const std::string& name, uint32_t line, uint32_t column);
    std::string formatted_message() const override;
    
private:
    std::string name_;
};

/**
 * @brief Division by zero error
 */
class DivisionByZeroError : public RuntimeError {
public:
    DivisionByZeroError(uint32_t line, uint32_t column);
    std::string formatted_message() const override;
};

/**
 * @brief Index out of bounds error
 */
class IndexError : public RuntimeError {
public:
    IndexError(int64_t index, size_t size, uint32_t line, uint32_t column);
    std::string formatted_message() const override;
    
private:
    int64_t index_;
    size_t size_;
};

/**
 * @brief File I/O error
 */
class FileError : public RuntimeError {
public:
    FileError(const std::string& filename, const std::string& reason,
              uint32_t line, uint32_t column);
    std::string formatted_message() const override;
    
private:
    std::string filename_;
    std::string reason_;
};

} // namespace kaynat
