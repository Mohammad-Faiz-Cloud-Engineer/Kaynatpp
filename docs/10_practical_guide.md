# Practical Guide to Kaynat++

Real-world examples and patterns.

## Table of Contents

1. [Hello World](#hello-world)
2. [Calculator](#calculator)
3. [FizzBuzz](#fizzbuzz)
4. [Fibonacci](#fibonacci)
5. [File Processing](#file-processing)
6. [Data Validation](#data-validation)
7. [Simple Database](#simple-database)
8. [Web Scraper](#web-scraper)
9. [Task Scheduler](#task-scheduler)
10. [Mini Projects](#mini-projects)

---

## Hello World

```kaynat
begin program.
set name to world.
say hello, name.
end program.
```

---

## Calculator

```kaynat
begin program.

define a function called add that takes a and b.
    set result to a.
    add b to result.
    give back result.
end.

define a function called subtract that takes a and b.
    set result to a.
    subtract b from result.
    give back result.
end.

define a function called multiply that takes a and b.
    set result to a.
    multiply result by b.
    give back result.
end.

define a function called divide that takes a and b.
    if b is equal to 0 then.
        raise an error saying cannot divide by zero.
    end.
    set result to a.
    divide result by b.
    give back result.
end.

call add with 10 and 5 and store as sum.
say 10 plus 5 equals, sum.

call multiply with 10 and 5 and store as product.
say 10 times 5 equals, product.

end program.
```

---

## FizzBuzz

```kaynat
begin program.

loop from 1 to 100.
    find the remainder of current divided by 15 and store as rem15.
    if rem15 is equal to 0 then.
        say fizzbuzz.
        skip.
    end.
    
    find the remainder of current divided by 3 and store as rem3.
    if rem3 is equal to 0 then.
        say fizz.
        skip.
    end.
    
    find the remainder of current divided by 5 and store as rem5.
    if rem5 is equal to 0 then.
        say buzz.
        skip.
    end.
    
    say current.
end.

end program.
```

---

## Fibonacci

```kaynat
begin program.

define a function called fibonacci that takes n.
    if n is less than or equal to 1 then.
        give back n.
    end.
    
    subtract 1 from n and store as n1.
    subtract 2 from n and store as n2.
    
    call fibonacci with n1 and store as fib1.
    call fibonacci with n2 and store as fib2.
    
    set result to fib1.
    add fib2 to result.
    give back result.
end.

loop from 0 to 10.
    call fibonacci with current and store as fib.
    say fibonacci of current is fib.
end.

end program.
```

---

## File Processing

```kaynat
begin program.

note. read file.
attempt.
    read the file called data.txt and store as content.
    say file content, content.
if it fails with message then.
    say error reading file, message.
end.

note. write file.
set data to hello from kaynat++.
attempt.
    write data to the file called output.txt.
    say file written successfully.
if it fails with message then.
    say error writing file, message.
end.

note. process file line by line.
attempt.
    read the file called log.txt line by line and store as lines.
    for each line in lines.
        say processing, line.
    end.
if it fails with message then.
    say error processing file, message.
end.

end program.
```

---

## Data Validation

```kaynat
begin program.

define a function called validate_email that takes email.
    check if email contains @ and store as has_at.
    check if email contains . and store as has_dot.
    
    if has_at is true and has_dot is true then.
        give back true.
    end.
    give back false.
end.

define a function called validate_age that takes age.
    if age is less than 0 then.
        give back false.
    end.
    if age is greater than 150 then.
        give back false.
    end.
    give back true.
end.

set email to user@example.com.
call validate_email with email and store as valid.
if valid is true then.
    say email is valid.
otherwise.
    say email is invalid.
end.

set age to 25.
call validate_age with age and store as valid.
if valid is true then.
    say age is valid.
otherwise.
    say age is invalid.
end.

end program.
```

---

## Simple Database

```kaynat
begin program.

note. create database (list of maps).
create a list called database.

note. add record function.
define a function called add_record that takes name and age.
    create a map called record.
    set key name to name in record.
    set key age to age in record.
    add record to database.
end.

note. find record function.
define a function called find_record that takes name.
    for each record in database.
        get key name from record and store as record_name.
        if record_name is equal to name then.
            give back record.
        end.
    end.
    give back nothing.
end.

note. add records.
call add_record with John and 30.
call add_record with Jane and 25.
call add_record with Bob and 35.

note. find and display record.
call find_record with Jane and store as result.
if result is not equal to nothing then.
    get key name from result and store as name.
    get key age from result and store as age.
    say found, name, age years old.
otherwise.
    say record not found.
end.

end program.
```

---

## Task Scheduler

```kaynat
begin program.

note. create task queue.
create a queue called task_queue.

note. add tasks.
enqueue process order into task_queue.
enqueue send email into task_queue.
enqueue update database into task_queue.
enqueue generate report into task_queue.

note. process tasks.
while task_queue is not empty.
    dequeue from task_queue and store as task.
    say processing task, task.
    note. simulate work.
    say task completed, task.
end.

say all tasks completed.

end program.
```

---

## Mini Project: Student Grade Manager

```kaynat
begin program.

note. student database.
create a list called students.

note. add student function.
define a function called add_student that takes name, id, and grade.
    create a map called student.
    set key name to name in student.
    set key id to id in student.
    set key grade to grade in student.
    add student to students.
    say added student, name.
end.

note. calculate average function.
define a function called calculate_average that takes nothing.
    if students is empty then.
        give back 0.
    end.
    
    set total to 0.
    for each student in students.
        get key grade from student and store as grade.
        add grade to total.
    end.
    
    find the length of students and store as count.
    divide total by count.
    give back total.
end.

note. find top student function.
define a function called find_top_student that takes nothing.
    if students is empty then.
        give back nothing.
    end.
    
    get item at position 0 in students and store as top.
    get key grade from top and store as top_grade.
    
    for each student in students.
        get key grade from student and store as grade.
        if grade is greater than top_grade then.
            set top to student.
            set top_grade to grade.
        end.
    end.
    
    give back top.
end.

note. add students.
call add_student with John Doe and S001 and 85.
call add_student with Jane Smith and S002 and 92.
call add_student with Bob Johnson and S003 and 78.
call add_student with Alice Brown and S004 and 95.

note. calculate and display average.
call calculate_average and store as avg.
say class average, avg.

note. find and display top student.
call find_top_student and store as top.
if top is not equal to nothing then.
    get key name from top and store as name.
    get key grade from top and store as grade.
    say top student, name, with grade, grade.
end.

end program.
```

---

## Best Practices

1. **Use functions for reusable code**
2. **Handle errors with try-catch**
3. **Validate input data**
4. **Use meaningful variable names**
5. **Add comments for complex logic**
6. **Break large programs into smaller functions**
7. **Test edge cases**

---

All examples shown here will work in Kaynat++ once fully implemented.
