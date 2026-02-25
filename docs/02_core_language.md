# Core Language Reference

Complete reference for the Kaynat++ programming language.

## Table of Contents

1. [Program Structure](#program-structure)
2. [Comments](#comments)
3. [Variables](#variables)
4. [Data Types](#data-types)
5. [Arithmetic Operations](#arithmetic-operations)
6. [String Operations](#string-operations)
7. [Comparison and Logic](#comparison-and-logic)
8. [Conditionals](#conditionals)
9. [Loops](#loops)
10. [Functions](#functions)
11. [Lists](#lists)
12. [Dictionaries](#dictionaries)
13. [Input and Output](#input-and-output)
14. [File Operations](#file-operations)
15. [Error Handling](#error-handling)
16. [Type System](#type-system)

---

## Program Structure

Every Kaynat++ program must start with `begin program.` and end with `end program.`

```kaynat
begin program.
    note. your code goes here.
end program.
```

---

## Comments

### Single-line Comments

```kaynat
note. this is a single-line comment.
set x to 10.  note. comments can go after statements too.
```

### Multi-line Comments

```kaynat
begin note.
this is a multi-line comment.
it can span multiple lines.
useful for documentation.
end note.
```

---

## Variables

### Declaring Variables

```kaynat
set x to 10.
set name to Kaynat++.
set price to 9.99.
set active to true.
```

### Alternative Syntax

```kaynat
let age be 21.
define title as developer.
```

### Constants

```kaynat
always set pi as 3.14159.
always set max_users as 100.
```

### Modifying Variables

```kaynat
set count to 0.
change count to 10.
add 5 to count.
```

### Deleting Variables

```kaynat
set temp to 42.
forget temp.
```

### Checking Existence

```kaynat
check if score exists.
```

---

## Data Types

### Integer

```kaynat
set count to 25.
set negative to negative 10.
```

### Float

```kaynat
set price to 9.99.
set temperature to negative 5.5.
```

### Boolean

```kaynat
set active to true.
set verified to false.
```

### Character

```kaynat
set letter to a.
set symbol to x.
```

### String

```kaynat
set name to Kaynat++.
set message to hello, world.
```

### Null

```kaynat
set result to nothing.
```

### List

```kaynat
set fruits to a list containing apple, banana, cherry.
set numbers to a list containing 1, 2, 3, 4, 5.
```

### Dictionary

```kaynat
create a map called person.
set key name to John in person.
set key age to 30 in person.
```

### Big Number

```kaynat
set huge to a big number 99999999999999999999999999.
```

---

## Arithmetic Operations

### Basic Operations

```kaynat
set x to 10.
add 5 to x.           note. x = 15.
subtract 3 from x.    note. x = 12.
multiply x by 2.      note. x = 24.
divide x by 4.        note. x = 6.
```

### Advanced Operations

```kaynat
find the remainder of 17 divided by 5 and store as rem.
find the integer division of 17 by 5 and store as quot.
raise 2 to the power 10 and store as result.
find the square root of 144 and store as root.
find the absolute value of negative 42 and store as abs_val.
```

### Rounding

```kaynat
set price to 9.876.
round price to 2 decimal places.
find the ceiling of 4.2 and store as ceil_val.
find the floor of 4.8 and store as floor_val.
```

### Trigonometry

```kaynat
set angle to 45.
find the sine of angle and store as sin_val.
find the cosine of angle and store as cos_val.
find the tangent of angle and store as tan_val.
```

### Logarithms

```kaynat
find the logarithm of 1000 in base 10 and store as log_val.
```

### Complex Expressions

```kaynat
set width to 10.
set height to 20.
set offset to 5.
add the product of width and height to offset.
```

---

## String Operations

### Concatenation

```kaynat
set first_name to John.
set last_name to Doe.
join first_name and last_name and store as full_name.
```

### Length

```kaynat
set message to hello.
find the length of message and store as len.
```

### Case Conversion

```kaynat
set name to kaynat++.
convert name to uppercase and store as upper.
convert name to lowercase and store as lower.
```

### Trimming

```kaynat
set input to   hello   .
trim whitespace from input and store as trimmed.
```

### Checking Patterns

```kaynat
set title to Hello World.
check if title starts with Hello.
check if filename ends with txt.
check if description contains error.
```

### Replacement

```kaynat
set sentence to hello, world.
replace comma with period in sentence and store as fixed.
```

### Splitting

```kaynat
set sentence to hello world kaynat.
split sentence by space and store as words.
```

### Position

```kaynat
set greeting to hello world.
find the position of world in greeting and store as pos.
```

### Substring

```kaynat
set name to Kaynat++.
take characters from 0 to 5 in name and store as short_name.
```

### Reversal

```kaynat
set message to hello.
reverse the string message and store as reversed.
```

### Repetition

```kaynat
set star to *.
repeat star 10 times and store as border.
```

---

## Comparison and Logic

### Comparison Operators

```kaynat
if x is equal to 10 then.
if x is not equal to 10 then.
if x is greater than 10 then.
if x is less than 10 then.
if x is greater than or equal to 10 then.
if x is less than or equal to 10 then.
```

### Logical Operators

```kaynat
if active is true and verified is true then.
if input is empty or count is 0 then.
if not finished then.
```

### Type Checking

```kaynat
if x is a number then.
if name is a string then.
if fruits is a list then.
if person is a map then.
```

### Membership

```kaynat
if fruits contains apple then.
if score exists then.
```

---

## Conditionals

### If-Then-End

```kaynat
if age is greater than 18 then.
    say you are an adult.
end.
```

### If-Otherwise-End

```kaynat
if age is greater than 18 then.
    say you are an adult.
otherwise.
    say you are a minor.
end.
```

### If-Otherwise If-Otherwise-End

```kaynat
if age is greater than 18 then.
    say you are an adult.
otherwise if age is equal to 18 then.
    say just turned adult.
otherwise.
    say you are a minor.
end.
```

### Switch-Case (Check Value)

```kaynat
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

---

## Loops

### Repeat N Times

```kaynat
repeat 10 times.
    say hello.
end.
```

### While Loop

```kaynat
set count to 0.
while count is less than 100.
    add 1 to count.
end.
```

### Do-Until Loop

```kaynat
do.
    ask the user for response.
until response is equal to yes.
```

### For-Each Loop

```kaynat
set fruits to a list containing apple, banana, cherry.
for each fruit in fruits.
    say fruit.
end.
```

### Range Loop

```kaynat
loop from 1 to 100.
    say current.
end.

loop from 1 to 100 stepping by 5.
    say current.
end.
```

### Loop Control

```kaynat
loop from 1 to 100.
    if current is equal to 50 then.
        stop.  note. break out of loop.
    end.
    if current is equal to 25 then.
        skip.  note. continue to next iteration.
    end.
    say current.
end.
```

---

## Functions

### Defining Functions

```kaynat
define a function called greet that takes name.
    say hello, name.
end.
```

### Multiple Parameters

```kaynat
define a function called add that takes a and b.
    set sum to a.
    add b to sum.
    give back sum.
end.
```

### Calling Functions

```kaynat
call greet with Kaynat++.
call add with 10 and 20 and store as result.
```

### Recursive Functions

```kaynat
define a function called factorial that takes n.
    if n is equal to 0 then.
        give back 1.
    end.
    subtract 1 from n and store as prev.
    call factorial with prev and store as sub_result.
    set result to n.
    multiply result by sub_result.
    give back result.
end.
```

### Inline Functions

```kaynat
define an inline function that takes x and gives back x multiplied by x, and store as square.
call square with 5 and store as result.
```

---

## Lists

### Creating Lists

```kaynat
create a list called tasks.
set fruits to a list containing apple, banana, cherry.
```

### Adding Elements

```kaynat
add wash dishes to tasks.
add buy milk to the front of tasks.
insert clean room at position 2 in tasks.
```

### Removing Elements

```kaynat
remove wash dishes from tasks.
remove item at position 0 from tasks.
```

### Accessing Elements

```kaynat
get item at position 1 in tasks and store as first_task.
```

### List Properties

```kaynat
find the length of tasks and store as count.
check if tasks is empty.
```

### Sorting

```kaynat
sort tasks ascending.
sort tasks descending.
```

### Reversing

```kaynat
reverse tasks.
```

### Joining

```kaynat
join tasks with comma and store as task_string.
```

### Filtering

```kaynat
filter tasks where item starts with buy and store as shopping.
```

### Mapping

```kaynat
map tasks using uppercase and store as upper_tasks.
```

### Reducing

```kaynat
reduce tasks using join with and and store as summary.
```

### Copying

```kaynat
copy tasks and store as backup.
```

### Flattening

```kaynat
flatten nested_list and store as flat.
```

---

## Dictionaries

### Creating Dictionaries

```kaynat
create a map called profile.
```

### Setting Values

```kaynat
set key name to Kaynat++ in profile.
set key age to 1 in profile.
```

### Getting Values

```kaynat
get key name from profile and store as username.
```

### Removing Keys

```kaynat
remove key age from profile.
```

### Checking Keys

```kaynat
check if key email exists in profile.
```

### Listing Keys and Values

```kaynat
list all keys in profile and store as fields.
list all values in profile and store as field_values.
```

### Iterating

```kaynat
for each key and value in profile.
    say key is value.
end.
```

---

## Input and Output

### Output

```kaynat
say hello, world.
print total.
show the value of score.
say my name is name and I am age years old.
```

### Input

```kaynat
ask the user for name.
read a number from the user and store as age.
```

---

## File Operations

### Reading Files

```kaynat
read the file called data.txt and store as content.
read the file called log.txt line by line and store as lines.
```

### Writing Files

```kaynat
write hello world to the file called output.txt.
append new entry to the file called log.txt.
```

### File Checks

```kaynat
check if the file called config.txt exists.
```

### Deleting Files

```kaynat
delete the file called temp.txt.
```

---

## Error Handling

### Try-Catch

```kaynat
attempt.
    divide 10 by 0 and store as result.
if it fails with message then.
    say something went wrong, message.
end.
```

### Try-Catch-Finally

```kaynat
attempt.
    divide 10 by 0 and store as result.
if it fails with message then.
    say error occurred, message.
always after.
    say cleanup complete.
end.
```

### Raising Errors

```kaynat
raise an error saying the value cannot be negative.
```

### Custom Error Types

```kaynat
define an error type called validation error.
```

---

## Type System

### Type Checking

```kaynat
check the type of score and store as type_name.
```

### Type Conversion

```kaynat
convert age to text and store as age_string.
turn input into a number and store as num.
convert list to string and store as str.
```

### Type Predicates

```kaynat
if score is a number then.
if name is a string then.
if items is a list then.
if data is a map then.
```

---

## Best Practices

1. **Use descriptive variable names**
   ```kaynat
   set user_count to 0.  note. good.
   set x to 0.           note. bad.
   ```

2. **Add comments for complex logic**
   ```kaynat
   note. calculate compound interest.
   set result to principal.
   multiply result by rate.
   ```

3. **Use constants for fixed values**
   ```kaynat
   always set max_retries as 3.
   always set timeout as 30.
   ```

4. **Handle errors appropriately**
   ```kaynat
   attempt.
       read the file called data.txt and store as content.
   if it fails with message then.
       say could not read file, message.
   end.
   ```

5. **Break complex operations into functions**
   ```kaynat
   define a function called validate_input that takes data.
       note. validation logic here.
   end.
   ```

---

## Common Patterns

### Counter Pattern

```kaynat
set count to 0.
repeat 10 times.
    add 1 to count.
end.
```

### Accumulator Pattern

```kaynat
set total to 0.
for each number in numbers.
    add number to total.
end.
```

### Guard Pattern

```kaynat
if input is empty then.
    say input cannot be empty.
    give back nothing.
end.
```

### Iterator Pattern

```kaynat
set index to 0.
while index is less than length.
    get item at position index in list and store as item.
    say item.
    add 1 to index.
end.
```

---

This is the complete core language reference. Every example shown here will work in Kaynat++ once the interpreter is fully implemented.
