_This project has been created as part of the 42 curriculum by rmourey-._

# ft_printf

## Description

ft_printf is a reimplementation of the C standard library function `printf()`. The goal is to understand variadic functions in C and practice parsing format strings to produce formatted output.

The function handles the following format specifiers:

| Specifier | Description              |
| --------- | ------------------------ |
| `%c`      | Single character         |
| `%s`      | String                   |
| `%p`      | Pointer address          |
| `%d`      | Signed decimal integer   |
| `%i`      | Signed decimal integer   |
| `%u`      | Unsigned decimal integer |
| `%x`      | Hexadecimal (lowercase)  |
| `%X`      | Hexadecimal (uppercase)  |
| `%%`      | Percent sign             |

## Bonus Features

The bonus implementation adds support for the following flags and formatting options:

| Flag / Option | Description                                                  |
| ------------- | ------------------------------------------------------------ |
| `-`           | Left-justify within the given field width                    |
| `0`           | Zero-pad numbers instead of space-pad                        |
| `.`           | Precision: limits string length or sets minimum digit count  |
| `#`           | Alternate form: `0x`/`0X` prefix for hex conversions         |
| ` ` (space)   | Prefix positive numbers with a space                         |
| `+`           | Always prefix signed numbers with `+` or `-`                 |
| width         | Minimum field width for output                               |

## Instructions

### Compilation

```bash
make        # Compile mandatory part
make bonus  # Compile bonus part (with flags, width, precision)
make clean  # Remove object files
make fclean # Remove object files and library
make re     # Full rebuild
```

This produces `libftprintf.a`, a static library.

### Usage

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s!\n", "world");
    ft_printf("Number: %d\n", 42);
    return (0);
}
```

Compile your program with the library:

```bash
cc your_program.c libftprintf.a
```

## Algorithm and Data Structure

### Mandatory

The mandatory implementation uses a simple linear parsing approach:

1. **Format string parsing**: Iterate through the format string character by character
2. **Specifier detection**: When `%` is encountered, read the next character directly to determine the conversion type
3. **Variadic argument extraction**: Use `va_arg()` to retrieve the appropriate argument based on the specifier
4. **Output**: Write formatted output using `write()` system call

This approach was chosen for its simplicity and efficiency. No complex data structures are needed since the format string is processed sequentially in a single pass.

### Bonus

The bonus implementation extends the parser with a `t_fmt` struct that captures all formatting metadata for each conversion:

```c
typedef struct s_fmt
{
    int     minus;      // Left-justify flag
    int     zero;       // Zero-padding flag
    int     hash;       // Alternate form flag (#)
    int     space;      // Space prefix flag
    int     plus;       // Plus sign flag
    int     width;      // Minimum field width
    int     precision;  // Precision value (-1 if unset)
    char    specifier;  // Conversion character (c, s, p, d, i, u, x, X, %)
}   t_fmt;
```

The `ft_parse_format` function fills this struct by scanning flags, width, precision, and specifier in order. Each print function then uses the struct to apply the correct formatting (padding, truncation, prefixes) before writing output.

## Resources

- [GNU C Library - Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)
- [C Standard Library - printf](https://en.cppreference.com/w/c/io/fprintf)
- [Variadic Functions in C](https://en.cppreference.com/w/c/variadic)

### AI Usage

AI tools (Claude) were used to assist in restructuring the project into mandatory and bonus file separation.
