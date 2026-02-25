/**
 * @file interpreter.hpp
 * @brief Tree-walking interpreter for Kaynat++
 * 
 * Executes AST nodes and manages runtime state.
 */

#pragma once

#include "runtime_value.hpp"
#include "environment.hpp"
#include "../parser/nodes.hpp"
#include <memory>

namespace kaynat {

/**
 * @brief Tree-walking interpreter for Kaynat++
 * 
 * Executes AST by recursively evaluating nodes.
 * Manages global environment and function call stack.
 */
class Interpreter {
public:
    /**
     * @brief Construct interpreter with global environment
     */
    Interpreter();
    
    /**
     * @brief Execute a program
     * @param program Root program node
     * @return Last expression value or null
     */
    KaynatValue execute(const std::shared_ptr<ProgramNode>& program);
    
    /**
     * @brief Evaluate an AST node
     * @param node Node to evaluate
     * @return Resulting value
     */
    KaynatValue evaluate(const ASTNode& node);
    
private:
    std::shared_ptr<Environment> global_env_;
    std::shared_ptr<Environment> current_env_;
    bool return_flag_;
    KaynatValue return_value_;
    
    // Node evaluation methods
    KaynatValue eval_program(const std::shared_ptr<ProgramNode>& node);
    KaynatValue eval_literal(const std::shared_ptr<LiteralNode>& node);
    KaynatValue eval_identifier(const std::shared_ptr<IdentifierNode>& node);
    KaynatValue eval_binary_op(const std::shared_ptr<BinaryOpNode>& node);
    KaynatValue eval_unary_op(const std::shared_ptr<UnaryOpNode>& node);
    KaynatValue eval_assignment(const std::shared_ptr<AssignmentNode>& node);
    KaynatValue eval_if(const std::shared_ptr<IfNode>& node);
    KaynatValue eval_while(const std::shared_ptr<WhileNode>& node);
    KaynatValue eval_for_each(const std::shared_ptr<ForEachNode>& node);
    KaynatValue eval_function_def(const std::shared_ptr<FunctionDefNode>& node);
    KaynatValue eval_function_call(const std::shared_ptr<FunctionCallNode>& node);
    KaynatValue eval_return(const std::shared_ptr<ReturnNode>& node);
    KaynatValue eval_list(const std::shared_ptr<ListNode>& node);
    KaynatValue eval_dict(const std::shared_ptr<DictNode>& node);
    KaynatValue eval_index(const std::shared_ptr<IndexNode>& node);
    KaynatValue eval_property_access(const std::shared_ptr<PropertyAccessNode>& node);
    KaynatValue eval_block(const std::shared_ptr<BlockNode>& node);
    
    // Helper methods
    void register_builtin_functions();
    void register_stdlib_functions();
};

} // namespace kaynat
