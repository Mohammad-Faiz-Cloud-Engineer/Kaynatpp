# Kaynat++ Grammar Reference

Formal grammar specification for Kaynat++.

## Lexical Structure

### Keywords

```
Program: begin, program, end
Variables: set, let, define, always, change, forget, check, exists
Arithmetic: add, subtract, multiply, divide, find, raise, power, square, root
Strings: join, split, trim, uppercase, lowercase, replace, reverse, repeat
Comparison: is, equal, not, greater, less, than, or, and
Control: if, then, otherwise, when, do, by, default
Loops: repeat, times, while, until, for, each, in, loop, from, to, stepping, stop, skip
Functions: function, called, that, takes, give, back, call, with, inline, gives
Collections: list, map, containing, create, add, remove, get, item, at, insert
I/O: ask, user, read, say, print, show
Files: file, line, write, append, delete
Errors: attempt, it, fails, message, after, raise, error, saying
Types: number, text, type, convert, turn, into
OOP: blueprint, has, initialize, my, new, on, extends, parent, abstract, this, must, be, implemented, contract, requires, private
DSA: stack, queue, push, pop, peek, enqueue, dequeue, tree, graph, heap, hash, trie
GUI: window, title, width, height, button, label, input, place, row, column
```

### Punctuation

```
Period: .
Comma: ,
```

### Literals

```
Integer: [0-9]+
Float: [0-9]+\.[0-9]+
String: [a-zA-Z0-9 ]+
Boolean: true | false
Null: nothing
```

## Grammar Rules

### Program

```
program ::= "begin" "program" "." statements "end" "program" "."
```

### Statements

```
statement ::= variable_declaration
            | assignment
            | arithmetic_operation
            | conditional
            | loop
            | function_definition
            | function_call
            | io_operation
            | comment
```

### Variable Declaration

```
variable_declaration ::= "set" identifier "to" expression "."
                       | "let" identifier "be" expression "."
                       | "define" identifier "as" expression "."
                       | "always" "set" identifier "as" expression "."
```

### Assignment

```
assignment ::= "change" identifier "to" expression "."
```

### Arithmetic

```
arithmetic ::= "add" expression "to" identifier "."
             | "subtract" expression "from" identifier "."
             | "multiply" identifier "by" expression "."
             | "divide" identifier "by" expression "."
```

### Conditional

```
conditional ::= "if" condition "then" "." statements ("otherwise" "." statements)? "end" "."
```

### Loop

```
loop ::= "repeat" expression "times" "." statements "end" "."
       | "while" condition "." statements "end" "."
       | "for" "each" identifier "in" expression "." statements "end" "."
       | "loop" "from" expression "to" expression ("stepping" "by" expression)? "." statements "end" "."
```

### Function

```
function_definition ::= "define" "a" "function" "called" identifier "that" "takes" parameters "." statements "end" "."
function_call ::= "call" identifier "with" arguments ("and" "store" "as" identifier)? "."
```

### Expression

```
expression ::= literal
             | identifier
             | binary_operation
             | function_call
```

### Condition

```
condition ::= expression comparison_operator expression
            | condition logical_operator condition
            | "not" condition
```

---

This grammar defines the complete syntax of Kaynat++.
