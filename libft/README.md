*This project has been created as part of the 42 curriculum by rmourey-.*

# libft

## Description

**libft** is the first project in the 42 curriculum. The goal is to create a personal C library containing re-implementations of standard C library functions, along with additional utility functions that will be useful throughout the 42 cursus.

This library serves as the foundation for all future C projects at 42, providing essential functions for:
- Character classification and conversion
- String manipulation
- Memory operations
- Linked list management
- File descriptor output

By building this library from scratch, students gain a deep understanding of how fundamental C functions work at a low level.

## Instructions

### Compilation

```bash
# Compile the library
make

# Recompile from scratch
make re

# Clean object files
make clean

# Clean everything (object files + library)
make fclean
```

### Usage

After compilation, link `libft.a` with your project:

```bash
cc your_program.c -L. -lft -o your_program
```

Include the header in your source files:

```c
#include "libft.h"
```

## Library Contents

### Part 1 - Libc Functions

Re-implementations of standard C library functions:

| Function | Description |
|----------|-------------|
| `ft_isalpha` | Check if character is alphabetic |
| `ft_isdigit` | Check if character is a digit |
| `ft_isalnum` | Check if character is alphanumeric |
| `ft_isascii` | Check if character is ASCII |
| `ft_isprint` | Check if character is printable |
| `ft_strlen` | Calculate string length |
| `ft_memset` | Fill memory with a constant byte |
| `ft_bzero` | Zero a byte string |
| `ft_memcpy` | Copy memory area |
| `ft_memmove` | Copy memory area (handles overlap) |
| `ft_strlcpy` | Size-bounded string copy |
| `ft_strlcat` | Size-bounded string concatenation |
| `ft_toupper` | Convert character to uppercase |
| `ft_tolower` | Convert character to lowercase |
| `ft_strchr` | Locate character in string |
| `ft_strrchr` | Locate character in string (reverse) |
| `ft_strncmp` | Compare two strings |
| `ft_memchr` | Scan memory for a character |
| `ft_memcmp` | Compare memory areas |
| `ft_strnstr` | Locate substring in string |
| `ft_atoi` | Convert string to integer |
| `ft_calloc` | Allocate and zero memory |
| `ft_strdup` | Duplicate a string |

### Part 2 - Additional Functions

Custom utility functions:

| Function | Description |
|----------|-------------|
| `ft_substr` | Extract substring from string |
| `ft_strjoin` | Concatenate two strings |
| `ft_strtrim` | Trim characters from string |
| `ft_split` | Split string by delimiter |
| `ft_itoa` | Convert integer to string |
| `ft_strmapi` | Apply function to each character (new string) |
| `ft_striteri` | Apply function to each character (in place) |
| `ft_putchar_fd` | Output character to file descriptor |
| `ft_putstr_fd` | Output string to file descriptor |
| `ft_putendl_fd` | Output string with newline to fd |
| `ft_putnbr_fd` | Output integer to file descriptor |

### Part 3 - Linked List Functions

Functions for manipulating linked lists using the `t_list` structure:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

| Function | Description |
|----------|-------------|
| `ft_lstnew` | Create new list node |
| `ft_lstadd_front` | Add node at beginning of list |
| `ft_lstsize` | Count nodes in list |
| `ft_lstlast` | Get last node of list |
| `ft_lstadd_back` | Add node at end of list |
| `ft_lstdelone` | Delete one node |
| `ft_lstclear` | Delete and free entire list |
| `ft_lstiter` | Apply function to each node |
| `ft_lstmap` | Create new list with transformed content |

## Resources

### Documentation

- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [C Standard Library Reference](https://en.cppreference.com/w/c)
- [GNU C Library Manual](https://www.gnu.org/software/libc/manual/)
- [42 Norm Documentation](https://github.com/42School/norminette)

### AI Usage

AI assistance (Claude) was used in this project for:

- **Code review**: Analyzing implementations for correctness, edge cases, and potential bugs
- **Debugging**: Identifying issues in the libftTester leak detection system
- **Documentation**: Generating this README and code explanations
- **Learning**: Understanding concepts like integer overflow protection in `ft_calloc`

All code was written with understanding of the underlying concepts. AI served as a learning tool and reviewer, similar to consulting documentation or discussing with peers.

## Author

- **rmourey-** - 42 Madrid
