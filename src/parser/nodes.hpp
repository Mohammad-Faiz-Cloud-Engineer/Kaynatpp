/**
 * @file nodes.hpp
 * @brief Abstract Syntax Tree node definitions
 * 
 * Defines all AST node types for Kaynat++ parser.
 * Uses std::variant for type-safe node representation.
 */

#pragma once

#include "../lexer/token_types.hpp"
#include <memory>
#include <vector>
#include <string>
#include <variant>

namespace kaynat {

// Forward declarations
struct ProgramNode;
struct LiteralNode;
struct IdentifierNode;
struct BinaryOpNode;
struct UnaryOpNode;
struct AssignmentNode;
struct IfNode;
struct WhileNode;
struct ForEachNode;
struct FunctionDefNode;
struct FunctionCallNode;
struct ReturnNode;
struct ListNode;
struct DictNode;
struct IndexNode;
struct PropertyAccessNode;
struct BlockNode;

/**
 * @brief Base AST node using variant
 */
using ASTNode = std::variant<
    std::monostate,
    std::shared_ptr<ProgramNode>,
    std::shared_ptr<LiteralNode>,
    std::shared_ptr<IdentifierNode>,
    std::shared_ptr<BinaryOpNode>,
    std::shared_ptr<UnaryOpNode>,
    std::shared_ptr<AssignmentNode>,
    std::shared_ptr<IfNode>,
    std::shared_ptr<WhileNode>,
    std::shared_ptr<ForEachNode>,
    std::shared_ptr<FunctionDefNode>,
    std::shared_ptr<FunctionCallNode>,
    std::shared_ptr<ReturnNode>,
    std::shared_ptr<ListNode>,
    std::shared_ptr<DictNode>,
    std::shared_ptr<IndexNode>,
    std::shared_ptr<PropertyAccessNode>,
    std::shared_ptr<BlockNode>
>;

/**
 * @brief Program root node
 */
struct ProgramNode {
    std::vector<ASTNode> statements;
    uint32_t line;
};

/**
 * @brief Literal value node
 */
struct LiteralNode {
    enum class Type {
        INTEGER,
        FLOAT,
        STRING,
        BOOLEAN,
        NULL_VALUE
    };
    
    Type type;
    std::string value;
    uint32_t line;
};

/**
 * @brief Identifier reference
 */
struct IdentifierNode {
    std::string name;
    uint32_t line;
};

/**
 * @brief Binary operation
 */
struct BinaryOpNode {
    enum class Op {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        MODULO,
        EQUAL,
        NOT_EQUAL,
        LESS_THAN,
        LESS_EQUAL,
        GREATER_THAN,
        GREATER_EQUAL,
        AND,
        OR
    };
    
    Op op;
    ASTNode left;
    ASTNode right;
    uint32_t line;
};

/**
 * @brief Unary operation
 */
struct UnaryOpNode {
    enum class Op {
        NEGATE,
        NOT
    };
    
    Op op;
    ASTNode operand;
    uint32_t line;
};

/**
 * @brief Variable assignment
 */
struct AssignmentNode {
    std::string name;
    ASTNode value;
    bool is_constant;
    uint32_t line;
};

/**
 * @brief If-then-else conditional
 */
struct IfNode {
    ASTNode condition;
    std::vector<ASTNode> then_branch;
    std::vector<ASTNode> else_branch;
    uint32_t line;
};

/**
 * @brief While loop
 */
struct WhileNode {
    ASTNode condition;
    std::vector<ASTNode> body;
    uint32_t line;
};

/**
 * @brief For-each loop
 */
struct ForEachNode {
    std::string variable;
    ASTNode iterable;
    std::vector<ASTNode> body;
    uint32_t line;
};

/**
 * @brief Function definition
 */
struct FunctionDefNode {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<ASTNode> body;
    uint32_t line;
};

/**
 * @brief Function call
 */
struct FunctionCallNode {
    std::string name;
    std::vector<ASTNode> arguments;
    uint32_t line;
};

/**
 * @brief Return statement
 */
struct ReturnNode {
    ASTNode value;
    uint32_t line;
};

/**
 * @brief List literal
 */
struct ListNode {
    std::vector<ASTNode> elements;
    uint32_t line;
};

/**
 * @brief Dictionary literal
 */
struct DictNode {
    std::vector<std::pair<std::string, ASTNode>> entries;
    uint32_t line;
};

/**
 * @brief Index access (list[0], dict["key"])
 */
struct IndexNode {
    ASTNode object;
    ASTNode index;
    uint32_t line;
};

/**
 * @brief Property access (object.property)
 */
struct PropertyAccessNode {
    ASTNode object;
    std::string property;
    uint32_t line;
};

/**
 * @brief Block of statements
 */
struct BlockNode {
    std::vector<ASTNode> statements;
    uint32_t line;
};

} // namespace kaynat
