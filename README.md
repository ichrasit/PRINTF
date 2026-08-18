*This project has been created as part of the 42 curriculum by muhaoz.*

# ft_printf

> Because `ft_putnbr()` and `ft_putstr()` aren't enough.

A from-scratch reimplementation of the C standard library's `printf()`, compiled into a static library, `libftprintf.a`. Conversions are resolved through a constant-time function-pointer dispatch table rather than a chain of `if` / `else if` statements, and numeric formatting is built iteratively instead of recursively.

## Table of Contents

- [Description](#description)
- [Supported Conversions](#supported-conversions)
- [Instructions](#instructions)
- [Project Structure](#project-structure)
- [Architecture & Design Choices](#architecture--design-choices)
- [Resources](#resources)

## Description

`ft_printf` recreates the subset of `printf()` behavior required by the subject — it does not reimplement libc's internal buffering. It ships as a static library exposing a single public function:

```c
int ft_printf(const char *format, ...);
```

The format string is scanned once. Literal characters are written as-is; every `%` conversion is resolved by looking up the conversion character directly in a fixed-size table of function pointers, instead of testing it against each supported letter in turn.

The project is designed to stay within the constraints set by the subject: only `malloc`, `free`, `write`, and the `va_start` / `va_arg` / `va_copy` / `va_end` family are used, all allocations are freed, the archive is built with `ar` (no `libtool`), and the sources follow the 42 Norm.

## Supported Conversions

| Specifier | Description |
|:---:|---|
| `%c` | Single character |
| `%s` | String of characters (handles a `NULL` argument gracefully) |
| `%p` | `void *` pointer, printed in hexadecimal |
| `%d`, `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal integer, lowercase |
| `%X` | Unsigned hexadecimal integer, uppercase |
| `%%` | A literal percent sign |

## Instructions

### Build

```bash
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and the library
make re     # fclean, then make
```

### Link into another project

```bash
cc your_program.c -L. -lftprintf -o your_program
```

`ft_printf.h` needs to be on your include path, and `libftprintf.a` reachable by `-L`.

### Example

```c
#include "ft_printf.h"

int main(void)
{
    int answer = 42;

    ft_printf("Hello, %s! The answer is %d (0x%x).\n", "world", answer, answer);
    return (0);
}
```

## Project Structure

```
.
├── Makefile
├── ft_printf.h        # public header: prototype and shared declarations
├── ft_printf.c        # entry point, format-string parsing, dispatch table
├── ft_format_chars.c  # %c and %s handlers
├── ft_format_nums.c   # %d, %i and %u handlers
├── ft_format_hex.c    # %x, %X and %p handlers
├── ft_utils.c         # shared helper functions
└── main.c             # local test harness, not part of the library itself
```

## Architecture & Design Choices

### Function-pointer dispatch table

Rather than resolving a conversion character with a sequence of comparisons (`if (c == 's') ... else if (c == 'd') ...`), this project declares a 256-entry array of function pointers — one slot per possible `char` value — and fills in only the slots for supported conversions (`c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%`). Every other slot stays `NULL`.

Resolving a conversion is then a single array lookup, `table[(unsigned char)c]`, followed by a `NULL` check. Dispatch time stays constant no matter how many conversions are supported, and adding a new one later means writing and registering one handler rather than extending a conditional chain.

### Iterative number formatting

Base conversion is often written recursively — print `n / base` first, then the last digit. That's compact, but it adds one stack frame per digit for no real benefit here.

This project instead:

1. Computes the digit count (and sign, for signed conversions) up front.
2. Fills a fixed local buffer, `char buf[21]` — large enough for the widest 64-bit value, its sign, and the terminator — back-to-front using division and modulo.
3. Writes the completed buffer in a single `write` call.

Stack usage stays constant regardless of the size of the number being printed, and each number costs one `write` instead of one per digit.

## Resources

Classic references related to this project's topic:

- `man 3 printf` — manual page for the libc function this project reimplements.
- `man 3 stdarg` — manual page for `va_start`, `va_arg`, `va_copy` and `va_end`.
- [cppreference — Variadic functions](https://en.cppreference.com/c/variadic) — reference documentation for `<stdarg.h>`.
- The `ft_printf` subject PDF distributed by 42.

*(Add or swap in whatever you actually read while building this — only list sources you personally used.)*

### AI usage disclosure

- **This README**: an AI assistant (Claude) reorganized an existing draft into the sections required by the subject (Description, Instructions, Resources, and this disclosure), reformatted the specifier list into a table, and wrote the Project Structure and build sections. It did not read, write, or modify any `.c` or `.h` file.
- **Source code**: *fill in here, honestly — e.g. "no AI assistance," or the specific task/file/date if you did ask for help.*