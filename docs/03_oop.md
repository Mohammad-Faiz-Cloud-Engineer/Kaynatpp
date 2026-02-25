# Object-Oriented Programming in Kaynat++

Complete guide to OOP in Kaynat++.

## Table of Contents

1. [Introduction](#introduction)
2. [Blueprints (Classes)](#blueprints-classes)
3. [Properties](#properties)
4. [Methods](#methods)
5. [Initializers](#initializers)
6. [Creating Instances](#creating-instances)
7. [Encapsulation](#encapsulation)
8. [Inheritance](#inheritance)
9. [Polymorphism](#polymorphism)
10. [Abstract Blueprints](#abstract-blueprints)
11. [Contracts (Interfaces)](#contracts-interfaces)
12. [Real-World Examples](#real-world-examples)

---

## Introduction

Kaynat++ supports object-oriented programming through **blueprints** (classes). A blueprint defines the structure and behavior of objects.

---

## Blueprints (Classes)

### Basic Blueprint

```kaynat
define a blueprint called animal.
    it has name.
    it has sound.
end.
```

### Blueprint with Methods

```kaynat
define a blueprint called animal.
    it has name.
    it has sound.
    
    to speak, do.
        say my name, says, my sound.
    end.
end.
```

---

## Properties

Properties are the data that objects hold.

```kaynat
define a blueprint called person.
    it has name.
    it has age.
    it has email.
end.
```

---

## Methods

Methods are functions that belong to a blueprint.

```kaynat
define a blueprint called calculator.
    it has result.
    
    to add, take value.
        add value to my result.
    end.
    
    to subtract, take value.
        subtract value from my result.
    end.
    
    to get_result, do.
        give back my result.
    end.
end.
```

---

## Initializers

Initializers set up new objects when they're created.

```kaynat
define a blueprint called animal.
    it has name.
    it has sound.
    it has age.
    
    to initialize, take name, sound, and age.
        set my name to name.
        set my sound to sound.
        set my age to age.
    end.
    
    to speak, do.
        say my name, says, my sound.
    end.
end.
```

---

## Creating Instances

### Basic Instance Creation

```kaynat
create a new animal with Whiskers, meow, and 3, and store as cat.
call speak on cat.
```

### Accessing Properties

```kaynat
create a new animal with Buddy, woof, and 5, and store as dog.
say dog name is, dog name.
say dog age is, dog age.
```

### Calling Methods

```kaynat
create a new calculator with 0, and store as calc.
call add with 10 on calc.
call add with 5 on calc.
call get_result on calc and store as result.
say result.
```

---

## Encapsulation

### Private Properties

```kaynat
define a blueprint called bank_account.
    it has private balance.
    it has owner.
    
    to initialize, take owner and starting_balance.
        set my owner to owner.
        set my private balance to starting_balance.
    end.
    
    to deposit, take amount.
        if amount is less than or equal to 0 then.
            raise an error saying deposit amount must be positive.
        end.
        add amount to my private balance.
    end.
    
    to withdraw, take amount.
        if amount is greater than my private balance then.
            raise an error saying insufficient funds.
        end.
        subtract amount from my private balance.
    end.
    
    to get_balance, do.
        give back my private balance.
    end.
end.
```

### Using Encapsulation

```kaynat
create a new bank_account with John and 1000, and store as account.
call deposit with 500 on account.
call withdraw with 200 on account.
call get_balance on account and store as balance.
say balance is, balance.
```

---

## Inheritance

### Basic Inheritance

```kaynat
define a blueprint called dog that extends animal.
    to initialize, take name and age.
        call parent initialize with name, woof, and age.
    end.
    
    to speak, do.
        say my name, barks loudly.
    end.
end.
```

### Using Inherited Blueprints

```kaynat
create a new dog with Buddy and 5, and store as my_dog.
call speak on my_dog.
```

### Multi-Level Inheritance

```kaynat
define a blueprint called animal.
    it has name.
    
    to initialize, take name.
        set my name to name.
    end.
    
    to move, do.
        say my name, is moving.
    end.
end.

define a blueprint called mammal that extends animal.
    it has fur_color.
    
    to initialize, take name and fur_color.
        call parent initialize with name.
        set my fur_color to fur_color.
    end.
end.

define a blueprint called dog that extends mammal.
    to initialize, take name and fur_color.
        call parent initialize with name and fur_color.
    end.
    
    to bark, do.
        say my name, says woof.
    end.
end.
```

---

## Polymorphism

### Method Overriding

```kaynat
define a blueprint called shape.
    to calculate_area, do.
        give back 0.
    end.
end.

define a blueprint called circle that extends shape.
    it has radius.
    
    to initialize, take radius.
        set my radius to radius.
    end.
    
    to calculate_area, do.
        always set pi as 3.14159.
        set result to pi.
        multiply result by my radius.
        multiply result by my radius.
        give back result.
    end.
end.

define a blueprint called rectangle that extends shape.
    it has width.
    it has height.
    
    to initialize, take width and height.
        set my width to width.
        set my height to height.
    end.
    
    to calculate_area, do.
        set result to my width.
        multiply result by my height.
        give back result.
    end.
end.
```

### Using Polymorphism

```kaynat
create a new circle with 5, and store as c.
create a new rectangle with 4 and 6, and store as r.

call calculate_area on c and store as circle_area.
call calculate_area on r and store as rect_area.

say circle area is, circle_area.
say rectangle area is, rect_area.
```

---

## Abstract Blueprints

Abstract blueprints define methods that must be implemented by child blueprints.

```kaynat
define an abstract blueprint called shape.
    to calculate_area, do.
        this must be implemented.
    end.
    
    to calculate_perimeter, do.
        this must be implemented.
    end.
end.

define a blueprint called circle that extends shape.
    it has radius.
    
    to initialize, take radius.
        set my radius to radius.
    end.
    
    to calculate_area, do.
        always set pi as 3.14159.
        set result to pi.
        multiply result by my radius.
        multiply result by my radius.
        give back result.
    end.
    
    to calculate_perimeter, do.
        always set pi as 3.14159.
        set result to 2.
        multiply result by pi.
        multiply result by my radius.
        give back result.
    end.
end.
```

---

## Contracts (Interfaces)

Contracts define a set of methods that blueprints must implement.

```kaynat
define a contract called printable.
    it requires a function called print_details.
end.

define a blueprint called book that implements printable.
    it has title.
    it has author.
    
    to initialize, take title and author.
        set my title to title.
        set my author to author.
    end.
    
    to print_details, do.
        say title, my title.
        say author, my author.
    end.
end.
```

---

## Real-World Examples

### Example 1: Student Management System

```kaynat
define a blueprint called student.
    it has name.
    it has student_id.
    it has grades.
    
    to initialize, take name and student_id.
        set my name to name.
        set my student_id to student_id.
        set my grades to a list.
    end.
    
    to add_grade, take grade.
        add grade to my grades.
    end.
    
    to calculate_average, do.
        if my grades is empty then.
            give back 0.
        end.
        
        set total to 0.
        for each grade in my grades.
            add grade to total.
        end.
        
        find the length of my grades and store as count.
        divide total by count.
        give back total.
    end.
    
    to print_report, do.
        say student name, my name.
        say student id, my student_id.
        call calculate_average and store as avg.
        say average grade, avg.
    end.
end.

note. using the student blueprint.
create a new student with John Doe and S001, and store as student1.
call add_grade with 85 on student1.
call add_grade with 90 on student1.
call add_grade with 78 on student1.
call print_report on student1.
```

### Example 2: Bank Account System

```kaynat
define a blueprint called bank_account.
    it has private balance.
    it has account_number.
    it has owner.
    
    to initialize, take account_number, owner, and initial_balance.
        set my account_number to account_number.
        set my owner to owner.
        set my private balance to initial_balance.
    end.
    
    to deposit, take amount.
        if amount is less than or equal to 0 then.
            raise an error saying deposit amount must be positive.
        end.
        add amount to my private balance.
        say deposited, amount.
    end.
    
    to withdraw, take amount.
        if amount is less than or equal to 0 then.
            raise an error saying withdrawal amount must be positive.
        end.
        if amount is greater than my private balance then.
            raise an error saying insufficient funds.
        end.
        subtract amount from my private balance.
        say withdrew, amount.
    end.
    
    to get_balance, do.
        give back my private balance.
    end.
    
    to print_statement, do.
        say account number, my account_number.
        say owner, my owner.
        say balance, my private balance.
    end.
end.

note. using the bank account.
create a new bank_account with ACC001, John Doe, and 1000, and store as account.
call deposit with 500 on account.
call withdraw with 200 on account.
call print_statement on account.
```

### Example 3: Inventory Management

```kaynat
define a blueprint called product.
    it has name.
    it has price.
    it has quantity.
    
    to initialize, take name, price, and quantity.
        set my name to name.
        set my price to price.
        set my quantity to quantity.
    end.
    
    to restock, take amount.
        add amount to my quantity.
    end.
    
    to sell, take amount.
        if amount is greater than my quantity then.
            raise an error saying not enough stock.
        end.
        subtract amount from my quantity.
    end.
    
    to get_value, do.
        set value to my price.
        multiply value by my quantity.
        give back value.
    end.
end.

define a blueprint called inventory.
    it has products.
    
    to initialize, do.
        set my products to a list.
    end.
    
    to add_product, take product.
        add product to my products.
    end.
    
    to total_value, do.
        set total to 0.
        for each product in my products.
            call get_value on product and store as value.
            add value to total.
        end.
        give back total.
    end.
end.

note. using the inventory system.
create a new product with Laptop, 1000, and 10, and store as laptop.
create a new product with Mouse, 25, and 50, and store as mouse.

create a new inventory and store as inv.
call add_product with laptop on inv.
call add_product with mouse on inv.

call total_value on inv and store as total.
say total inventory value, total.
```

---

## Best Practices

1. **Use meaningful blueprint names**
   ```kaynat
   define a blueprint called user_account.  note. good.
   define a blueprint called x.             note. bad.
   ```

2. **Keep blueprints focused**
   - Each blueprint should have a single, clear purpose
   - Don't create "god objects" that do everything

3. **Use encapsulation**
   - Make properties private when they shouldn't be accessed directly
   - Provide methods to interact with private data

4. **Favor composition over inheritance**
   - Don't create deep inheritance hierarchies
   - Use composition when objects "have a" relationship

5. **Document your blueprints**
   ```kaynat
   note. represents a user in the system.
   note. handles authentication and profile management.
   define a blueprint called user.
       note. implementation.
   end.
   ```

---

This is the complete OOP guide for Kaynat++. All examples will work once the OOP system is implemented.
