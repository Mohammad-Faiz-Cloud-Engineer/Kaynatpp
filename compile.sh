#!/bin/bash
# Direct g++ compilation script for Kaynat++ (when CMake is not available)

echo "Compiling Kaynat++ with g++..."

g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -I./src -o kaynat \
  src/main.cpp \
  src/repl.cpp \
  src/lexer/lexer.cpp \
  src/parser/parser.cpp \
  src/interpreter/interpreter.cpp \
  src/interpreter/environment.cpp \
  src/interpreter/runtime_value.cpp \
  src/errors/messages.cpp \
  src/stdlib/math_tools.cpp \
  src/stdlib/string_tools.cpp \
  src/stdlib/list_tools.cpp \
  src/stdlib/other_tools.cpp \
  src/gui/gui_system.cpp

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "✓ Executable: ./kaynat"
    echo ""
    echo "Usage:"
    echo "  ./kaynat                    # Start REPL"
    echo "  ./kaynat <file.kn>          # Run a Kaynat++ program"
else
    echo "✗ Compilation failed!"
    exit 1
fi
