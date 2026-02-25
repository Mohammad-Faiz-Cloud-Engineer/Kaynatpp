/**
 * @file environment.cpp
 * @brief Environment implementation
 */

#include "environment.hpp"
#include "../errors/error_types.hpp"

namespace kaynat {

Environment::Environment(std::shared_ptr<Environment> parent)
    : parent_(parent) {}

void Environment::define(const std::string& name, const KaynatValue& value, bool is_constant) {
    if (variables_.find(name) != variables_.end()) {
        throw RuntimeError("Variable '" + name + "' already defined in this scope", 0, 0);
    }
    
    variables_[name] = value;
    if (is_constant) {
        constants_[name] = true;
    }
}

KaynatValue Environment::get(const std::string& name) const {
    const Environment* env = find_environment(name);
    if (env == nullptr) {
        throw UndefinedError(name, 0, 0);
    }
    
    return env->variables_.at(name);
}

void Environment::set(const std::string& name, const KaynatValue& value) {
    Environment* env = find_environment(name);
    if (env == nullptr) {
        throw UndefinedError(name, 0, 0);
    }
    
    if (env->is_constant(name)) {
        throw RuntimeError("Cannot modify constant '" + name + "'", 0, 0);
    }
    
    env->variables_[name] = value;
}

bool Environment::exists(const std::string& name) const {
    return find_environment(name) != nullptr;
}

void Environment::remove(const std::string& name) {
    auto it = variables_.find(name);
    if (it == variables_.end()) {
        throw UndefinedError(name, 0, 0);
    }
    
    variables_.erase(it);
    constants_.erase(name);
}

bool Environment::is_constant(const std::string& name) const {
    auto it = constants_.find(name);
    return it != constants_.end() && it->second;
}

std::shared_ptr<Environment> Environment::create_child() {
    return std::make_shared<Environment>(shared_from_this());
}

Environment* Environment::find_environment(const std::string& name) {
    if (variables_.find(name) != variables_.end()) {
        return this;
    }
    
    if (parent_ != nullptr) {
        return parent_->find_environment(name);
    }
    
    return nullptr;
}

const Environment* Environment::find_environment(const std::string& name) const {
    if (variables_.find(name) != variables_.end()) {
        return this;
    }
    
    if (parent_ != nullptr) {
        return parent_->find_environment(name);
    }
    
    return nullptr;
}

} // namespace kaynat
