# Contributing to Kaynat++

Thank you for your interest in contributing to Kaynat++! This document provides guidelines and instructions for contributing to the project.

## Code of Conduct

- Be respectful and professional
- Focus on constructive feedback
- Help others learn and grow
- Maintain high code quality standards

## Getting Started

1. **Read the documentation**:
   - [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) - Understand what's built
   - [IMPLEMENTATION_STATUS.md](IMPLEMENTATION_STATUS.md) - See what needs work
   - [DEVELOPMENT_GUIDE.md](DEVELOPMENT_GUIDE.md) - Learn how to implement

2. **Set up your environment**:
   ```bash
   git clone <repository-url>
   cd kaynat
   cd third_party && ./setup_deps.sh && cd ..
   ./build.sh --debug
   ```

3. **Choose a task**:
   - Check [IMPLEMENTATION_STATUS.md](IMPLEMENTATION_STATUS.md) for open tasks
   - Look for issues labeled "good first issue"
   - Ask in discussions if unsure where to start

## Development Workflow

### 1. Create a Branch

```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/your-bug-fix
```

### 2. Implement Your Changes

Follow the code quality standards:

#### Code Quality Checklist

- [ ] Every function has Doxygen comments
- [ ] No raw `new` or `delete` (use smart pointers)
- [ ] No `using namespace std` in headers
- [ ] Compiles with `-Wall -Wextra -Wpedantic` with zero warnings
- [ ] No undefined behavior under sanitizers
- [ ] All `#include` directives are necessary
- [ ] No unused variables or functions
- [ ] Functions are under 50 lines
- [ ] All errors are properly handled
- [ ] Thread-safety is documented

#### Naming Conventions

- **Functions and variables**: `snake_case`
- **Classes and structs**: `PascalCase`
- **Constants and enums**: `SCREAMING_SNAKE_CASE`
- **Private members**: Trailing underscore `member_`

#### Example Code

```cpp
/**
 * @file feature.hpp
 * @brief Brief description of the feature
 * 
 * Detailed description explaining what this module does,
 * how it fits into the system, and any important notes.
 */

#pragma once

#include <string>
#include <memory>

namespace kaynat {

/**
 * @brief Class description
 * 
 * Detailed explanation of the class purpose and behavior.
 * 
 * Thread-safety: Not thread-safe. Each thread should have its own instance.
 */
class Feature {
public:
    /**
     * @brief Constructor description
     * @param param Description of parameter
     * @throws ExceptionType When this exception is thrown
     */
    explicit Feature(std::string param);
    
    /**
     * @brief Method description
     * @param input Description of input
     * @return Description of return value
     * @throws ExceptionType When this exception is thrown
     */
    std::string process(const std::string& input);
    
private:
    std::string data_;
};

} // namespace kaynat
```

### 3. Write Tests

Create tests for your changes:

```cpp
// test_feature.cpp
#include "feature.hpp"
#include <cassert>
#include <iostream>

void test_basic_functionality() {
    kaynat::Feature f("test");
    std::string result = f.process("input");
    assert(result == "expected");
    std::cout << "✓ test_basic_functionality passed\n";
}

void test_error_handling() {
    kaynat::Feature f("test");
    try {
        f.process("");
        assert(false && "Should have thrown");
    } catch (const kaynat::RuntimeError& e) {
        std::cout << "✓ test_error_handling passed\n";
    }
}

int main() {
    test_basic_functionality();
    test_error_handling();
    std::cout << "All tests passed!\n";
    return 0;
}
```

### 4. Test Your Changes

```bash
# Build with sanitizers
./build.sh --debug

# Run your tests
./build/debug/kaynat test_program.kn

# Check for memory leaks
valgrind --leak-check=full ./build/release/kaynat test_program.kn

# Run with sanitizers
./build/debug/kaynat test_program.kn
```

### 5. Update Documentation

- Update [IMPLEMENTATION_STATUS.md](IMPLEMENTATION_STATUS.md) to mark your task complete
- Add examples to relevant documentation files
- Update [SYNTAX_QUICK_REFERENCE.md](SYNTAX_QUICK_REFERENCE.md) if adding syntax
- Add comments explaining complex logic

### 6. Commit Your Changes

Write clear commit messages:

```bash
git add .
git commit -m "feat: implement lexer tokenization

- Add keyword map with all 200+ keywords
- Implement number tokenization (int and float)
- Implement string tokenization with escape sequences
- Add comprehensive error reporting
- Add tests for all token types

Closes #123"
```

