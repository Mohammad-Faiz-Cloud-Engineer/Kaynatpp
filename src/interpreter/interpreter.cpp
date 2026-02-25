/**
 * @file interpreter.cpp
 * @brief Interpreter implementation for Kaynat++
 */

#include "interpreter.hpp"
#include "../errors/error_types.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace kaynat {

Interpreter::Interpreter()
    : global_env_(std::make_shared<Environment>()),
      current_env_(global_env_),
      return_flag_(false) {
    register_builtin_functions();
    register_stdlib_functions();
}

KaynatValue Interpreter::execute(const std::shared_ptr<ProgramNode>& program) {
    return eval_program(program);
}

KaynatValue Interpreter::evaluate(const ASTNode& node) {
    return std::visit([this](auto&& arg) -> KaynatValue {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, std::monostate>) {
            return KaynatValue();
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<ProgramNode>>) {
            return eval_program(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<LiteralNode>>) {
            return eval_literal(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<IdentifierNode>>) {
            return eval_identifier(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<BinaryOpNode>>) {
            return eval_binary_op(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<UnaryOpNode>>) {
            return eval_unary_op(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<AssignmentNode>>) {
            return eval_assignment(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<IfNode>>) {
            return eval_if(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<WhileNode>>) {
            return eval_while(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<ForEachNode>>) {
            return eval_for_each(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<FunctionDefNode>>) {
            return eval_function_def(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<FunctionCallNode>>) {
            return eval_function_call(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<ReturnNode>>) {
            return eval_return(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<ListNode>>) {
            return eval_list(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<DictNode>>) {
            return eval_dict(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<IndexNode>>) {
            return eval_index(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<PropertyAccessNode>>) {
            return eval_property_access(arg);
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<BlockNode>>) {
            return eval_block(arg);
        }
        
        return KaynatValue();
    }, node);
}

KaynatValue Interpreter::eval_program(const std::shared_ptr<ProgramNode>& node) {
    KaynatValue last_value;
    
    for (const auto& stmt : node->statements) {
        if (return_flag_) break;
        last_value = evaluate(stmt);
    }
    
    return last_value;
}

KaynatValue Interpreter::eval_literal(const std::shared_ptr<LiteralNode>& node) {
    switch (node->type) {
        case LiteralNode::Type::INTEGER:
            return KaynatValue(std::stoll(node->value));
        
        case LiteralNode::Type::FLOAT:
            return KaynatValue(std::stod(node->value));
        
        case LiteralNode::Type::STRING:
            return KaynatValue(node->value);
        
        case LiteralNode::Type::BOOLEAN:
            return KaynatValue(node->value == "true");
        
        case LiteralNode::Type::NULL_VALUE:
            return KaynatValue();
    }
    
    return KaynatValue();
}

KaynatValue Interpreter::eval_identifier(const std::shared_ptr<IdentifierNode>& node) {
    return current_env_->get(node->name);
}

KaynatValue Interpreter::eval_binary_op(const std::shared_ptr<BinaryOpNode>& node) {
    KaynatValue left = evaluate(node->left);
    KaynatValue right = evaluate(node->right);
    
    switch (node->op) {
        case BinaryOpNode::Op::ADD: {
            auto l_int = left.as_int();
            auto r_int = right.as_int();
            if (l_int && r_int) {
                return KaynatValue(*l_int + *r_int);
            }
            
            // Handle mixed int/float
            double l_val = l_int ? static_cast<double>(*l_int) : (left.as_float() ? *left.as_float() : 0.0);
            double r_val = r_int ? static_cast<double>(*r_int) : (right.as_float() ? *right.as_float() : 0.0);
            
            if (left.as_float() || right.as_float()) {
                return KaynatValue(l_val + r_val);
            }
            
            // String concatenation
            return KaynatValue(left.to_string() + right.to_string());
        }
        
        case BinaryOpNode::Op::SUBTRACT: {
            auto l_int = left.as_int();
            auto r_int = right.as_int();
            if (l_int && r_int) {
                return KaynatValue(*l_int - *r_int);
            }
            
            // Handle mixed int/float
            double l_val = l_int ? static_cast<double>(*l_int) : (left.as_float() ? *left.as_float() : 0.0);
            double r_val = r_int ? static_cast<double>(*r_int) : (right.as_float() ? *right.as_float() : 0.0);
            
            if (left.as_float() || right.as_float()) {
                return KaynatValue(l_val - r_val);
            }
            
            throw TypeError("Number", left.type_name(), node->line, 0);
        }
        
        case BinaryOpNode::Op::MULTIPLY: {
            auto l_int = left.as_int();
            auto r_int = right.as_int();
            if (l_int && r_int) {
                return KaynatValue(*l_int * *r_int);
            }
            
            // Handle mixed int/float
            double l_val = l_int ? static_cast<double>(*l_int) : (left.as_float() ? *left.as_float() : 0.0);
            double r_val = r_int ? static_cast<double>(*r_int) : (right.as_float() ? *right.as_float() : 0.0);
            
            if (left.as_float() || right.as_float()) {
                return KaynatValue(l_val * r_val);
            }
            
            throw TypeError("Number", left.type_name(), node->line, 0);
        }
        
        case BinaryOpNode::Op::DIVIDE: {
            auto l_int = left.as_int();
            auto r_int = right.as_int();
            
            // Always return float for division
            double l_val = l_int ? static_cast<double>(*l_int) : (left.as_float() ? *left.as_float() : 0.0);
            double r_val = r_int ? static_cast<double>(*r_int) : (right.as_float() ? *right.as_float() : 0.0);
            
            if (l_int || left.as_float()) {
                if (r_val == 0.0) {
                    throw DivisionByZeroError(node->line, 0);
                }
                return KaynatValue(l_val / r_val);
            }
            
            throw TypeError("Number", left.type_name(), node->line, 0);
        }
        
        case BinaryOpNode::Op::MODULO: {
            auto l_int = left.as_int();
            auto r_int = right.as_int();
            if (l_int && r_int) {
                if (*r_int == 0) {
                    throw DivisionByZeroError(node->line, 0);
                }
                return KaynatValue(*l_int % *r_int);
            }
            
            throw TypeError("Integer", left.type_name(), node->line, 0);
        }
        
        case BinaryOpNode::Op::EQUAL:
            return KaynatValue(left == right);
        
        case BinaryOpNode::Op::NOT_EQUAL:
            return KaynatValue(left != right);
        
        case BinaryOpNode::Op::LESS_THAN:
            return KaynatValue(left < right);
        
        case BinaryOpNode::Op::LESS_EQUAL:
            return KaynatValue(left <= right);
        
        case BinaryOpNode::Op::GREATER_THAN:
            return KaynatValue(left > right);
        
        case BinaryOpNode::Op::GREATER_EQUAL:
            return KaynatValue(left >= right);
        
        case BinaryOpNode::Op::AND:
            return KaynatValue(left.is_truthy() && right.is_truthy());
        
        case BinaryOpNode::Op::OR:
            return KaynatValue(left.is_truthy() || right.is_truthy());
    }
    
    return KaynatValue();
}

KaynatValue Interpreter::eval_unary_op(const std::shared_ptr<UnaryOpNode>& node) {
    KaynatValue operand = evaluate(node->operand);
    
    switch (node->op) {
        case UnaryOpNode::Op::NEGATE: {
            auto int_val = operand.as_int();
            if (int_val) {
                return KaynatValue(-*int_val);
            }
            
            auto float_val = operand.as_float();
            if (float_val) {
                return KaynatValue(-*float_val);
            }
            
            throw TypeError("Number", operand.type_name(), node->line, 0);
        }
        
        case UnaryOpNode::Op::NOT:
            return KaynatValue(!operand.is_truthy());
    }
    
    return KaynatValue();
}

KaynatValue Interpreter::eval_assignment(const std::shared_ptr<AssignmentNode>& node) {
    KaynatValue value = evaluate(node->value);
    
    if (current_env_->exists(node->name)) {
        current_env_->set(node->name, value);
    } else {
        current_env_->define(node->name, value, node->is_constant);
    }
    
    return value;
}

KaynatValue Interpreter::eval_if(const std::shared_ptr<IfNode>& node) {
    KaynatValue condition = evaluate(node->condition);
    
    if (condition.is_truthy()) {
        KaynatValue last_value;
        for (const auto& stmt : node->then_branch) {
            if (return_flag_) break;
            last_value = evaluate(stmt);
        }
        return last_value;
    } else if (!node->else_branch.empty()) {
        KaynatValue last_value;
        for (const auto& stmt : node->else_branch) {
            if (return_flag_) break;
            last_value = evaluate(stmt);
        }
        return last_value;
    }
    
    return KaynatValue();
}

KaynatValue Interpreter::eval_while(const std::shared_ptr<WhileNode>& node) {
    KaynatValue last_value;
    
    while (evaluate(node->condition).is_truthy()) {
        for (const auto& stmt : node->body) {
            if (return_flag_) break;
            last_value = evaluate(stmt);
        }
        if (return_flag_) break;
    }
    
    return last_value;
}

KaynatValue Interpreter::eval_for_each(const std::shared_ptr<ForEachNode>& node) {
    KaynatValue iterable = evaluate(node->iterable);
    auto list = iterable.as_list();
    
    if (!list) {
        throw TypeError("List", iterable.type_name(), node->line, 0);
    }
    
    KaynatValue last_value;
    auto loop_env = current_env_->create_child();
    auto prev_env = current_env_;
    current_env_ = loop_env;
    
    for (const auto& item : *list) {
        loop_env->define(node->variable, item);
        
        for (const auto& stmt : node->body) {
            if (return_flag_) break;
            last_value = evaluate(stmt);
        }
        if (return_flag_) break;
    }
    
    current_env_ = prev_env;
    return last_value;
}

KaynatValue Interpreter::eval_function_def(const std::shared_ptr<FunctionDefNode>& node) {
    // Capture the function definition
    auto func_node = node;
    auto closure_env = current_env_;
    
    CallableType callable = [this, func_node, closure_env](std::vector<KaynatValue> args) -> KaynatValue {
        if (args.size() != func_node->parameters.size()) {
            throw RuntimeError("Function expects " + std::to_string(func_node->parameters.size()) +
                             " arguments, got " + std::to_string(args.size()), func_node->line, 0);
        }
        
        // Create new environment for function execution
        auto func_env = closure_env->create_child();
        
        // Bind parameters
        for (size_t i = 0; i < args.size(); ++i) {
            func_env->define(func_node->parameters[i], args[i]);
        }
        
        // Execute function body
        auto prev_env = current_env_;
        current_env_ = func_env;
        
        KaynatValue result;
        for (const auto& stmt : func_node->body) {
            if (return_flag_) {
                result = return_value_;
                return_flag_ = false;
                break;
            }
            result = evaluate(stmt);
        }
        
        current_env_ = prev_env;
        return result;
    };
    
    current_env_->define(node->name, KaynatValue(callable));
    return KaynatValue();
}

KaynatValue Interpreter::eval_function_call(const std::shared_ptr<FunctionCallNode>& node) {
    // Special handling for "say" function
    if (node->name == "say") {
        for (const auto& arg_node : node->arguments) {
            KaynatValue arg = evaluate(arg_node);
            std::cout << arg.to_string();
            if (&arg_node != &node->arguments.back()) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
        return KaynatValue();
    }
    
    // Get function
    KaynatValue func_value = current_env_->get(node->name);
    auto callable = func_value.as_callable();
    
    if (!callable) {
        throw TypeError("Function", func_value.type_name(), node->line, 0);
    }
    
    // Evaluate arguments
    std::vector<KaynatValue> args;
    for (const auto& arg_node : node->arguments) {
        args.push_back(evaluate(arg_node));
    }
    
    // Call function
    return (*callable)(args);
}

KaynatValue Interpreter::eval_return(const std::shared_ptr<ReturnNode>& node) {
    return_value_ = evaluate(node->value);
    return_flag_ = true;
    return return_value_;
}

KaynatValue Interpreter::eval_list(const std::shared_ptr<ListNode>& node) {
    ListType elements;
    for (const auto& elem_node : node->elements) {
        elements.push_back(evaluate(elem_node));
    }
    return KaynatValue(elements);
}

KaynatValue Interpreter::eval_dict(const std::shared_ptr<DictNode>& node) {
    DictType dict;
    for (const auto& [key, value_node] : node->entries) {
        dict[key] = evaluate(value_node);
    }
    return KaynatValue(dict);
}

KaynatValue Interpreter::eval_index(const std::shared_ptr<IndexNode>& node) {
    KaynatValue object = evaluate(node->object);
    KaynatValue index = evaluate(node->index);
    
    auto list = object.as_list();
    if (list) {
        auto idx = index.as_int();
        if (!idx) {
            throw TypeError("Integer", index.type_name(), node->line, 0);
        }
        
        if (*idx < 0 || static_cast<size_t>(*idx) >= list->size()) {
            throw IndexError(*idx, list->size(), node->line, 0);
        }
        
        return (*list)[*idx];
    }
    
    auto dict = object.as_dict();
    if (dict) {
        auto key = index.as_string();
        if (!key) {
            throw TypeError("String", index.type_name(), node->line, 0);
        }
        
        auto it = dict->find(*key);
        if (it == dict->end()) {
            return KaynatValue();
        }
        
        return it->second;
    }
    
    throw TypeError("List or Dictionary", object.type_name(), node->line, 0);
}

KaynatValue Interpreter::eval_property_access(const std::shared_ptr<PropertyAccessNode>& node) {
    // Not implemented yet
    return KaynatValue();
}

KaynatValue Interpreter::eval_block(const std::shared_ptr<BlockNode>& node) {
    KaynatValue last_value;
    
    for (const auto& stmt : node->statements) {
        if (return_flag_) break;
        last_value = evaluate(stmt);
    }
    
    return last_value;
}

void Interpreter::register_builtin_functions() {
    // Built-in functions will be registered here
}

void Interpreter::register_stdlib_functions() {
    // Math functions
    global_env_->define("sqrt", KaynatValue(CallableType([](std::vector<KaynatValue> args) -> KaynatValue {
        if (args.size() != 1) {
            throw RuntimeError("sqrt expects 1 argument", 0, 0);
        }
        auto num = args[0].as_float();
        if (!num) {
            auto int_val = args[0].as_int();
            if (int_val) {
                num = static_cast<double>(*int_val);
            } else {
                throw TypeError("Number", args[0].type_name(), 0, 0);
            }
        }
        return KaynatValue(std::sqrt(*num));
    })));
    
    global_env_->define("pow", KaynatValue(CallableType([](std::vector<KaynatValue> args) -> KaynatValue {
        if (args.size() != 2) {
            throw RuntimeError("pow expects 2 arguments", 0, 0);
        }
        auto base = args[0].as_float();
        auto exp = args[1].as_float();
        if (!base) {
            auto int_val = args[0].as_int();
            if (int_val) base = static_cast<double>(*int_val);
        }
        if (!exp) {
            auto int_val = args[1].as_int();
            if (int_val) exp = static_cast<double>(*int_val);
        }
        if (!base || !exp) {
            throw TypeError("Number", "unknown", 0, 0);
        }
        return KaynatValue(std::pow(*base, *exp));
    })));
    
    // String functions
    global_env_->define("uppercase", KaynatValue(CallableType([](std::vector<KaynatValue> args) -> KaynatValue {
        if (args.size() != 1) {
            throw RuntimeError("uppercase expects 1 argument", 0, 0);
        }
        auto str = args[0].as_string();
        if (!str) {
            throw TypeError("String", args[0].type_name(), 0, 0);
        }
        std::string result = *str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return KaynatValue(result);
    })));
    
    global_env_->define("lowercase", KaynatValue(CallableType([](std::vector<KaynatValue> args) -> KaynatValue {
        if (args.size() != 1) {
            throw RuntimeError("lowercase expects 1 argument", 0, 0);
        }
        auto str = args[0].as_string();
        if (!str) {
            throw TypeError("String", args[0].type_name(), 0, 0);
        }
        std::string result = *str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return KaynatValue(result);
    })));
}

} // namespace kaynat
