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

## Instructions

### Compilation

```bash
make
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

The implementation uses a simple linear parsing approach:

1. **Format string parsing**: Iterate through the format string character by character
2. **Specifier detection**: When `%` is encountered, check the next character to determine the conversion type
3. **Variadic argument extraction**: Use `va_arg()` to retrieve the appropriate argument based on the specifier
4. **Output**: Write formatted output using `write()` system call

This approach was chosen for its simplicity and efficiency. No complex data structures are needed since the format string is processed sequentially in a single pass.

## Resources

- [GNU C Library - Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)
- [C Standard Library - printf](https://en.cppreference.com/w/c/io/fprintf)
- [Variadic Functions in C](https://en.cppreference.com/w/c/variadic)

### AI Usage

No AI tools were used in the development of this project.
