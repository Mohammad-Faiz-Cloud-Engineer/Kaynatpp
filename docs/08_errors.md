# Error Reference

Complete guide to errors in Kaynat++.

## Error Types

### 1. Lexer Error

**When**: Invalid characters or tokens in source code.

**Example**:
```kaynat
set x to 10@.  note. @ is invalid.
```

**Error**: `Lexer error at line 1: Unexpected character '@'`

**Fix**: Remove invalid characters.

---

### 2. Parser Error

**When**: Syntax doesn't match grammar rules.

**Example**:
```kaynat
set x to.  note. missing value.
```

**Error**: `Parser error at line 1: Expected expression after 'to'`

**Fix**: Provide complete syntax.

---

### 3. Runtime Error

**When**: Error during program execution.

**Example**:
```kaynat
say undefined_variable.
```

**Error**: `Runtime error at line 1: Undefined variable 'undefined_variable'`

**Fix**: Define variable before use.

---

### 4. Type Error

**When**: Operation on incompatible types.

**Example**:
```kaynat
set x to 10.
add hello to x.
```

**Error**: `Type error at line 2: Cannot add String to Integer`

**Fix**: Use compatible types.

---

### 5. Division By Zero Error

**When**: Dividing by zero.

**Example**:
```kaynat
set x to 10.
divide x by 0.
```

**Error**: `Division by zero at line 2`

**Fix**: Check divisor before dividing.

---

### 6. Index Error

**When**: Accessing invalid list index.

**Example**:
```kaynat
set list to a list containing 1, 2, 3.
get item at position 10 in list and store as item.
```

**Error**: `Index error at line 2: Index 10 out of bounds for size 3`

**Fix**: Check list size before accessing.

---

### 7. File Error

**When**: File operation fails.

**Example**:
```kaynat
read the file called nonexistent.txt and store as content.
```

**Error**: `File error at line 1: Cannot access 'nonexistent.txt' - file not found`

**Fix**: Check file exists before reading.

---

### 8. Undefined Error

**When**: Using undefined variable.

**Example**:
```kaynat
say x.
```

**Error**: `Undefined variable at line 1: 'x' has not been defined`

**Fix**: Define variable first.

---

## Error Handling

### Try-Catch

```kaynat
attempt.
    divide 10 by 0 and store as result.
if it fails with message then.
    say error occurred, message.
end.
```

### Try-Catch-Finally

```kaynat
attempt.
    read the file called data.txt and store as content.
if it fails with message then.
    say could not read file, message.
always after.
    say cleanup complete.
end.
```

### Raising Errors

```kaynat
if age is less than 0 then.
    raise an error saying age cannot be negative.
end.
```

---

## Common Error Patterns

### Pattern 1: Undefined Variable

```kaynat
note. wrong.
say x.

note. correct.
set x to 10.
say x.
```

### Pattern 2: Type Mismatch

```kaynat
note. wrong.
set x to 10.
add hello to x.

note. correct.
set x to 10.
add 5 to x.
```

### Pattern 3: Index Out of Bounds

```kaynat
note. wrong.
set list to a list containing 1, 2, 3.
get item at position 10 in list and store as item.

note. correct.
set list to a list containing 1, 2, 3.
find the length of list and store as len.
if 10 is less than len then.
    get item at position 10 in list and store as item.
end.
```

### Pattern 4: File Not Found

```kaynat
note. wrong.
read the file called data.txt and store as content.

note. correct.
check if the file called data.txt exists and store as exists.
if exists is true then.
    read the file called data.txt and store as content.
otherwise.
    say file not found.
end.
```

---

All error types and handling shown here will work in Kaynat++.
