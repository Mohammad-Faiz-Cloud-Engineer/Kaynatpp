/**
 * @file token_types.hpp
 * @brief Token type definitions for Kaynat++ lexer
 * 
 * Defines all token types and the Token structure used during lexical analysis.
 */

#pragma once

#include <string>
#include <cstdint>

namespace kaynat {

/**
 * @brief All token types in Kaynat++
 * 
 * Organized by category: literals, keywords, operators, punctuation, special.
 */
enum class TokenType {
    // Literals
    INTEGER,
    FLOAT,
    STRING,
    CHARACTER,
    TRUE,
    FALSE,
    NOTHING,
    
    // Identifiers
    IDENTIFIER,
    
    // Keywords - Variables
    SET,
    LET,
    DEFINE,
    ALWAYS,
    CHANGE,
    FORGET,
    CHECK,
    EXISTS,
    
    // Keywords - Arithmetic
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    FIND,
    RAISE,
    POWER,
    SQUARE,
    ROOT,
    ABSOLUTE,
    VALUE,
    ROUND,
    CEILING,
    FLOOR,
    LOGARITHM,
    SINE,
    COSINE,
    TANGENT,
    PRODUCT,
    REMAINDER,
    INTEGER_DIVISION,
    
    // Keywords - String
    JOIN,
    LENGTH,
    UPPERCASE,
    LOWERCASE,
    TRIM,
    WHITESPACE,
    STARTS,
    ENDS,
    REPLACE,
    SPLIT,
    POSITION,
    TAKE,
    CHARACTERS,
    REVERSE,
    REPEAT,
    CONTAINS,
    
    // Keywords - Comparison
    IS,
    EQUAL,
    NOT,
    GREATER,
    LESS,
    THAN,
    OR,
    AND,
    EMPTY,
    
    // Keywords - Types
    NUMBER,
    TEXT,
    LIST,
    MAP,
    BIG,
    TYPE,
    CONVERT,
    TURN,
    INTO,
    
    // Keywords - Control Flow
    IF,
    THEN,
    OTHERWISE,
    END,
    WHEN,
    DO,
    BY,
    DEFAULT,
    // REPEAT already defined in String operations
    TIMES,
    WHILE,
    UNTIL,
    FOR,
    EACH,
    IN,
    LOOP,
    FROM,
    TO,
    STEPPING,
    STOP,
    SKIP,
    
    // Keywords - Functions
    FUNCTION,
    CALLED,
    THAT,
    TAKES,
    GIVE,
    BACK,
    CALL,
    WITH,
    INLINE,
    GIVES,
    
    // Keywords - Collections
    CREATE,
    CONTAINING,
    INSERT,
    AT,
    REMOVE,
    GET,
    ITEM,
    SORT,
    ASCENDING,
    DESCENDING,
    FILTER,
    WHERE,
    REDUCE,
    USING,
    COPY,
    FLATTEN,
    KEY,
    
    // Keywords - I/O
    ASK,
    USER,
    READ,
    SAY,
    PRINT,
    SHOW,
    
    // Keywords - File System
    FILE,
    LINE,
    WRITE,
    APPEND,
    DELETE,
    
    // Keywords - Error Handling
    ATTEMPT,
    IT,
    FAILS,
    MESSAGE,
    AFTER,
    // RAISE already defined in Arithmetic
    ERROR,
    SAYING,
    
    // Keywords - Scope
    GLOBAL,
    BRING,
    USE,
    MODULE,
    NAMED,
    EXPORT,
    
    // Keywords - Comments
    NOTE,
    BEGIN,
    
    // Keywords - Program
    PROGRAM,
    
    // Keywords - OOP
    BLUEPRINT,
    HAS,
    INITIALIZE,
    MY,
    NEW,
    ON,
    EXTENDS,
    PARENT,
    ABSTRACT,
    THIS,
    MUST,
    BE,
    IMPLEMENTED,
    CONTRACT,
    REQUIRES,
    PRIVATE,
    
