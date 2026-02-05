# Task 1: String Replace

## Description
This program implements a `replace` function that takes a string and replaces all spaces with a specified character (default is a `-`). It returns the count of replacements made.

## Setup & Run

### Compilation
Compile the program manually using `gcc`:
```
gcc main.c -o main
```

### Usage
Run the program with optional arguments:
```
./main [string] [replacement_char]
```

- **Argument 1:** The input string to process. **Default value:** `"The cat sat"`
- **Argument 2:** The character to replace spaces with. **Default value:** `-`

### Examples
Default usage:
```
./main
# Output: "The-cat-sat", Replaced: 2
```

Custom string:
```
./main "Hello World"
# Output: "Hello-World", Replaced: 1
```

Custom string and replacement:
```
./main "Words words words words" ,
# Output: "Words,words,words,words", Replaced: 3
```
