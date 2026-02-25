# GUI Usage Guide

Practical examples of building desktop applications.

## Example 1: Simple Calculator

```kaynat
begin program.

note. create window.
create a window called calc_window.
set the title of calc_window to Calculator.
set the width of calc_window to 400.
set the height of calc_window to 300.

note. create input fields.
create a text input called num1_input.
set the placeholder of num1_input to First number.
place num1_input at row 0 and column 0 in calc_window.

create a text input called num2_input.
set the placeholder of num2_input to Second number.
place num2_input at row 0 and column 1 in calc_window.

note. create buttons.
create a button called add_button.
set the text of add_button to Add.
place add_button at row 1 and column 0 in calc_window.

create a button called subtract_button.
set the text of subtract_button to Subtract.
place subtract_button at row 1 and column 1 in calc_window.

note. create result label.
create a label called result_label.
set the text of result_label to Result will appear here.
place result_label at row 2 and column 0 in calc_window.

note. define button actions.
define a function called on_add that takes nothing.
    get the text of num1_input and store as num1.
    get the text of num2_input and store as num2.
    turn num1 into a number and store as n1.
    turn num2 into a number and store as n2.
    set result to n1.
    add n2 to result.
    convert result to text and store as result_text.
    set the text of result_label to result_text.
end.

define a function called on_subtract that takes nothing.
    get the text of num1_input and store as num1.
    get the text of num2_input and store as num2.
    turn num1 into a number and store as n1.
    turn num2 into a number and store as n2.
    set result to n1.
    subtract n2 from result.
    convert result to text and store as result_text.
    set the text of result_label to result_text.
end.

note. attach events.
when add_button is clicked, call on_add.
when subtract_button is clicked, call on_subtract.

note. show window.
show calc_window.

end program.
```

## Example 2: To-Do List

```kaynat
begin program.

note. create window.
create a window called todo_window.
set the title of todo_window to To-Do List.
set the width of todo_window to 600.
set the height of todo_window to 400.

note. create input.
create a text input called task_input.
set the placeholder of task_input to Enter new task.
place task_input at row 0 and column 0 in todo_window.

note. create add button.
create a button called add_button.
set the text of add_button to Add Task.
place add_button at row 0 and column 1 in todo_window.

note. create task list display.
create a text area called task_list.
set the width of task_list to 50.
set the height of task_list to 15.
place task_list at row 1 and column 0 in todo_window.

note. create clear button.
create a button called clear_button.
set the text of clear_button to Clear All.
place clear_button at row 2 and column 0 in todo_window.

note. task storage.
create a list called tasks.

note. define functions.
define a function called add_task that takes nothing.
    get the text of task_input and store as new_task.
    if new_task is not empty then.
        add new_task to tasks.
        join tasks with newline and store as task_text.
        set the text of task_list to task_text.
        set the text of task_input to empty.
    end.
end.

define a function called clear_all that takes nothing.
    set tasks to a list.
    set the text of task_list to empty.
end.

note. attach events.
when add_button is clicked, call add_task.
when clear_button is clicked, call clear_all.

note. show window.
show todo_window.

end program.
```

## Example 3: Text Editor

```kaynat
begin program.

note. create window.
create a window called editor_window.
set the title of editor_window to Text Editor.
set the width of editor_window to 800.
set the height of editor_window to 600.

note. create menu bar.
create a menu bar called main_menu.
add menu called file to main_menu.
add item called open to file menu with action on_open.
add item called save to file menu with action on_save.
add separator to file menu.
add item called exit to file menu with action on_exit.
attach main_menu to editor_window.

note. create text area.
create a text area called editor_area.
set the width of editor_area to 80.
set the height of editor_area to 30.
place editor_area at row 0 and column 0 in editor_window.

note. define menu actions.
define a function called on_open that takes nothing.
    ask the user to choose a file and store as file_path.
    if file_path is not empty then.
        read the file called file_path and store as content.
        set the text of editor_area to content.
    end.
end.

define a function called on_save that takes nothing.
    ask the user to choose a file and store as file_path.
    if file_path is not empty then.
        get the text of editor_area and store as content.
        write content to the file called file_path.
        show a message saying file saved successfully.
    end.
end.

define a function called on_exit that takes nothing.
    ask the user to confirm with message are you sure and store as confirmed.
    if confirmed is true then.
        note. close application.
        say closing application.
    end.
end.

note. show window.
show editor_window.

end program.
```

---

All GUI examples will work once the GUI system is fully implemented.
