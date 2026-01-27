# ft_printf Study Guide

A comprehensive documentation of the ft_printf implementation.

---

## Table of Contents

1. [Overview](#1-overview)
2. [Architecture](#2-architecture)
3. [Parsing Logic](#3-parsing-logic)
4. [Core Algorithms](#4-core-algorithms)
5. [Specifier Deep Dives](#5-specifier-deep-dives)
6. [Flag Interaction Matrix](#6-flag-interaction-matrix)
7. [Precision vs Width](#7-precision-vs-width)
8. [Common Edge Cases](#8-common-edge-cases)
9. [Code Walkthrough Examples](#9-code-walkthrough-examples)
10. [Practice Exercises](#10-practice-exercises)

---

## 1. Overview

### What is ft_printf?

`ft_printf` is a custom implementation of the standard C library's `printf` function. It writes formatted output to stdout, supporting various format specifiers, flags, width, and precision options.

### Format String Syntax

```
%[flags][width][.precision]specifier
```

| Component    | Description                                                  | Example |
| ------------ | ------------------------------------------------------------ | ------- |
| `%`          | Format specifier start                                       | `%d`    |
| `flags`      | Optional modifiers: `-`, `0`, `#`, ` `, `+`                  | `%-5d`  |
| `width`      | Minimum field width (decimal number)                         | `%10s`  |
| `.precision` | Precision (dot followed by decimal number)                   | `%.3f`  |
| `specifier`  | Conversion type: `c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%` | `%s`    |

### Return Value

`ft_printf` returns the total number of characters printed (excluding the null terminator). Returns `-1` if the format string is NULL.

---

## 2. Architecture

### File Structure

# TODO FILE STRUCTURE

### The t_fmt Structure

The `t_fmt` structure stores all parsed format information:

```c
typedef struct s_fmt
{
    int     minus;      // '-' flag: left-align output
    int     zero;       // '0' flag: zero-pad numbers
    int     hash;       // '#' flag: alternate form (0x prefix for hex)
    int     space;      // ' ' flag: space before positive numbers
    int     plus;       // '+' flag: always show sign
    int     width;      // Minimum field width
    int     precision;  // Precision (-1 if not specified)
    char    specifier;  // Conversion character (c, s, p, d, i, u, x, X, %)
}   t_fmt;
```

**Field Details:**

| Field       | Type | Default | Purpose                                     |
| ----------- | ---- | ------- | ------------------------------------------- |
| `minus`     | int  | 0       | Left-align within field width               |
| `zero`      | int  | 0       | Pad with zeros instead of spaces            |
| `hash`      | int  | 0       | Alternate form (adds 0x for hex)            |
| `space`     | int  | 0       | Add space for positive numbers              |
| `plus`      | int  | 0       | Always show + or - sign                     |
| `width`     | int  | 0       | Minimum characters to output                |
| `precision` | int  | -1      | Min digits (numbers) or max chars (strings) |
| `specifier` | char | 0       | The conversion character                    |

### Function Call Flow

```
ft_printf(format, ...)
    │
    ├─► Iterate through format string
    │       │
    │       ├─► '%' found
    │       │       │
    │       │       └─► ft_parse_format()
    │       │               ├─► ft_init_spec()
    │       │               ├─► ft_parse_flags()
    │       │               ├─► ft_parse_width()
    │       │               └─► ft_parse_precision()
    │       │
    │       └─► ft_dispatch()
    │               │
    │               ├─► 'c' → ft_print_char()
    │               ├─► 's' → ft_print_str()
    │               ├─► 'p' → ft_print_ptr()
    │               ├─► 'd'/'i' → ft_print_nbr()
    │               ├─► 'u' → ft_print_unsigned()
    │               ├─► 'x'/'X' → ft_print_hex()
    │               └─► '%' → ft_print_char('%')
    │
    └─► Return total character count
```

---

## 3. Parsing Logic

### ft_parse_format.c Overview

The parser processes the format string sequentially after encountering `%`:

```c
int ft_parse_format(const char *fmt, int *i, t_fmt *spec)
{
    ft_init_spec(spec);           // 1. Initialize all fields
    (*i)++;                        // 2. Skip '%'
    ft_parse_flags(fmt, i, spec); // 3. Parse flags
    ft_parse_width(fmt, i, spec); // 4. Parse width
    ft_parse_precision(fmt, i, spec); // 5. Parse precision
    if (fmt[*i] && ft_strchr("cspdiuxX%", fmt[*i]))
    {
        spec->specifier = fmt[*i];
        return (1);  // Valid specifier found
    }
    return (0);  // Invalid specifier
}
```

### Initialization

All fields are reset to default values:

```c
static void ft_init_spec(t_fmt *spec)
{
    spec->minus = 0;
    spec->zero = 0;
    spec->hash = 0;
    spec->space = 0;
    spec->plus = 0;
    spec->width = 0;
    spec->precision = -1;  // -1 means "not specified"
    spec->specifier = 0;
}
```

**Key Point:** `precision = -1` indicates precision was not specified, which affects zero-padding behavior.

### Flag Parsing

Flags can appear in any order and are parsed until a non-flag character:

```c
static void ft_parse_flags(const char *fmt, int *i, t_fmt *spec)
{
    while (fmt[*i] && ft_strchr("-0# +", fmt[*i]))
    {
        if (fmt[*i] == '-')
            spec->minus = 1;
        else if (fmt[*i] == '0')
            spec->zero = 1;
        else if (fmt[*i] == '#')
            spec->hash = 1;
        else if (fmt[*i] == ' ')
            spec->space = 1;
        else if (fmt[*i] == '+')
            spec->plus = 1;
        (*i)++;
    }
}
```

### Width Parsing

Width is accumulated from consecutive digits:

```c
static void ft_parse_width(const char *fmt, int *i, t_fmt *spec)
{
    while (fmt[*i] && ft_isdigit(fmt[*i]))
    {
        spec->width = spec->width * 10 + (fmt[*i] - '0');
        (*i)++;
    }
}
```

**Algorithm:** Horner's method - `width = width * 10 + digit`

### Precision Parsing

Precision is triggered by `.` and defaults to 0 if no digits follow:

```c
static void ft_parse_precision(const char *fmt, int *i, t_fmt *spec)
{
    if (fmt[*i] == '.')
    {
        (*i)++;
        spec->precision = 0;  // Mark as specified
        while (fmt[*i] && ft_isdigit(fmt[*i]))
        {
            spec->precision = spec->precision * 10 + (fmt[*i] - '0');
            (*i)++;
        }
    }
}
```

**Key Point:** `%.d` and `%.0d` are equivalent (precision = 0).

---

## 4. Core Algorithms

### Padding Algorithm

The `ft_print_padding` function outputs `n` copies of character `c`:

```c
int ft_print_padding(int n, char c)
{
    int count = 0;
    while (n > 0)
    {
        count += ft_putchar_count(c);
        n--;
    }
    return (count);
}
```

**Edge Case:** If `n <= 0`, no characters are printed.

### Recursive Digit Printing

Numbers are printed most-significant-digit first using recursion:

```c
static int ft_print_digits(long n)
{
    int count = 0;
    if (n >= 10)
        count += ft_print_digits(n / 10);  // Recurse for higher digits
    count += ft_putchar_count('0' + (n % 10));  // Print current digit
    return (count);
}
```

**Why Recursion?**

- Digits are extracted right-to-left (42 % 10 = 2, 42 / 10 = 4)
- But we need to print left-to-right (4, then 2)
- Recursion naturally reverses the order via the call stack

**Example: Printing 123**

```
ft_print_digits(123)
  └─► ft_print_digits(12)
        └─► ft_print_digits(1)
              └─► print '1', return
        └─► print '2', return
  └─► print '3', return
Output: "123"
```

### Precision for Numbers

Precision specifies minimum digits, adding leading zeros if needed:

```c
int digit_len = ft_num_len(n);       // Actual digits
int num_len = digit_len;
if (spec->precision > digit_len)
    num_len = spec->precision;       // Pad with leading zeros

// Print leading zeros
ft_print_padding(num_len - digit_len, '0');
```

**Example:** `%.5d` with value `42`:

- `digit_len = 2`, `precision = 5`
- `num_len = 5`, leading zeros = 3
- Output: `00042`

### Width & Alignment: Three Rendering Paths

Number handlers use three distinct rendering paths:

```c
// Determine pad character
char pad = ' ';
if (spec->zero && !spec->minus && spec->precision < 0)
    pad = '0';

// PATH 1: Left-align (minus flag)
if (spec->minus)
{
    // [sign][precision zeros][digits][space padding]
}
// PATH 2: Zero-padding
else if (pad == '0')
{
    // [sign][zero padding][precision zeros][digits]
}
// PATH 3: Space-padding (default)
else
{
    // [space padding][sign][precision zeros][digits]
}
```

**Path Summary:**

| Path       | Condition                             | Order                          |
| ---------- | ------------------------------------- | ------------------------------ |
| Left-align | `minus` flag set                      | content → padding              |
| Zero-pad   | `zero` flag, no `minus`, no precision | sign → zeros → digits          |
| Space-pad  | Default                               | spaces → sign → zeros → digits |

---

## 5. Specifier Deep Dives

### %c - Character

**Applicable Flags:** `-` (width for padding)

**Algorithm:**

```
if (minus)
    print char, then pad with spaces
else
    pad with spaces, then print char
```

**Examples:**

| Format | Input | Output | Explanation            |
| ------ | ----- | ------ | ---------------------- |
| `%c`   | `'A'` | `A`    | Single character       |
| `%5c`  | `'A'` | `A`    | Right-aligned, width 5 |
| `%-5c` | `'A'` | `A`    | Left-aligned, width 5  |

**Edge Cases:**

- Width < 1: No padding
- Zero flag: Ignored (always space padding)

---

### %s - String

**Applicable Flags:** `-` (width for padding)

**Algorithm:**

```
if (str == NULL)
    str = "(null)"
len = strlen(str)
print_len = (precision >= 0 && precision < len) ? precision : len
if (minus)
    print print_len chars, then pad
else
    pad, then print print_len chars
```

**Examples:**

| Format   | Input     | Output   | Explanation              |
| -------- | --------- | -------- | ------------------------ |
| `%s`     | `"hello"` | `hello`  | Full string              |
| `%10s`   | `"hello"` | `hello`  | Right-aligned, width 10  |
| `%-10s`  | `"hello"` | `hello`  | Left-aligned             |
| `%.3s`   | `"hello"` | `hel`    | Precision truncates to 3 |
| `%10.3s` | `"hello"` | `hel`    | Width 10, precision 3    |
| `%s`     | `NULL`    | `(null)` | NULL handling            |

**Edge Cases:**

- NULL string: Prints "(null)" (6 characters)
- Precision = 0: Prints nothing from string
- Width < string length: No truncation, just no padding

---

### %p - Pointer

**Applicable Flags:** `-` (width for padding)

**Algorithm:**

```
if (ptr == NULL)
    return print_nil()  // prints "(nil)"
addr = (unsigned long)ptr
total_len = hex_digit_count(addr) + 2  // +2 for "0x"
if (minus)
    print "0x", print hex digits, then pad
else
    pad, print "0x", print hex digits
```

**Examples:**

| Format  | Input    | Output   | Explanation             |
| ------- | -------- | -------- | ----------------------- |
| `%p`    | `0x7fff` | `0x7fff` | Hex address with prefix |
| `%20p`  | `0x7fff` | `0x7fff` | Right-aligned           |
| `%-20p` | `0x7fff` | `0x7fff` | Left-aligned            |
| `%p`    | `NULL`   | `(nil)`  | NULL handling           |

**Edge Cases:**

- NULL pointer: Prints "(nil)" (5 characters)
- Always lowercase hex (a-f)
- "0x" prefix always included (except NULL)

---

### %d / %i - Signed Integer

**Applicable Flags:** `-`, `0`, ` `, `+`

**Algorithm:**

```
sign = get_sign_char(is_negative, spec)  // '-', '+', ' ', or none
digit_len = count_digits(abs(n))
if (n == 0 && precision == 0)
    digit_len = 0  // Special case
num_len = max(digit_len, precision)
total_len = num_len + (sign ? 1 : 0)

if (minus)
    [sign][precision zeros][digits][space padding]
else if (zero && precision < 0)
    [sign][zero padding][digits]
else
    [space padding][sign][precision zeros][digits]
```

**Sign Priority:**

1. Negative number → `-`
2. Plus flag → `+`
3. Space flag → ` `
4. Otherwise → no sign character

**Examples:**

| Format  | Input | Output  | Explanation            |
| ------- | ----- | ------- | ---------------------- |
| `%d`    | `42`  | `42`    | Basic integer          |
| `%5d`   | `42`  | `42`    | Width 5, space-padded  |
| `%05d`  | `42`  | `00042` | Zero-padded            |
| `%-5d`  | `42`  | `42`    | Left-aligned           |
| `%+d`   | `42`  | `+42`   | Force sign             |
| `% d`   | `42`  | `42`    | Space for positive     |
| `%d`    | `-42` | `-42`   | Negative               |
| `%05d`  | `-42` | `-0042` | Negative with zero-pad |
| `%.5d`  | `42`  | `00042` | Precision = min digits |
| `%8.5d` | `42`  | `00042` | Width and precision    |
| `%.0d`  | `0`   | ``      | Zero with precision 0  |

**Edge Cases:**

- Zero with precision 0: Prints nothing
- INT_MIN: Handled via long conversion
- Precision overrides zero-padding

---

### %u - Unsigned Integer

**Applicable Flags:** `-`, `0`

**Algorithm:**
Same as `%d` but without sign handling.

**Examples:**

| Format | Input | Output  | Explanation           |
| ------ | ----- | ------- | --------------------- |
| `%u`   | `42`  | `42`    | Basic unsigned        |
| `%5u`  | `42`  | `42`    | Width 5               |
| `%05u` | `42`  | `00042` | Zero-padded           |
| `%.5u` | `42`  | `00042` | Precision             |
| `%.0u` | `0`   | ``      | Zero with precision 0 |

---

### %x / %X - Hexadecimal

**Applicable Flags:** `-`, `0`, `#`

**Algorithm:**

```
digit_len = hex_digit_count(n)
if (n == 0 && precision == 0)
    digit_len = 0
num_len = max(digit_len, precision)
prefix_len = (hash && n != 0) ? 2 : 0  // "0x" or "0X"
total_len = num_len + prefix_len

if (minus)
    [prefix][precision zeros][hex digits][space padding]
else if (zero && precision < 0)
    [prefix][zero padding][hex digits]
else
    [space padding][prefix][precision zeros][hex digits]
```

**Examples:**

| Format  | Input | Output     | Explanation                |
| ------- | ----- | ---------- | -------------------------- |
| `%x`    | `255` | `ff`       | Lowercase hex              |
| `%X`    | `255` | `FF`       | Uppercase hex              |
| `%#x`   | `255` | `0xff`     | With prefix                |
| `%#X`   | `255` | `0XFF`     | Uppercase prefix           |
| `%8x`   | `255` | `ff`       | Width 8                    |
| `%08x`  | `255` | `000000ff` | Zero-padded                |
| `%#8x`  | `255` | `0xff`     | Prefix with width          |
| `%#08x` | `255` | `0x0000ff` | Prefix + zero-pad          |
| `%#x`   | `0`   | `0`        | Hash with zero (no prefix) |
| `%.0x`  | `0`   | ``         | Zero with precision 0      |

**Edge Cases:**

- Hash flag with zero value: No prefix printed
- Precision 0 with zero: Prints nothing

---

### %% - Percent Literal

**Algorithm:**
Treated as `%c` with character `'%'`.

**Examples:**

| Format | Output |
| ------ | ------ |
| `%%`   | `%`    |
| `%5%`  | `%`    |
| `%-5%` | `%`    |

---

## 6. Flag Interaction Matrix

### Which Flags Affect Which Specifiers

| Flag        | %c  | %s  | %p  | %d/%i | %u  | %x/%X | %%  |
| ----------- | :-: | :-: | :-: | :---: | :-: | :---: | :-: |
| `-` (minus) |  Y  |  Y  |  Y  |   Y   |  Y  |   Y   |  Y  |
| `0` (zero)  |  -  |  -  |  -  |  Y\*  | Y\* |  Y\*  |  -  |
| `#` (hash)  |  -  |  -  |  -  |   -   |  -  |   Y   |  -  |
| ` ` (space) |  -  |  -  |  -  |   Y   |  -  |   -   |  -  |
| `+` (plus)  |  -  |  -  |  -  |   Y   |  -  |   -   |  -  |

\*Zero flag only applies when no precision specified and no minus flag

### Flag Priority Rules

1. **Minus disables Zero:** `-` flag makes `0` flag ineffective

   ```
   %0-5d  →  left-aligned with spaces, not zeros
   ```

2. **Plus overrides Space:** `+` takes priority over ` `

   ```
   %+ d   →  shows '+' not ' ' for positive
   ```

3. **Precision disables Zero-padding:** Specifying precision uses spaces

   ```
   %05.3d →  "  042" not "00042" (precision 3 = min 3 digits)
   ```

---

## 7. Precision vs Width

### Key Distinctions

| Aspect           | Width                   | Precision                   |
| ---------------- | ----------------------- | --------------------------- |
| **Symbol**       | Digits after flags      | `.` followed by digits      |
| **For strings**  | Minimum field width     | Maximum characters to print |
| **For numbers**  | Minimum field width     | Minimum digits to print     |
| **Padding char** | Space (or zero if flag) | Always zero                 |
| **Truncation**   | Never truncates         | Truncates strings only      |

### Visual Comparison

**Strings:**

```
Width 10:     printf("%10s", "hello")   →  "     hello"  (padded to 10)
Precision 3:  printf("%.3s", "hello")   →  "hel"        (truncated to 3)
Both:         printf("%10.3s", "hello") →  "       hel" (3 chars, width 10)
```

**Numbers:**

```
Width 10:     printf("%10d", 42)        →  "        42" (padded to 10)
Precision 5:  printf("%.5d", 42)        →  "00042"      (5 digits minimum)
Both:         printf("%10.5d", 42)      →  "     00042" (5 digits, width 10)
```

### Edge Cases

**%.0d with 0:**

```c
printf("%.0d", 0);  // Output: "" (empty)
printf("%5.0d", 0); // Output: "     " (5 spaces)
```

When precision is 0 and value is 0, nothing is printed for the number itself.

**%.3s truncation:**

```c
printf("%.3s", "hello");  // Output: "hel"
printf("%.10s", "hello"); // Output: "hello" (no padding, just limits)
```

Precision limits but doesn't pad strings.

---

## 8. Common Edge Cases

### Zero with Precision 0

When the value is 0 and precision is 0, the digit is suppressed:

```c
printf("%.0d", 0);     // ""
printf("%5.0d", 0);    // "     "
printf("%.0x", 0);     // ""
printf("%#.0x", 0);    // "" (no prefix either)
```

### NULL String

NULL strings print as "(null)":

```c
printf("%s", NULL);      // "(null)"
printf("%10s", NULL);    // "    (null)"
printf("%.3s", NULL);    // "(nu" - precision applies!
```

### NULL Pointer

NULL pointers print as "(nil)":

```c
printf("%p", NULL);      // "(nil)"
printf("%10p", NULL);    // "     (nil)"
```

### Negative Numbers with Zero-Padding

Sign comes before zeros:

```c
printf("%05d", -42);     // "-0042" not "000-42"
printf("%+05d", 42);     // "+0042"
```

### Hash Flag Only for Non-Zero Hex

The `0x` prefix is not added for zero values:

```c
printf("%#x", 255);  // "0xff"
printf("%#x", 0);    // "0" (no prefix)
```

### Precision and Zero-Padding Interaction

Precision overrides zero-padding:

```c
printf("%05d", 42);      // "00042" (zero-padded)
printf("%05.3d", 42);    // "  042" (space-padded, 3 digit precision)
printf("%05.0d", 0);     // "     " (5 spaces, nothing for 0)
```

---

## 9. Code Walkthrough Examples

### Example 1: `ft_printf("%05d", -42)` → `-0042`

**Step-by-step execution:**

1. **Parse format:** `%05d`
   - Flags: `zero = 1`
   - Width: `5`
   - Precision: `-1` (not specified)
   - Specifier: `d`

2. **Get argument:** `n = -42`

3. **Calculate lengths:**
   - `nb = 42` (absolute value)
   - `digit_len = 2` (digits in 42)
   - `sign = '-'`
   - `num_len = 2` (no precision adjustment)
   - `total_len = 2 + 1 = 3` (digits + sign)

4. **Determine padding:**
   - `zero = 1`, `minus = 0`, `precision = -1`
   - Use zero-padding path

5. **Render (zero-padding path):**
   - Print sign: `-` (count = 1)
   - Print zero-padding: `width - total_len = 5 - 3 = 2` zeros → `00` (count = 3)
   - Print digits: `42` (count = 5)

**Output:** `-0042`

---

### Example 2: `ft_printf("%#10x", 255)` → `0xff`

**Step-by-step execution:**

1. **Parse format:** `%#10x`
   - Flags: `hash = 1`
   - Width: `10`
   - Precision: `-1`
   - Specifier: `x`

2. **Get argument:** `n = 255`

3. **Calculate lengths:**
   - `digit_len = 2` (ff)
   - `prefix_len = 2` (0x, because hash=1 and n!=0)
   - `num_len = 2`
   - `total_len = 2 + 2 = 4`

4. **Determine padding:**
   - `zero = 0` → space-padding path

5. **Render (space-padding path):**
   - Print space-padding: `10 - 4 = 6` spaces → `      ` (count = 6)
   - Print prefix: `0x` (count = 8)
   - Print hex digits: `ff` (count = 10)

**Output:** `0xff`

---

### Example 3: `ft_printf("%-10.3s", "hello")` → `hel`

**Step-by-step execution:**

1. **Parse format:** `%-10.3s`
   - Flags: `minus = 1`
   - Width: `10`
   - Precision: `3`
   - Specifier: `s`

2. **Get argument:** `s = "hello"`

3. **Calculate lengths:**
   - `len = 5` (strlen of "hello")
   - `print_len = 3` (precision < len, so truncate)

4. **Render (left-align path):**
   - Print string content: `hel` (3 chars, count = 3)
   - Print space-padding: `10 - 3 = 7` spaces → `       ` (count = 10)

**Output:** `hel`

---

## 10. Practice Exercises

### Predict the Output

Try to predict the output before checking the answers.

1. `ft_printf("[%10d]", 42)`
2. `ft_printf("[%-10d]", 42)`
3. `ft_printf("[%010d]", 42)`
4. `ft_printf("[%+d]", 42)`
5. `ft_printf("[% d]", 42)`
6. `ft_printf("[%5.3d]", 42)`
7. `ft_printf("[%.0d]", 0)`
8. `ft_printf("[%5.0d]", 0)`
9. `ft_printf("[%#x]", 0)`
10. `ft_printf("[%#8x]", 255)`
11. `ft_printf("[%s]", NULL)`
12. `ft_printf("[%10.3s]", "hello")`
13. `ft_printf("[%p]", NULL)`
14. `ft_printf("[%05d]", -42)`
15. `ft_printf("[%+05d]", 42)`

<details>
<summary>Click to reveal answers</summary>

1. `[        42]` - Right-aligned, width 10
2. `[42        ]` - Left-aligned, width 10
3. `[0000000042]` - Zero-padded, width 10
4. `[+42]` - Plus flag forces sign
5. `[ 42]` - Space before positive
6. `[  042]` - Width 5, precision 3 (3 digits min)
7. `[]` - Zero with precision 0 prints nothing
8. `[     ]` - 5 spaces, nothing for the zero
9. `[0]` - Hash with 0 has no prefix
10. `[    0xff]` - Width 8 with prefix
11. `[(null)]` - NULL string handling
12. `[       hel]` - Width 10, precision 3 truncates
13. `[(nil)]` - NULL pointer handling
14. `[-0042]` - Sign before zeros
15. `[+0042]` - Plus sign before zeros

</details>

### Flag Combination Challenges

For each scenario, determine the correct format string:

1. Print integer `42` as `+00042` (6 chars total)
2. Print `255` as `0x000000ff` (10 chars total)
3. Print `"hello"` left-aligned in 10-char field: `hello`
4. Print first 3 chars of `"hello"` right-aligned in 8-char field: `hel`
5. Print `-7` zero-padded to width 5: `-0007`

<details>
<summary>Click to reveal answers</summary>

1. `%+06d` or `%+.5d` (both produce `+00042`)
2. `%#010x` (width 10, zero-padded with prefix)
3. `%-10s`
4. `%8.3s`
5. `%05d`

</details>

---

## Quick Reference Card

```
Format: %[flags][width][.precision]specifier

FLAGS:
  -   Left-align
  0   Zero-pad (numbers only, if no precision)
  #   Alternate form (0x for hex)
  ' ' Space before positive
  +   Always show sign

SPECIFIERS:
  c   Character
  s   String (NULL → "(null)")
  p   Pointer (NULL → "(nil)")
  d/i Signed integer
  u   Unsigned integer
  x/X Hexadecimal (lower/upper)
  %   Literal percent

RULES:
  • minus (-) disables zero (0)
  • plus (+) overrides space ( )
  • precision overrides zero-padding
  • precision 0 + value 0 = empty output
  • hash (#) + hex 0 = no prefix
```

---

_This study guide is for educational purposes to understand the ft_printf implementation._