    // Keywords - DSA
    STACK,
    QUEUE,
    PUSH,
    ONTO,
    POP,
    PEEK,
    SIZE,
    ENQUEUE,
    DEQUEUE,
    FRONT,
    LINKED,
    NODE,
    BINARY,
    SEARCH,
    TREE,
    INORDER,
    PREORDER,
    POSTORDER,
    TRAVERSE,
    HEIGHT,
    MINIMUM,
    MAXIMUM,
    GRAPH,
    EDGE,
    WEIGHT,
    SHORTEST,
    PATH,
    DIJKSTRA,
    BREADTH,
    FIRST,
    DEPTH,
    CYCLE,
    CONNECTED,
    COMPONENTS,
    MIN,
    HEAP,
    MAX,
    EXTRACT,
    HASH,
    PUT,
    LOAD,
    FACTOR,
    TRIE,
    WORD,
    ALL,
    WORDS,
    STARTING,
    SUGGESTIONS,
    NUMBERS,
    BUBBLE,
    MERGE,
    QUICK,
    INSERTION,
    SELECTION,
    RADIX,
    COUNTING,
    LINEAR,
    KNUTH,
    MORRIS,
    PRATT,
    PATTERN,
    POSITIONS,
    SORTED,
    BELLMAN,
    FORD,
    SPANNING,
    KRUSKAL,
    PRIM,
    TOPOLOGICAL,
    STRONGLY,
    KOSARAJU,
    
    // Keywords - GUI
    WINDOW,
    TITLE,
    WIDTH,
    // HEIGHT already defined in DSA
    BACKGROUND,
    LABEL,
    FONT,
    PLACE,
    ROW,
    COLUMN,
    BUTTON,
    ACTION,
    INPUT,
    PLACEHOLDER,
    AREA,
    CHECKBOX,
    DROPDOWN,
    OPTIONS,
    SLIDER,
    PROGRESS,
    BAR,
    DRAW,
    DRAWING,
    BOARD,
    COLOR,
    RECTANGLE,
    FILL,
    CIRCLE,
    RADIUS,
    CONFIRM,
    CHOOSE,
    CLICKED,
    CHANGES,
    CLOSED,
    APPLY,
    THEME,
    DARK,
    LIGHT,
    MENU,
    SEPARATOR,
    ATTACH,
    
    // Keywords - Async
    RUN,
    // BACKGROUND already defined in GUI
    WAIT,
    FINISH,
    FINISHES,
    SAVE,
    TASK,
    BOTH,
    TIMER,
    SECONDS,
    CANCEL,
    REFRESH,
    
    // Keywords - Misc
    AS,
    THE,
    A,
    AN,
    OF,
    STORE,
    CURRENT,
    RESULT,
    DECIMAL,
    PLACES,
    BASE,
    ANGLE,
    OFFSET,
    NAME,
    AGE,
    DESCRIPTION,
    RESPONSE,
    CONTENT,
    LINES,
    CONFIG,
    TEMP,
    NESTED,
    FLAT,
    FIELDS,
    VALUES,
    TOTAL,
    SUMMARY,
    UPPERCASE_FUNC,
    LOWERCASE_FUNC,
    NEGATIVE,
    COMMA,
    PERIOD_KW,
    SPACE,
    STAR,
    BORDER,
    LIMIT,
    ACTIVE,
    VERIFIED,
    FINISHED,
    FRUITS,
    DAY,
    MONDAY,
    FRIDAY,
    WEEK,
    REGULAR,
    HELLO,
    WORLD,
    GREETING,
    CLEANUP,
    COMPLETE,
    CANNOT,
    VALIDATION,
    SCORE,
    TYPE_NAME,
    UTILS,
    STRING_TOOLS,
    CALCULATE,
    // AREA already defined in GUI
    WELCOME,
    KAYNAT,
    
    // Punctuation
    PERIOD,
    COMMA_PUNCT,
    
    // Special
    END_OF_FILE,
    INVALID
};

/**
 * @brief Token structure
 * 
 * Represents a single lexical token with type, lexeme, and source location.
 */
struct Token {
    TokenType type;
    std::string lexeme;
    uint32_t line;
    uint32_t column;
    
    Token() : type(TokenType::INVALID), line(0), column(0) {}
    
    Token(TokenType t, std::string lex, uint32_t ln, uint32_t col)
        : type(t), lexeme(std::move(lex)), line(ln), column(col) {}
    
    /**
     * @brief Get human-readable token type name
     */
    std::string type_name() const;
};

/**
 * @brief Convert token type to string for debugging
 */
const char* token_type_to_string(TokenType type);

} // namespace kaynat
