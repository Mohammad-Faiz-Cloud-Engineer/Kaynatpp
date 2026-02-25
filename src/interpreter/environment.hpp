/**
 * @file environment.hpp
 * @brief Variable scope management for Kaynat++ interpreter
 * 
 * Manages variable storage with lexical scoping and constant enforcement.
 */

#pragma once

#include "runtime_value.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <optional>

namespace kaynat {

/**
 * @brief Environment for variable storage with lexical scoping
 * 
 * Manages variables in a scope chain. Each environment has an optional
 * parent environment for nested scopes. Supports:
 * - Variable definition and lookup
 * - Constant enforcement
 * - Scope chaining
 * - Variable shadowing
 * 
 * Thread-safe: No. Each interpreter instance should have its own environment.
 */
class Environment : public std::enable_shared_from_this<Environment> {
public:
    /**
     * @brief Create a new environment
     * @param parent Optional parent environment for scope chaining
     */
    explicit Environment(std::shared_ptr<Environment> parent = nullptr);
    
    /**
     * @brief Define a new variable in this scope
     * @param name Variable name
     * @param value Initial value
     * @param is_constant Whether variable is constant
     * @throws RuntimeError if variable already exists in this scope
     */
    void define(const std::string& name, const KaynatValue& value, bool is_constant = false);
    
    /**
     * @brief Get variable value
     * @param name Variable name
     * @return Value if found
     * @throws UndefinedError if variable not found in any scope
     */
    KaynatValue get(const std::string& name) const;
    
    /**
     * @brief Set variable value
     * @param name Variable name
     * @param value New value
     * @throws UndefinedError if variable not found
     * @throws RuntimeError if trying to modify constant
     */
    void set(const std::string& name, const KaynatValue& value);
    
    /**
     * @brief Check if variable exists in any scope
     * @param name Variable name
     * @return true if variable exists
     */
    bool exists(const std::string& name) const;
    
    /**
     * @brief Remove variable from this scope
     * @param name Variable name
     * @throws UndefinedError if variable not found in this scope
     */
    void remove(const std::string& name);
    
    /**
     * @brief Check if variable is constant
     * @param name Variable name
     * @return true if variable is constant
     */
    bool is_constant(const std::string& name) const;
    
    /**
     * @brief Get parent environment
     */
    std::shared_ptr<Environment> parent() const { return parent_; }
    
    /**
     * @brief Create a new child environment
     */
    std::shared_ptr<Environment> create_child();
    
private:
    std::shared_ptr<Environment> parent_;
    std::unordered_map<std::string, KaynatValue> variables_;
    std::unordered_map<std::string, bool> constants_;
    
    /**
     * @brief Find environment containing variable
     * @return Environment pointer or nullptr if not found
     */
    Environment* find_environment(const std::string& name);
    const Environment* find_environment(const std::string& name) const;
};

} // namespace kaynat
