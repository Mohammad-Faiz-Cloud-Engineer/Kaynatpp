# Kaynat++ Quick Start Guide

Get up and running with Kaynat++ in 5 minutes.

## Installation

### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt install cmake g++ build-essential

# Clone repository
git clone https://github.com/Mohammad-Faiz-Cloud-Engineer/Kaynatpp.git
cd Kaynatpp

# Build
./build.sh

# The executable will be in build/kaynat
```

### macOS
```bash
# Install dependencies
brew install cmake

# Clone and build
git clone https://github.com/Mohammad-Faiz-Cloud-Engineer/Kaynatpp.git
cd Kaynatpp
./build.sh
```

### Windows (WSL)
```bash
# Use Windows Subsystem for Linux
# Follow Linux instructions above
```

## Your First Program

Create a file called `hello.kn`:

```kaynat
begin program.

set name to World.
say Hello, name.

end program.
```

Run it:
```bash
./build/kaynat hello.kn
```

Output:
```
Hello World
```

## Interactive Mode (REPL)

Start the REPL:
```bash
./build/kaynat --repl
```

Try these commands:
```kaynat
>>> set x to 10.
>>> say x.
10
>>> set y to x add 5.
>>> say y.
15
>>> if y is greater than 10 then. say Large. end.
Large
>>> exit
```

## Basic Examples

### Variables
```kaynat
set age to 25.
set name to Alice.
always pi to 3.14159.
say name is age years old.
```

### Math
```kaynat
set x to 10.
set y to 20.
set sum to x add y.
set product to x multiply y.
say Sum:, sum.
say Product:, product.
```

### Conditionals
```kaynat
set score to 85.

if score is greater than 90 then.
    say Grade A.
otherwise if score is greater than 80 then.
    say Grade B.
otherwise.
    say Grade C.
end.
```

### Loops
```kaynat
note Repeat loop.
repeat 5 times.
    say Hello.
end.

note While loop.
set count to 0.
while count is less than 5.
    say count.
    add 1 to count.
end.

note For loop.
loop from 1 to 10.
    say current.
end.
```

### Functions
```kaynat
define a function called greet that takes name.
    say Hello, name.
end.

call greet with Alice.
call greet with Bob.

define a function called add that takes a and b.
    give back a add b.
end.

call add with 10 and 20 and store as result.
say Result:, result.
```

### Lists
```kaynat
set fruits to a list containing apple, banana, cherry.
say Fruits:, fruits.

set numbers to a list containing 1, 2, 3, 4, 5.
say Numbers:, numbers.
```

## Complete Example

Create `calculator.kn`:

```kaynat
begin program.

note Simple calculator.

define a function called add that takes a and b.
    give back a add b.
end.

define a function called subtract that takes a and b.
    give back a subtract b.
end.

define a function called multiply that takes a and b.
    give back a multiply b.
end.

define a function called divide that takes a and b.
    give back a divide b.
end.

set x to 10.
set y to 5.

call add with x and y and store as sum.
call subtract with x and y and store as diff.
call multiply with x and y and store as prod.
call divide with x and y and store as quot.

say x add y equals, sum.
say x subtract y equals, diff.
say x multiply y equals, prod.
say x divide y equals, quot.

end program.
```

Run it:
```bash
./build/kaynat calculator.kn
```

Output:
```
10 add 5 equals 15
10 subtract 5 equals 5
10 multiply 5 equals 50
10 divide 5 equals 2
```

## Built-in Functions

### Math Functions
```kaynat
call sqrt with 16 and store as root.
say Square root of 16 is, root.

call pow with 2 and 10 and store as result.
say 2 to the power 10 is, result.
```

### String Functions
```kaynat
set text to hello world.

call uppercase with text and store as upper.
say Uppercase:, upper.

call lowercase with text and store as lower.
say Lowercase:, lower.
```

## Syntax Rules

1. **Every statement ends with a period (.)**
   ```kaynat
   set x to 10.
   say x.
   ```

2. **Use commas to separate items**
   ```kaynat
   set list to a list containing 1, 2, 3.
   say Hello, World.
   ```

3. **Comments start with "note"**
   ```kaynat
   note This is a comment.
   set x to 10.  note This is also a comment.
   ```

4. **Blocks end with "end."**
   ```kaynat
   if x is greater than 5 then.
       say Large.
   end.
   ```

## Common Patterns

### FizzBuzz
```kaynat
loop from 1 to 100.
    set n to current.
    
    if n remainder 15 is equal to 0 then.
        say FizzBuzz.
    otherwise if n remainder 3 is equal to 0 then.
        say Fizz.
    otherwise if n remainder 5 is equal to 0 then.
        say Buzz.
    otherwise.
        say n.
    end.
end.
```

### Fibonacci
```kaynat
define a function called fibonacci that takes n.
    if n is less than 2 then.
        give back n.
    end.
    
    set n1 to n subtract 1.
    set n2 to n subtract 2.
    
    call fibonacci with n1 and store as fib1.
    call fibonacci with n2 and store as fib2.
    
    give back fib1 add fib2.
end.

loop from 0 to 10.
    call fibonacci with current and store as result.
    say Fibonacci of current is, result.
end.
```

### Factorial
```kaynat
define a function called factorial that takes n.
    if n is equal to 0 then.
        give back 1.
    end.
    
    set prev to n subtract 1.
    call factorial with prev and store as result.
    give back n multiply result.
end.

call factorial with 5 and store as answer.
say Factorial of 5 is, answer.
```

## Next Steps

1. **Read the full documentation**: `docs/01_getting_started.md`
2. **Try the examples**: Browse `examples/` directory
3. **Learn the syntax**: `SYNTAX_QUICK_REFERENCE.md`
4. **Read the story**: `STORY.md`
5. **Explore the language**: `docs/02_core_language.md`

## Getting Help

- **Documentation**: Check the `docs/` directory
- **Examples**: Look at `examples/` for working code
- **Issues**: Report bugs on GitHub
- **Contributing**: See `CONTRIBUTING.md`

## Tips

1. **Start simple** - Begin with variables and print statements
2. **Use the REPL** - Test code interactively before writing files
3. **Read error messages** - They include line numbers and helpful info
4. **Check examples** - See how others have solved similar problems
5. **Write comments** - Use "note" to document your code

## Common Mistakes

### Forgetting the period
```kaynat
set x to 10  ❌ Missing period
set x to 10. ✅ Correct
```

### Wrong keyword order
```kaynat
set to x 10.     ❌ Wrong order
set x to 10.     ✅ Correct
```

### Missing "end"
```kaynat
if x is greater than 5 then.
    say Large.
❌ Missing end.

if x is greater than 5 then.
    say Large.
end. ✅ Correct
```

## Cheat Sheet

```kaynat
note Variables
set x to 10.
always pi to 3.14.

note Math
set sum to x add 5.
set diff to x subtract 3.
set prod to x multiply 2.
set quot to x divide 2.

note Comparison
if x is equal to 10 then.
if x is not equal to 10 then.
if x is greater than 10 then.
if x is less than 10 then.

note Logic
if a and b then.
if a or b then.
if not a then.

note Loops
repeat 5 times.
while x is less than 10.
loop from 1 to 10.

note Functions
define a function called name that takes param.
    give back param.
end.

call name with value and store as result.

note Lists
set list to a list containing 1, 2, 3.

note Output
say Hello, World.
```

---

**Ready to code? Start with `./build/kaynat --repl` and experiment!**

*Write code that reads like English.*

Repository: https://github.com/Mohammad-Faiz-Cloud-Engineer/Kaynatpp
