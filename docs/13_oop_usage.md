# OOP Usage Guide

Practical examples of object-oriented programming.

## Example 1: Bank Account System

```kaynat
begin program.

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
            raise an error saying amount must be positive.
        end.
        add amount to my private balance.
        say deposited, amount.
    end.
    
    to withdraw, take amount.
        if amount is greater than my private balance then.
            raise an error saying insufficient funds.
        end.
        subtract amount from my private balance.
        say withdrew, amount.
    end.
    
    to get_balance, do.
        give back my private balance.
    end.
end.

note. create account.
create a new bank_account with ACC001, John Doe, and 1000, and store as account.

note. perform transactions.
call deposit with 500 on account.
call withdraw with 200 on account.

note. check balance.
call get_balance on account and store as balance.
say current balance, balance.

end program.
```

## Example 2: Student Management

```kaynat
begin program.

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
        say student, my name.
        say id, my student_id.
        call calculate_average and store as avg.
        say average, avg.
    end.
end.

note. create students.
create a new student with John Doe and S001, and store as student1.
call add_grade with 85 on student1.
call add_grade with 90 on student1.
call add_grade with 78 on student1.

create a new student with Jane Smith and S002, and store as student2.
call add_grade with 92 on student2.
call add_grade with 88 on student2.
call add_grade with 95 on student2.

note. print reports.
call print_report on student1.
call print_report on student2.

end program.
```

## Example 3: Shape Hierarchy

```kaynat
begin program.

define an abstract blueprint called shape.
    to calculate_area, do.
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
        set area to pi.
        multiply area by my radius.
        multiply area by my radius.
        give back area.
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
        set area to my width.
        multiply area by my height.
        give back area.
    end.
end.

note. create shapes.
create a new circle with 5, and store as c.
create a new rectangle with 4 and 6, and store as r.

note. calculate areas.
call calculate_area on c and store as circle_area.
call calculate_area on r and store as rect_area.

say circle area, circle_area.
say rectangle area, rect_area.

end program.
```

---

All OOP examples will work once the OOP system is fully implemented.
