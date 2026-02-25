# Standard Library Usage Guide

Practical examples of using the standard library.

## Math Operations

```kaynat
begin program.

note. basic math.
call sqrt with 16 and store as root.
say square root of 16 is, root.

call pow with 2 and 10 and store as power.
say 2 to the power 10 is, power.

call abs with negative 42 and store as absolute.
say absolute value of negative 42 is, absolute.

note. rounding.
call floor with 4.8 and store as floored.
say floor of 4.8 is, floored.

call ceil with 4.2 and store as ceiled.
say ceiling of 4.2 is, ceiled.

call round with 4.567 and 2 and store as rounded.
say 4.567 rounded to 2 decimals is, rounded.

note. trigonometry.
call sin with 45 and store as sine.
say sine of 45 is, sine.

call cos with 45 and store as cosine.
say cosine of 45 is, cosine.

end program.
```

## String Operations

```kaynat
begin program.

set text to hello world.

call uppercase with text and store as upper.
say upper.

call lowercase with text and store as lower.
say lower.

call split with text and space and store as words.
say words.

call reverse with text and store as reversed.
say reversed.

call replace with text and world and kaynat and store as replaced.
say replaced.

end program.
```

## List Operations

```kaynat
begin program.

set numbers to a list containing 5, 2, 8, 1, 9, 3.

call sort with numbers and store as sorted.
say sorted list, sorted.

call min with numbers and store as minimum.
say minimum value, minimum.

call max with numbers and store as maximum.
say maximum value, maximum.

call sum with numbers and store as total.
say sum, total.

call average with numbers and store as avg.
say average, avg.

end program.
```

## File Operations

```kaynat
begin program.

note. write to file.
set content to hello from kaynat++.
call write_file with output.txt and content.
say file written.

note. read from file.
call read_file with output.txt and store as data.
say file content, data.

note. check if file exists.
call file_exists with output.txt and store as exists.
if exists is true then.
    say file exists.
end.

end program.
```

## Date and Time

```kaynat
begin program.

call current_date and store as today.
say today is, today.

call current_time and store as now.
say current time is, now.

call format_date with today and YYYY-MM-DD and store as formatted.
say formatted date, formatted.

end program.
```

## Random Operations

```kaynat
begin program.

call random_int with 1 and 100 and store as num.
say random number, num.

set items to a list containing apple, banana, cherry, date.
call random_choice with items and store as item.
say random item, item.

call shuffle with items and store as shuffled.
say shuffled list, shuffled.

end program.
```

## JSON Operations

```kaynat
begin program.

note. create data structure.
create a map called person.
set key name to John in person.
set key age to 30 in person.

note. convert to JSON.
call json_generate with person and store as json.
say json string, json.

note. parse JSON.
call json_parse with json and store as data.
get key name from data and store as name.
say name from json, name.

end program.
```

## Crypto Operations

```kaynat
begin program.

set password to mysecretpassword.

call sha256 with password and store as hash.
say sha256 hash, hash.

call md5 with password and store as md5_hash.
say md5 hash, md5_hash.

call generate_token with 32 and store as token.
say random token, token.

end program.
```

---

All stdlib examples will work once the standard library is fully implemented.