Commit message format:
- `feat:` - New feature
- `fix:` - Bug fix
- `docs:` - Documentation changes
- `test:` - Adding tests
- `refactor:` - Code refactoring
- `perf:` - Performance improvements
- `style:` - Code style changes

### 7. Push and Create Pull Request

```bash
git push origin feature/your-feature-name
```

Then create a pull request on GitHub with:
- Clear title describing the change
- Description of what was implemented
- Reference to related issues
- Screenshots/examples if applicable

## What to Contribute

### High Priority

1. **Core Language Implementation**
   - Lexer implementation (`src/lexer/lexer.cpp`)
   - Parser implementation (`src/parser/parser.cpp`)
   - Interpreter implementation (`src/interpreter/interpreter.cpp`)
   - Runtime value operations (`src/interpreter/runtime_value.cpp`)

2. **Standard Library Modules**
   - Math tools
   - String tools
   - List tools
   - File tools
   - Any stdlib module from the list

3. **Example Programs**
   - Create examples 07-35
   - Test and verify existing examples

4. **Documentation**
   - Write remaining documentation pages
   - Improve existing documentation
   - Add more examples to docs

### Medium Priority

1. **Data Structures**
   - Implement DSA structures (stack, queue, BST, etc.)
   - Implement sorting algorithms
   - Implement searching algorithms

2. **OOP System**
   - Blueprint definitions
   - Instance management
   - Inheritance and polymorphism

3. **Testing**
   - Unit tests for all modules
   - Integration tests
   - Performance benchmarks

### Lower Priority

1. **GUI System**
   - ImGui integration
   - Widget implementations
   - Event system

2. **Advanced Features**
   - Concurrency support
   - Async operations
   - Network tools

## Code Review Process

All contributions go through code review:

1. **Automated Checks**
   - Code compiles without warnings
   - Tests pass
   - No memory leaks
   - No undefined behavior

2. **Manual Review**
   - Code follows style guidelines
   - Documentation is complete
   - Logic is correct and efficient
   - Error handling is proper

3. **Feedback**
   - Address reviewer comments
   - Make requested changes
   - Discuss design decisions

4. **Approval**
   - At least one maintainer approval required
   - All checks must pass
   - No unresolved comments

## Common Pitfalls to Avoid

### 1. Memory Management

```cpp
// ❌ WRONG - Raw pointer
char* buffer = new char[1024];
// ... code that might throw ...
delete[] buffer;

// ✅ CORRECT - Smart pointer
auto buffer = std::make_unique<char[]>(1024);
// ... code that might throw ...
// Automatically cleaned up
```

### 2. Error Handling

```cpp
// ❌ WRONG - Ignoring errors
auto value = kaynat_value.as_int();
return *value + 10;

// ✅ CORRECT - Checking errors
auto value = kaynat_value.as_int();
if (!value) {
    throw TypeError("Integer", kaynat_value.type_name(), line, col);
}
return *value + 10;
```

### 3. Resource Management

```cpp
// ❌ WRONG - Manual resource management
FILE* f = fopen("file.txt", "r");
// ... code ...
fclose(f);

// ✅ CORRECT - RAII wrapper
auto f = std::unique_ptr<FILE, decltype(&fclose)>(
    fopen("file.txt", "r"), fclose);
if (!f) {
    throw FileError("file.txt", "cannot open", 0, 0);
}
// ... code ...
// Automatically closed
```

### 4. Header Guards

```cpp
// ❌ WRONG - Missing include guard
// feature.hpp
class Feature { ... };

// ✅ CORRECT - Include guard
#pragma once
class Feature { ... };
```

### 5. Namespace Usage

```cpp
// ❌ WRONG - using namespace in header
// feature.hpp
using namespace std;
class Feature { ... };

// ✅ CORRECT - Explicit namespace
// feature.hpp
namespace kaynat {
class Feature { ... };
}
```

## Getting Help

- **Questions**: Open a discussion on GitHub
- **Bugs**: Open an issue with reproduction steps
- **Design Decisions**: Discuss in pull request comments
- **Documentation**: Check DEVELOPMENT_GUIDE.md

## Recognition

Contributors will be:
- Listed in CONTRIBUTORS.md
- Credited in release notes
- Acknowledged in documentation

## License

By contributing, you agree that your contributions will be licensed under the same license as the project.

---

Thank you for contributing to Kaynat++! Together we're building a language that speaks.

*Named Kaynat++. Built in silence. Meant to speak.*
