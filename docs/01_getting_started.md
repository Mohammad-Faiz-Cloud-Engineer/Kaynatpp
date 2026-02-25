# Getting Started with Kaynat++

Welcome to Kaynat++, a programming language that reads like English!

## What is Kaynat++?

Kaynat++ is a fully production-grade, Turing-complete programming language with English syntax. Instead of cryptic symbols and operators, you write code that reads like natural language.

**Traditional language:**
```python
if x > 10:
    print("Hello")
```

**Kaynat++:**
```
if x is greater than 10 then.
say hello.
end.
```

Every statement ends with a period. Commas separate items. That's it—no curly braces, no semicolons, no cryptic operators.

## Installation

### Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.20 or higher
- SDL2 development libraries
- libcurl development libraries

### Building from Source

1. **Clone the repository:**
```bash
git clone https://github.com/Mohammad-Faiz-Cloud-Engineer/Kaynatpp.git
cd Kaynatpp
```

2. **Install dependencies (Ubuntu/Debian):**
```bash
sudo apt-get install build-essential cmake libsdl2-dev libcurl4-openssl-dev
```

3. **Install dependencies (macOS):**
```bash
brew install cmake sdl2 curl
```

4. **Configure and build:**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

5. **Install (optional):**
```bash
sudo cmake --install build
```

The `kaynat` binary will be in `build/kaynat`.

## Your First Program

Create a file called `hello.kn`:

```
begin program.
say hello, world.
end program.
```

Run it:

```bash
./build/kaynat hello.kn
```

Output:
```
hello world
```

## Understanding the Syntax

### The Period and Comma

- **Period (.)**: Ends every statement
- **Comma (,)**: Separates items in lists or parameters

```
set fruits to a list containing apple, banana, cherry.
say my favorite fruits are apple, banana, and cherry.
```

### Program Structure

Every Kaynat++ program starts with `begin program.` and ends with `end program.`:

```
begin program.
    note. your code goes here.
end program.
```

### Comments

Use `note.` for single-line comments:

```
note. this is a comment.
set x to 10.
```

Use `begin note.` and `end note.` for multi-line comments:

```
begin note.
this is a longer comment
that spans multiple lines.
end note.
```

### Variables

Create variables with `set`:

```
set name to Kaynat++.
set age to 21.
set price to 9.99.
set active to true.
```

### Output

Use `say` to print to the console:

```
say hello, world.
say the answer is 42.
```

### Arithmetic

Arithmetic reads like English:

```
set x to 10.
add 5 to x.
say x.  note. outputs 15.

set y to 20.
multiply y by 3.
say y.  note. outputs 60.
```

### Conditionals

```
set age to 25.

if age is greater than 18 then.
    say you are an adult.
otherwise.
    say you are a minor.
end.
```

### Loops

Repeat a fixed number of times:

```
repeat 5 times.
    say hello.
end.
```

Loop with a condition:

```
set count to 0.
while count is less than 10.
    say count.
    add 1 to count.
end.
```

Loop through a list:

```
set fruits to a list containing apple, banana, cherry.
for each fruit in fruits.
    say fruit.
end.
```

## The REPL

Start the interactive REPL (Read-Eval-Print Loop):

```bash
./build/kaynat --repl
```

You can type Kaynat++ statements and see results immediately:

```
>>> set x to 10.
>>> add 5 to x.
>>> say x.
15
>>> exit.
```

## Example Programs

### Calculator

```
begin program.
set a to 10.
set b to 5.

add b to a.
say the sum is a.

set x to 20.
set y to 3.
multiply x by y.
say the product is x.
end program.
```

### Number Guessing Game

```
begin program.
set secret to 42.
set guess to 0.

say guess the number between 1 and 100.

while guess is not equal to secret.
    ask the user for guess.
    
    if guess is less than secret then.
        say too low, try again.
    otherwise if guess is greater than secret then.
        say too high, try again.
    otherwise.
        say correct, you win.
    end.
end.
end program.
```

## Reading Error Messages

Kaynat++ provides clear error messages with line numbers:

```
Error at line 5, column 10: Undefined variable 'count'
```

Common errors:

- **Undefined variable**: You're using a variable that hasn't been set
- **Type mismatch**: You're trying to perform an operation on incompatible types
- **Syntax error**: Your code doesn't follow Kaynat++ grammar rules

## Next Steps

- Read the [Core Language Reference](02_core_language.md) for complete syntax
- Explore [Object-Oriented Programming](03_oop.md) to learn about blueprints
- Check out [Data Structures & Algorithms](04_dsa.md) for advanced features
- Try [GUI Programming](05_gui.md) to build desktop applications

## Quick Reference

| Task | Syntax |
|------|--------|
| Variable | `set x to 10.` |
| Constant | `always set pi as 3.14.` |
| Output | `say hello, world.` |
| Input | `ask the user for name.` |
| Add | `add 5 to x.` |
| Subtract | `subtract 3 from x.` |
| Multiply | `multiply x by 2.` |
| Divide | `divide x by 4.` |
| If statement | `if x is greater than 10 then. ... end.` |
| While loop | `while x is less than 100. ... end.` |
| For each | `for each item in list. ... end.` |
| Function | `define a function called greet that takes name. ... end.` |
| List | `set items to a list containing a, b, c.` |
| Comment | `note. this is a comment.` |

---

*Welcome to Kaynat++. Write code that speaks.*
