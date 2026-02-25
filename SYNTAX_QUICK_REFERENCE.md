# Kaynat++ Syntax Quick Reference

## Program Structure

```
begin program.
    note. your code here.
end program.
```

## Comments

```
note. single line comment.

begin note.
multi-line comment
can span multiple lines.
end note.
```

## Variables

```
set x to 10.                          # Variable
let age be 21.                        # Alternative syntax
define title as developer.            # Alternative syntax
always set pi as 3.14159.             # Constant
change x to 20.                       # Modify variable
forget x.                             # Delete variable
check if x exists.                    # Check existence
```

## Data Types

```
set count to 25.                      # Integer
set price to 9.99.                    # Float
set temperature to negative 10.       # Negative number
set active to true.                   # Boolean (true/false)
set letter to a.                      # Character
set name to Kaynat++.                 # String
set result to nothing.                # Null
set fruits to a list containing apple, banana, cherry.  # List
set person to a map.                  # Dictionary
set huge to a big number 99999999999999999999.  # Big integer
```

## Arithmetic

```
add 5 to x.                           # x += 5
subtract 3 from x.                    # x -= 3
multiply x by 2.                      # x *= 2
divide x by 4.                        # x /= 4
find the remainder of x divided by 3 and store as rem.
find the integer division of x by 4 and store as quot.
raise 2 to the power 10 and store as result.
find the square root of 144 and store as root.
find the absolute value of negative 42 and store as abs_val.
round price to 2 decimal places.
find the ceiling of 4.2 and store as ceil_val.
find the floor of 4.8 and store as floor_val.
find the logarithm of 1000 in base 10 and store as log_val.
find the sine of angle and store as sin_val.
find the cosine of angle and store as cos_val.
find the tangent of angle and store as tan_val.
```

## String Operations

```
join first name and last name and store as full name.
find the length of message and store as len.
convert name to uppercase and store as upper.
convert name to lowercase and store as lower.
trim whitespace from input and store as trimmed.
check if title starts with Hello.
check if filename ends with txt.
replace comma with period in sentence and store as fixed.
split sentence by space and store as words.
find the position of world in greeting and store as pos.
take characters from 0 to 5 in name and store as short name.
reverse the string message and store as reversed.
repeat star 10 times and store as border.
check if description contains error.
```

## Comparison

```
if x is equal to 10 then.
if x is not equal to 10 then.
if x is greater than 10 then.
if x is less than 10 then.
if x is greater than or equal to 10 then.
if x is less than or equal to 10 then.
```

## Logic

```
if active is true and verified is true then.
if input is empty or count is 0 then.
if not finished then.
```

## Type Checking

```
if x is a number then.
if name is a string then.
if fruits is a list then.
if person is a map then.
```

## Conditionals

```
if age is greater than 18 then.
    say you are an adult.
otherwise if age is equal to 18 then.
    say just turned adult.
otherwise.
    say you are a minor.
end.
```

## Switch/Case

```
check value of day.
    when Monday do.
        say start of the week.
    end.
    when Friday do.
        say almost the weekend.
    end.
    by default do.
        say a regular day.
    end.
end.
```

## Loops

```
repeat 10 times.
    say hello.
end.

while count is less than 100.
    add 1 to count.
end.

do.
    ask the user for response.
until response is equal to yes.

for each fruit in fruits.
    say fruit.
end.

loop from 1 to 100 stepping by 5.
    say current.
end.

stop.                                 # Break
skip.                                 # Continue
```

## Functions

```
define a function called greet that takes name and age.
    say hello, name, you are age years old.
end.

call greet with Kaynat++ and 21.

define a function called add that takes a and b.
    set sum to a.
    add b to sum.
    give back sum.
end.

call add with 10 and 20 and store as result.

define an inline function that takes x and gives back x multiplied by x, and store as square.
```

## Lists

```
create a list called tasks.
add wash dishes to tasks.
add buy milk to the front of tasks.
insert clean room at position 2 in tasks.
remove wash dishes from tasks.
remove item at position 0 from tasks.
get item at position 1 in tasks and store as first task.
find the length of tasks and store as count.
sort tasks ascending.
sort tasks descending.
reverse tasks.
join tasks with comma and store as task string.
filter tasks where item starts with buy and store as shopping.
map tasks using uppercase and store as upper tasks.
check if tasks is empty.
copy tasks and store as backup.
```

