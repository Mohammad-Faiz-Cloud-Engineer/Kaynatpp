# Standard Library Reference

Complete reference for all built-in functions in Kaynat++.

## Math Tools

```kaynat
call sqrt with 16 and store as result.              note. square root.
call pow with 2 and 10 and store as result.         note. power.
call abs with negative 42 and store as result.      note. absolute value.
call floor with 4.8 and store as result.            note. floor.
call ceil with 4.2 and store as result.             note. ceiling.
call round with 4.567 and 2 and store as result.    note. round to 2 decimals.
call sin with 45 and store as result.               note. sine.
call cos with 45 and store as result.               note. cosine.
call tan with 45 and store as result.               note. tangent.
call log with 1000 and 10 and store as result.      note. logarithm base 10.
call factorial with 5 and store as result.          note. factorial.
call gcd with 12 and 8 and store as result.         note. greatest common divisor.
call lcm with 12 and 8 and store as result.         note. least common multiple.
```

## String Tools

```kaynat
call uppercase with hello and store as result.
call lowercase with HELLO and store as result.
call trim with   hello   and store as result.
call split with hello world and space and store as result.
call join with list and comma and store as result.
call replace with hello world and world and kaynat and store as result.
call substring with hello and 0 and 3 and store as result.
call reverse with hello and store as result.
call repeat with star and 10 and store as result.
call length with hello and store as result.
call contains with hello world and world and store as result.
call starts_with with hello and hel and store as result.
call ends_with with hello and lo and store as result.
call index_of with hello world and world and store as result.
```

## List Tools

```kaynat
call sort with list and store as result.
call reverse with list and store as result.
call filter with list and condition and store as result.
call map with list and function and store as result.
call reduce with list and function and store as result.
call min with list and store as result.
call max with list and store as result.
call sum with list and store as result.
call average with list and store as result.
call unique with list and store as result.
call flatten with nested_list and store as result.
```

## File Tools

```kaynat
call read_file with data.txt and store as content.
call write_file with output.txt and content.
call append_file with log.txt and new entry.
call file_exists with config.txt and store as exists.
call delete_file with temp.txt.
call copy_file with source.txt and dest.txt.
call move_file with old.txt and new.txt.
call list_files with directory and store as files.
call create_directory with new_folder.
call file_size with data.txt and store as size.
```

## Date Tools

```kaynat
call current_date and store as date.
call current_time and store as time.
call format_date with date and YYYY-MM-DD and store as formatted.
call parse_date with 2024-01-01 and store as date.
call date_diff with date1 and date2 and store as diff.
```

## Random Tools

```kaynat
call random_int with 1 and 100 and store as num.
call random_float with 0.0 and 1.0 and store as num.
call random_choice with list and store as item.
call shuffle with list and store as shuffled.
call random_string with 10 and store as str.
call random_seed with 42.
```

## Network Tools

```kaynat
call http_get with https://api.example.com and store as response.
call http_post with https://api.example.com and data and store as response.
```

## JSON Tools

```kaynat
call json_parse with json_string and store as data.
call json_generate with data and store as json_string.
call json_format with json_string and store as formatted.
```

## Crypto Tools

```kaynat
call sha256 with hello and store as hash.
call md5 with hello and store as hash.
call base64_encode with hello and store as encoded.
call base64_decode with encoded and store as decoded.
call generate_token with 32 and store as token.
```

## Pattern Tools

```kaynat
call regex_match with text and pattern and store as matches.
call regex_replace with text and pattern and replacement and store as result.
call validate_email with email@example.com and store as valid.
call validate_url with https://example.com and store as valid.
call validate_phone with 123-456-7890 and store as valid.
call extract_numbers with text and store as numbers.
```

---

All stdlib functions will be available once the standard library is fully implemented.
