/**
 * @file interpreter.cpp
 * @brief Interpreter implementation for Kaynat++
 */

#include "interpreter.hpp"
#include "../errors/error_types.hpp"
#include "../stdlib/stdlib.hpp"
#include "../gui/gui_system.hpp"
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
        else if constexpr (std::is_same_v<T, std::shared_ptr<RepeatNode>>) {
            return eval_repeat(arg);
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
        else if constexpr (std::is_same_v<T, std::shared_ptr<GUINode>>) {
            return eval_gui(arg);
        }
        
        return KaynatValue();
    }, node);
}

KaynatValue Interpreter::eval_program(const std::shared_ptr<ProgramNode>& node) {
    KaynatValue last_value;
    
    for (const auto& stmt : node->statements) {
        if (return_flag_) break;
        
        // Skip empty statements (comments)
        if (std::holds_alternative<std::monostate>(stmt)) {
            continue;
        }
        
        last_value = evaluate(stmt);
    }
    
    return last_value;
}

KaynatValue Interpreter::eval_literal(const std::shared_ptr<LiteralNode>& node) {
    switch (node->type) {
        case LiteralNode::Type::INTEGER:
            return KaynatValue(static_cast<int64_t>(std::stoll(node->value)));
        
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

KaynatValue Interpreter::eval_repeat(const std::shared_ptr<RepeatNode>& node) {
    KaynatValue count_value = evaluate(node->count);
    
    auto count_opt = count_value.as_int();
    if (!count_opt.has_value()) {
        throw TypeError("Integer", count_value.type_name(), node->line, 0);
    }
    
    int64_t count = count_opt.value();
    KaynatValue last_value;
    
    for (int64_t i = 0; i < count; i++) {
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

KaynatValue Interpreter::eval_property_access([[maybe_unused]] const std::shared_ptr<PropertyAccessNode>& node) {
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
    // Math functions (20)
    global_env_->define("sqrt", KaynatValue(CallableType(stdlib::math_sqrt)));
    global_env_->define("pow", KaynatValue(CallableType(stdlib::math_pow)));
    global_env_->define("abs", KaynatValue(CallableType(stdlib::math_abs)));
    global_env_->define("floor", KaynatValue(CallableType(stdlib::math_floor)));
    global_env_->define("ceil", KaynatValue(CallableType(stdlib::math_ceil)));
    global_env_->define("round", KaynatValue(CallableType(stdlib::math_round)));
    global_env_->define("sin", KaynatValue(CallableType(stdlib::math_sin)));
    global_env_->define("cos", KaynatValue(CallableType(stdlib::math_cos)));
    global_env_->define("tan", KaynatValue(CallableType(stdlib::math_tan)));
    global_env_->define("log", KaynatValue(CallableType(stdlib::math_log)));
    global_env_->define("log10", KaynatValue(CallableType(stdlib::math_log10)));
    global_env_->define("exp", KaynatValue(CallableType(stdlib::math_exp)));
    global_env_->define("min", KaynatValue(CallableType(stdlib::math_min)));
    global_env_->define("max", KaynatValue(CallableType(stdlib::math_max)));
    global_env_->define("factorial", KaynatValue(CallableType(stdlib::math_factorial)));
    global_env_->define("gcd", KaynatValue(CallableType(stdlib::math_gcd)));
    global_env_->define("lcm", KaynatValue(CallableType(stdlib::math_lcm)));
    global_env_->define("is_prime", KaynatValue(CallableType(stdlib::math_is_prime)));
    global_env_->define("random", KaynatValue(CallableType(stdlib::math_random)));
    global_env_->define("pi", KaynatValue(CallableType(stdlib::math_pi)));
    
    // String functions (20)
    global_env_->define("uppercase", KaynatValue(CallableType(stdlib::string_uppercase)));
    global_env_->define("lowercase", KaynatValue(CallableType(stdlib::string_lowercase)));
    global_env_->define("string_length", KaynatValue(CallableType(stdlib::string_length)));
    global_env_->define("trim", KaynatValue(CallableType(stdlib::string_trim)));
    global_env_->define("split", KaynatValue(CallableType(stdlib::string_split)));
    global_env_->define("join", KaynatValue(CallableType(stdlib::string_join)));
    global_env_->define("replace", KaynatValue(CallableType(stdlib::string_replace)));
    global_env_->define("starts_with", KaynatValue(CallableType(stdlib::string_starts_with)));
    global_env_->define("ends_with", KaynatValue(CallableType(stdlib::string_ends_with)));
    global_env_->define("contains", KaynatValue(CallableType(stdlib::string_contains)));
    global_env_->define("substring", KaynatValue(CallableType(stdlib::string_substring)));
    global_env_->define("index_of", KaynatValue(CallableType(stdlib::string_index_of)));
    global_env_->define("string_reverse", KaynatValue(CallableType(stdlib::string_reverse)));
    global_env_->define("string_repeat", KaynatValue(CallableType(stdlib::string_repeat)));
    global_env_->define("pad_left", KaynatValue(CallableType(stdlib::string_pad_left)));
    global_env_->define("pad_right", KaynatValue(CallableType(stdlib::string_pad_right)));
    global_env_->define("to_number", KaynatValue(CallableType(stdlib::string_to_number)));
    global_env_->define("to_list", KaynatValue(CallableType(stdlib::string_to_list)));
    global_env_->define("is_empty", KaynatValue(CallableType(stdlib::string_is_empty)));
    global_env_->define("capitalize", KaynatValue(CallableType(stdlib::string_capitalize)));
    
    // List functions (20)
    global_env_->define("list_length", KaynatValue(CallableType(stdlib::list_length)));
    global_env_->define("list_append", KaynatValue(CallableType(stdlib::list_append)));
    global_env_->define("list_prepend", KaynatValue(CallableType(stdlib::list_prepend)));
    global_env_->define("list_insert", KaynatValue(CallableType(stdlib::list_insert)));
    global_env_->define("list_remove", KaynatValue(CallableType(stdlib::list_remove)));
    global_env_->define("list_get", KaynatValue(CallableType(stdlib::list_get)));
    global_env_->define("list_set", KaynatValue(CallableType(stdlib::list_set)));
    global_env_->define("list_slice", KaynatValue(CallableType(stdlib::list_slice)));
    global_env_->define("list_sort", KaynatValue(CallableType(stdlib::list_sort)));
    global_env_->define("list_reverse", KaynatValue(CallableType(stdlib::list_reverse)));
    global_env_->define("list_contains", KaynatValue(CallableType(stdlib::list_contains)));
    global_env_->define("list_index_of", KaynatValue(CallableType(stdlib::list_index_of)));
    global_env_->define("list_min", KaynatValue(CallableType(stdlib::list_min)));
    global_env_->define("list_max", KaynatValue(CallableType(stdlib::list_max)));
    global_env_->define("list_sum", KaynatValue(CallableType(stdlib::list_sum)));
    global_env_->define("list_filter", KaynatValue(CallableType(stdlib::list_filter)));
    global_env_->define("list_map", KaynatValue(CallableType(stdlib::list_map)));
    global_env_->define("list_reduce", KaynatValue(CallableType(stdlib::list_reduce)));
    global_env_->define("list_unique", KaynatValue(CallableType(stdlib::list_unique)));
    global_env_->define("list_flatten", KaynatValue(CallableType(stdlib::list_flatten)));
    
    // File functions (12)
    global_env_->define("file_read", KaynatValue(CallableType(stdlib::file_read)));
    global_env_->define("file_write", KaynatValue(CallableType(stdlib::file_write)));
    global_env_->define("file_append", KaynatValue(CallableType(stdlib::file_append)));
    global_env_->define("file_exists", KaynatValue(CallableType(stdlib::file_exists)));
    global_env_->define("file_delete", KaynatValue(CallableType(stdlib::file_delete)));
    global_env_->define("file_copy", KaynatValue(CallableType(stdlib::file_copy)));
    global_env_->define("file_move", KaynatValue(CallableType(stdlib::file_move)));
    global_env_->define("file_size", KaynatValue(CallableType(stdlib::file_size)));
    global_env_->define("file_list_dir", KaynatValue(CallableType(stdlib::file_list_dir)));
    global_env_->define("file_create_dir", KaynatValue(CallableType(stdlib::file_create_dir)));
    global_env_->define("file_is_file", KaynatValue(CallableType(stdlib::file_is_file)));
    global_env_->define("file_is_dir", KaynatValue(CallableType(stdlib::file_is_dir)));
    
    // Date functions (5)
    global_env_->define("date_now", KaynatValue(CallableType(stdlib::date_now)));
    global_env_->define("date_format", KaynatValue(CallableType(stdlib::date_format)));
    global_env_->define("date_parse", KaynatValue(CallableType(stdlib::date_parse)));
    global_env_->define("date_add_days", KaynatValue(CallableType(stdlib::date_add_days)));
    global_env_->define("date_diff_days", KaynatValue(CallableType(stdlib::date_diff_days)));
    
    // Random functions (6)
    global_env_->define("random_int", KaynatValue(CallableType(stdlib::random_int)));
    global_env_->define("random_float", KaynatValue(CallableType(stdlib::random_float)));
    global_env_->define("random_choice", KaynatValue(CallableType(stdlib::random_choice)));
    global_env_->define("random_shuffle", KaynatValue(CallableType(stdlib::random_shuffle)));
    global_env_->define("random_sample", KaynatValue(CallableType(stdlib::random_sample)));
    global_env_->define("random_seed", KaynatValue(CallableType(stdlib::random_seed)));
    
    // Network functions (2)
    global_env_->define("http_get", KaynatValue(CallableType(stdlib::network_http_get)));
    global_env_->define("http_post", KaynatValue(CallableType(stdlib::network_http_post)));
    
    // JSON functions (3)
    global_env_->define("json_parse", KaynatValue(CallableType(stdlib::json_parse)));
    global_env_->define("json_stringify", KaynatValue(CallableType(stdlib::json_stringify)));
    global_env_->define("json_format", KaynatValue(CallableType(stdlib::json_format)));
    
    // Crypto functions (5)
    global_env_->define("sha256", KaynatValue(CallableType(stdlib::crypto_sha256)));
    global_env_->define("md5", KaynatValue(CallableType(stdlib::crypto_md5)));
    global_env_->define("base64_encode", KaynatValue(CallableType(stdlib::crypto_base64_encode)));
    global_env_->define("base64_decode", KaynatValue(CallableType(stdlib::crypto_base64_decode)));
    global_env_->define("random_token", KaynatValue(CallableType(stdlib::crypto_random_token)));
    
    // Pattern functions (6)
    global_env_->define("pattern_match", KaynatValue(CallableType(stdlib::pattern_match)));
    global_env_->define("pattern_find_all", KaynatValue(CallableType(stdlib::pattern_find_all)));
    global_env_->define("pattern_replace", KaynatValue(CallableType(stdlib::pattern_replace)));
    global_env_->define("pattern_split", KaynatValue(CallableType(stdlib::pattern_split)));
    global_env_->define("is_email", KaynatValue(CallableType(stdlib::pattern_is_email)));
    global_env_->define("is_url", KaynatValue(CallableType(stdlib::pattern_is_url)));
}


KaynatValue Interpreter::eval_gui(const std::shared_ptr<GUINode>& node) {
    auto& gui_mgr = GUIManager::instance();
    
    switch (node->command) {
        case GUINode::Command::CREATE_WINDOW: {
            auto window = std::make_shared<Window>(node->target, 800, 600);
            gui_mgr.register_window(node->target, window);
            current_env_->define(node->target, KaynatValue());  // Store reference
            break;
        }
        
        case GUINode::Command::SET_TITLE: {
            auto window = gui_mgr.get_window(node->target);
            if (window && !node->arguments.empty()) {
                KaynatValue val = evaluate(node->arguments[0]);
                auto str = val.as_string();
                if (str) window->title = *str;
            }
            break;
        }
        
        case GUINode::Command::SET_WIDTH: {
            auto window = gui_mgr.get_window(node->target);
            if (window && !node->arguments.empty()) {
                KaynatValue val = evaluate(node->arguments[0]);
                auto num = val.as_int();
                if (num) window->width = static_cast<int>(*num);
            }
            break;
        }
        
        case GUINode::Command::SET_HEIGHT: {
            auto window = gui_mgr.get_window(node->target);
            if (window && !node->arguments.empty()) {
                KaynatValue val = evaluate(node->arguments[0]);
                auto num = val.as_int();
                if (num) window->height = static_cast<int>(*num);
            }
            break;
        }
        
        case GUINode::Command::SET_BACKGROUND: {
            auto window = gui_mgr.get_window(node->target);
            if (window && !node->arguments.empty()) {
                KaynatValue val = evaluate(node->arguments[0]);
                auto str = val.as_string();
                if (str) window->background_color = *str;
            }
            break;
        }
        
        case GUINode::Command::SHOW_WINDOW: {
            auto window = gui_mgr.get_window(node->target);
            if (window) window->show();
            break;
        }
        
        case GUINode::Command::CREATE_LABEL: {
            auto label = std::make_shared<Label>("");
            label->id = node->target;
            current_env_->define(node->target, KaynatValue());
            // Store widget for later access
            gui_mgr.register_widget(node->target, label);
            break;
        }
        
        case GUINode::Command::SET_TEXT: {
            auto widget = gui_mgr.get_widget(node->target);
            if (widget && !node->arguments.empty()) {
                KaynatValue val = evaluate(node->arguments[0]);
                auto str = val.as_string();
                if (str) {
                    if (auto label = std::dynamic_pointer_cast<Label>(widget)) {
                        label->text = *str;
                    } else if (auto button = std::dynamic_pointer_cast<Button>(widget)) {
                        button->text = *str;
                    }
                }
            }
            break;
        }
        
        case GUINode::Command::CREATE_BUTTON: {
            auto button = std::make_shared<Button>("");
            button->id = node->target;
            current_env_->define(node->target, KaynatValue());
            gui_mgr.register_widget(node->target, button);
            break;
        }
        
        case GUINode::Command::CREATE_INPUT: {
            auto input = std::make_shared<TextInput>("");
            input->id = node->target;
            current_env_->define(node->target, KaynatValue());
            gui_mgr.register_widget(node->target, input);
            break;
        }
        
        case GUINode::Command::SET_PLACEHOLDER: {
            auto widget = gui_mgr.get_widget(node->target);
            if (widget && !node->arguments.empty()) {
                KaynatValue val = evaluate(node->arguments[0]);
                auto str = val.as_string();
                if (str) {
                    if (auto input = std::dynamic_pointer_cast<TextInput>(widget)) {
                        input->placeholder = *str;
                    }
                }
            }
            break;
        }
        
        case GUINode::Command::PLACE_WIDGET: {
            auto widget = gui_mgr.get_widget(node->target);
            if (widget && node->arguments.size() >= 3) {
                // Get row, column, window name
                auto row_val = evaluate(node->arguments[0]).as_int();
                auto col_val = evaluate(node->arguments[1]).as_int();
                auto win_val = evaluate(node->arguments[2]).as_string();
                
                if (row_val && col_val && win_val) {
                    auto window = gui_mgr.get_window(*win_val);
                    if (window) {
                        widget->x = static_cast<int>(*col_val);
                        widget->y = static_cast<int>(*row_val);
                        window->add_widget(widget);
                    }
                }
            }
            break;
        }
    }
    
    return KaynatValue();
}
} // namespace kaynat