## Dictionaries

```
create a map called profile.
set key name to Kaynat++ in profile.
get key name from profile and store as username.
remove key age from profile.
check if key email exists in profile.
list all keys in profile and store as fields.
list all values in profile and store as field values.

for each key and value in profile.
    say key is value.
end.
```

## Input/Output

```
ask the user for name.
read a number from the user and store as age.
say hello, world.
print total.
show the value of score.
say my name is name and I am age years old.
```

## File System

```
read the file called data.txt and store as content.
read the file called log.txt line by line and store as lines.
write hello world to the file called output.txt.
append new entry to the file called log.txt.
check if the file called config.txt exists.
delete the file called temp.txt.
```

## Error Handling

```
attempt.
    divide 10 by 0 and store as result.
if it fails with message then.
    say something went wrong, message.
always after.
    say cleanup complete.
end.

raise an error saying the value cannot be negative.
define an error type called validation error.
```

## Type Conversion

```
check the type of score and store as type name.
convert age to text and store as age string.
turn input into a number and store as num.
```

## Object-Oriented Programming

```
define a blueprint called animal.
    it has name.
    it has sound.
    
    to initialize, take name and sound.
        set my name to name.
        set my sound to sound.
    end.
    
    to speak, do.
        say my name, says, my sound.
    end.
end.

create a new animal with Whiskers and meow, and store as cat.
call speak on cat.

define a blueprint called dog that extends animal.
    to initialize, take name.
        call parent initialize with name and woof.
    end.
    
    to speak, do.
        say my name, barks loudly.
    end.
end.
```

## Data Structures

```
create a stack called history.
push page one onto history.
pop from history and store as last page.
peek at history and store as top.

create a queue called requests.
enqueue task one into requests.
dequeue from requests and store as next task.

create a binary search tree called bst.
insert 50 into bst.
search for 30 in bst and store as found.
traverse bst inorder and store as sorted values.

create a graph called network.
add node city a to network.
add edge from city a to city b with weight 10 in network.
find the shortest path from city a to city b in network using dijkstra.

sort numbers using quick sort and store as sorted.
search for 42 in sorted numbers using binary search and store as index.
```

## GUI Programming

```
create a window called main window.
set the title of main window to Kaynat++ App.
set the width of main window to 800.
set the height of main window to 600.
show main window.

create a label called greeting label.
set the text of greeting label to Hello, Kaynat++.
place greeting label at row 0 and column 0 in main window.

create a button called submit button.
set the text of submit button to Submit.
set the action of submit button to the function called on submit.
place submit button at row 1 and column 0 in main window.

create a text input called name input.
set the placeholder of name input to Enter your name.
place name input at row 0 and column 1 in main window.

when submit button is clicked, call on submit.
```

## Concurrency

```
run fetch user data in the background and call it data task.
wait for data task to finish.
run data task and save task at the same time and wait for both.

when data task finishes, do.
    say data loaded.
end.

set a timer for 3 seconds and then call refresh.
cancel the timer called refresh timer.
```

## Modules

```
bring in the file called utils.
use the module named string tools.
export the function called calculate total.
```

## Keywords Summary

### Variables
set, let, define, always, change, forget, check, exists

### Arithmetic
add, subtract, multiply, divide, find, raise, power, square, root, absolute, value, round, ceiling, floor, logarithm, sine, cosine, tangent, product, remainder

### Comparison
is, equal, not, greater, less, than, or, and, empty

### Control Flow
if, then, otherwise, end, when, do, by, default, repeat, times, while, until, for, each, in, loop, from, to, stepping, stop, skip

### Functions
function, called, that, takes, give, back, call, with, inline, gives

### Collections
create, list, map, containing, insert, at, remove, get, item, sort, ascending, descending, filter, where, reduce, using, copy

### I/O
ask, user, read, say, print, show

### Files
file, line, write, append, delete

### Errors
attempt, it, fails, message, after, raise, error, saying

### Types
number, text, type, convert, turn, into

### OOP
blueprint, has, initialize, my, new, on, extends, parent, abstract, this, must, be, implemented, contract, requires, private

### Program
begin, program, note

## Punctuation

- **Period (.)**: Ends every statement
- **Comma (,)**: Separates items in lists or parameters

## Reserved Words

true, false, nothing, negative

---

*Write code that reads like English.*
