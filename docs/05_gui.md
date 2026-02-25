# GUI Programming in Kaynat++

Build desktop applications with Kaynat++.

## Table of Contents

1. [Introduction](#introduction)
2. [Windows](#windows)
3. [Widgets](#widgets)
4. [Events](#events)
5. [Layout](#layout)
6. [Dialogs](#dialogs)
7. [Menus](#menus)
8. [Canvas Drawing](#canvas-drawing)
9. [Themes](#themes)
10. [Complete Example](#complete-example)

---

## Introduction

Kaynat++ uses Dear ImGui + SDL2 for GUI programming. All GUI operations use simple English syntax.

---

## Windows

### Creating a Window

```kaynat
create a window called main window.
set the title of main window to Kaynat++ App.
set the width of main window to 800.
set the height of main window to 600.
set the background of main window to white.
show main window.
```

---

## Widgets

### Label

```kaynat
create a label called greeting label.
set the text of greeting label to Hello, Kaynat++.
set the font of greeting label to Arial 18 bold.
place greeting label at row 0 and column 0 in main window.
```

### Button

```kaynat
create a button called submit button.
set the text of submit button to Submit.
set the action of submit button to the function called on_submit.
place submit button at row 1 and column 0 in main window.
```

### Text Input

```kaynat
create a text input called name input.
set the placeholder of name input to Enter your name.
place name input at row 0 and column 1 in main window.
```

### Text Area

```kaynat
create a text area called notes area.
set the width of notes area to 40.
set the height of notes area to 10.
place notes area at row 1 and column 1 in main window.
```

### Checkbox

```kaynat
create a checkbox called accept terms.
set the text of accept terms to I accept the terms.
place accept terms at row 2 and column 0 in main window.
```

### Dropdown

```kaynat
create a dropdown called color picker.
set the options of color picker to red, green, blue, yellow.
place color picker at row 3 and column 0 in main window.
```

### Slider

```kaynat
create a slider called volume slider.
set the minimum of volume slider to 0.
set the maximum of volume slider to 100.
place volume slider at row 4 and column 0 in main window.
```

### Progress Bar

```kaynat
create a progress bar called loading bar.
set the maximum of loading bar to 100.
set the value of loading bar to 50.
place loading bar at row 5 and column 0 in main window.
```

---

## Events

### Button Click

```kaynat
when submit button is clicked, call on_submit.

define a function called on_submit that takes nothing.
    say button was clicked.
end.
```

### Text Change

```kaynat
when name input text changes, call validate_input.

define a function called validate_input that takes nothing.
    say text changed.
end.
```

### Window Close

```kaynat
when main window is closed, call on_close.

define a function called on_close that takes nothing.
    say window closing.
end.
```

---

## Layout

### Grid Layout

```kaynat
place label1 at row 0 and column 0 in main window.
place button1 at row 0 and column 1 in main window.
place input1 at row 1 and column 0 in main window.
place button2 at row 1 and column 1 in main window.
```

---

## Dialogs

### Message Dialog

```kaynat
show a message saying file saved successfully.
```

### Error Dialog

```kaynat
show an error saying please fill in all fields.
```

### Confirmation Dialog

```kaynat
ask the user to confirm with message are you sure and store as confirmed.
if confirmed is true then.
    say user confirmed.
end.
```

### File Chooser

```kaynat
ask the user to choose a file and store as file_path.
say selected file, file_path.
```

---

## Menus

### Menu Bar

```kaynat
create a menu bar called app menu.
add menu called file to app menu.
add item called open to file menu with action on_open.
add separator to file menu.
add item called exit to file menu with action on_exit.
attach app menu to main window.
```

---

## Canvas Drawing

### Drawing Shapes

```kaynat
create a canvas called drawing board.

note. draw a line.
draw a line from 0, 0 to 100, 100 on drawing board with color black.

note. draw a rectangle.
draw a rectangle from 50, 50 to 200, 150 on drawing board with fill blue.

note. draw a circle.
draw a circle at 300, 200 with radius 50 on drawing board with fill red.
```

---

## Themes

### Applying Themes

```kaynat
apply theme dark to main window.
apply theme light to main window.
set global font to Arial 12.
```

---

## Complete Example

### To-Do List Application

```kaynat
begin program.

note. create main window.
create a window called todo window.
set the title of todo window to To-Do List.
set the width of todo window to 600.
set the height of todo window to 400.

note. create input for new task.
create a text input called task input.
set the placeholder of task input to Enter new task.
place task input at row 0 and column 0 in todo window.

note. create add button.
create a button called add button.
set the text of add button to Add Task.
place add button at row 0 and column 1 in todo window.

note. create task list area.
create a text area called task list.
set the width of task list to 50.
set the height of task list to 15.
place task list at row 1 and column 0 in todo window.

note. create clear button.
create a button called clear button.
set the text of clear button to Clear All.
place clear button at row 2 and column 0 in todo window.

note. task storage.
create a list called tasks.

note. add task function.
define a function called add_task that takes nothing.
    note. get text from input.
    get the text of task input and store as new_task.
    
    if new_task is not empty then.
        add new_task to tasks.
        
        note. update display.
        join tasks with newline and store as task_text.
        set the text of task list to task_text.
        
        note. clear input.
        set the text of task input to empty.
    end.
end.

note. clear all function.
define a function called clear_all that takes nothing.
    set tasks to a list.
    set the text of task list to empty.
end.

note. attach events.
when add button is clicked, call add_task.
when clear button is clicked, call clear_all.

note. show window.
show todo window.

end program.
```

---

All GUI examples will work in Kaynat++ once the GUI system is fully implemented.
