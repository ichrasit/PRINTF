# ft_printf — A Custom Implementation of printf

---

*This project has been created as part of the 42 curriculum by [muhaoz](https://profile.intra.42.fr/users/muhaoz).*

---

## 📋 Table of Contents

1. [Description](#description)
2. [Features](#features)
3. [Instructions](#instructions)
4. [Supported Format Specifiers](#supported-format-specifiers)
5. [Algorithm & Data Structures](#algorithm--data-structures)
6. [Usage Examples](#usage-examples)
7. [Technical Details](#technical-details)
8. [Resources](#resources)
9. [AI Usage Disclosure](#ai-usage-disclosure)
10. [Project Structure](#project-structure)
11. [Acknowledgments](#acknowledgments)

---

## 📖 Description

**ft_printf** is a custom implementation of the standard C library function `printf`, developed as part of the 42 School curriculum. This project provides a fully functional recreation of the popular `printf` function with support for various format specifiers, enabling formatted output to the standard output stream.

### Project Goal

The primary objective of this project is to deepen understanding of:

- **Variadic functions** in C and the `<stdarg.h>` interface
- **Variable argument list manipulation** (`va_list`, `va_start`, `va_arg`, `va_end`)
- **Formatted output processing** and format string parsing
- **Low-level I/O operations** using `write()` system call
- **Memory-safe string handling** and edge case management

### Brief Overview

The `ft_printf` function mimics the behavior of the standard library's `printf`, accepting a format string and a variable number of arguments. It parses the format string character by character, identifying format specifiers and dispatching appropriate conversion functions. The implementation handles edge cases such as null pointers, negative integers, and special characters while maintaining exact compatibility with the original `printf` return values.

---

## ✨ Features

| Feature | Status | Description |
|---------|--------|-------------|
| Character output (`%c`) | ✅ Implemented | Prints a single character |
| String output (`%s`) | ✅ Implemented | Prints a null-terminated string |
| Pointer address (`%p`) | ✅ Implemented | Prints memory address in hexadecimal |
| Decimal integer (`%d`, `%i`) | ✅ Implemented | Prints signed decimal integer |
| Unsigned integer (`%u`) | ✅ Implemented | Prints unsigned decimal integer |
| Hexadecimal lowercase (`%x`) | ✅ Implemented | Prints unsigned integer in base-16 (a-f) |
| Hexadecimal uppercase (`%X`) | ✅ Implemented | Prints unsigned integer in base-16 (A-F) |
| Literal percent (`%%`) | ✅ Implemented | Prints a literal percent sign |
| Return value compatibility | ✅ Implemented | Returns exact character count like original |

---

## 🛠️ Instructions

### Prerequisites

- **Operating System**: Linux/macOS (Unix-like systems)
- **Compiler**: GCC or Clang (C99 standard or later)
- **Build Tools**: GNU Make

### Compilation

To compile the library, navigate to the project directory and run:

```bash
cd printf
make
```

This will generate a static library file `libftprintf.a`.

### Compilation Flags

The Makefile uses the following compilation flags for maximum code quality:

| Flag | Description |
|------|-------------|
| `-Wall` | Enable all common warnings |
| `-Wextra` | Enable extra warning flags |
| `-Werror` | Treat warnings as errors |

### Building the Test Program

To compile and run the test suite that compares `ft_printf` with the original `printf`:

```bash
make test
```

Or manually:

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test_program
./test_program
```

### Cleaning Build Artifacts

```bash
make clean    # Remove object files
make fclean   # Remove object files and library
make re       # Rebuild everything from scratch
```

### Using in Your Project

To use `ft_printf` in your own projects:

1. Copy `ft_printf.c` and `ft_printf.h` to your project
2. Compile your code with `ft_printf.c`:

```bash
cc your_program.c ft_printf.c -o your_program
```

Or create a static library and link it:

```bash
cc -c ft_printf.c -o ft_printf.o
ar rcs libftprintf.a ft_printf.o
cc your_program.c -L. -lftprintf -o your_program
```

---

## 🔤 Supported Format Specifiers

| Specifier | Type | Description | Example Output |
|-----------|------|-------------|----------------|
| `%c` | `int` | Single character | `A` |
| `%s` | `char *` | String of characters | `Hello, World!` |
| `%p` | `void *` | Pointer address (hex) | `0x7fff5fbff8ac` |
| `%d` | `int` | Signed decimal integer | `-123` |
| `%i` | `int` | Signed integer (base 10) | `42` |
| `%u` | `unsigned int` | Unsigned decimal integer | `4294967295` |
| `%x` | `unsigned int` | Hexadecimal (lowercase) | `deadbeef` |
| `%X` | `unsigned int` | Hexadecimal (uppercase) | `DEADBEEF` |
| `%%` | None | Literal percent sign | `%` |

### Special Cases Handled

- **NULL string** (`%s` with NULL): Outputs `(null)`
- **NULL pointer** (`%p` with NULL): Outputs `(nil)`
- **Negative integers** (`%d`, `%i`): Outputs with leading `-` sign
- **Overflow values** (`INT_MAX`, `INT_MIN`, `UINT_MAX`): Handled correctly

---

## 🧮 Algorithm & Data Structures

### Algorithm Overview

The `ft_printf` implementation uses a **state-machine based parsing algorithm** with **recursive number conversion**. Here's a detailed breakdown:

#### 1. Format String Parsing (Main Loop)

```
Algorithm: ft_printf_main_loop
Input: format string s, variable arguments
Output: total characters written

1. Initialize va_list and set len = 0
2. For each character in s:
   a. If character != '%':
      - Write character directly to stdout
      - Increment len by 1
   b. If character == '%':
      - Look ahead at next character
      - If next char is '%': write literal '%'
      - Else: call dispatcher with format specifier
3. Return total len
```

#### 2. Format Specifier Dispatching

The `cheat_summon` function acts as a dispatcher, routing each format specifier to the appropriate handler:

```
Switch on specifier t:
  case 'c': → handle_char()
  case 's': → handle_string()
  case 'p': → handle_pointer()
  case 'd': → handle_signed_int()
  case 'i': → handle_signed_int()
  case 'u': → handle_unsigned_int()
  case 'x': → handle_hex_lower()
  case 'X': → handle_hex_upper()
```

#### 3. Recursive Number Conversion (cheat_hex_magic)

This is the core algorithm for converting numbers to their string representation:

```
Algorithm: number_to_string(n, base)
Input: unsigned long n, base string
Output: character count

1. Calculate base length
2. If n >= base_length:
   - Recursively call number_to_string(n / base_length, base)
   - Accumulate returned count
3. Write single digit: b[n % base_length]
4. Return total characters written
```

**Why Recursion?** The recursive approach naturally handles numbers of arbitrary length by processing digits from most significant to least significant. The recursion unwinds in the correct order, eliminating the need for an intermediate buffer.

### Data Structures

#### No Dynamic Data Structures

This implementation intentionally avoids dynamic data structures (arrays, linked lists, etc.) for several reasons:

1. **Memory Efficiency**: No heap allocations required
2. **Performance**: Direct system call (`write`) without intermediate buffers
3. **Simplicity**: Cleaner, more maintainable code
4. **Stack-based Processing**: All processing happens on the call stack

#### Recursion as Implicit Data Structure

Instead of storing digits in an array, the recursive call stack acts as an implicit data structure:

```
Example: Converting 123 to string "123"

Recursive calls (before writing):
  cheat_hex_magic(123, "0123456789")
    └─ cheat_hex_magic(12, "0123456789")
        └─ cheat_hex_magic(1, "0123456789")
            └─ base case reached (n < 10)

Writing (as calls unwind):
  1 → 2 → 3 → "123"
```

### Time & Space Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| String output (`%s`) | O(n) | O(1) |
| Character output (`%c`) | O(1) | O(1) |
| Integer to string (`%d`, `%i`, `%u`) | O(log₁₀ n) | O(log₁₀ n) stack |
| Hex conversion (`%x`, `%X`) | O(log₁₆ n) | O(log₁₆ n) stack |
| Pointer output (`%p`) | O(log₁₆ n) | O(log₁₆ n) stack |

### Design Decisions & Justifications

#### Decision 1: Why `unsigned long` for Pointer Handling?

Pointers on 64-bit systems can exceed `unsigned int` range. Using `unsigned long` ensures:
- Compatibility with both 32-bit and 64-bit architectures
- Proper handling of memory addresses across different platforms
- Consistent behavior with glibc's `printf`

#### Decision 2: Why Recursion Instead of Iteration?

While iterative solutions exist, recursion provides:
- **Natural digit order**: No need to reverse the digit buffer
- **Zero initialization**: No buffer setup required
- **Code clarity**: Self-documenting algorithm structure

The maximum recursion depth is bounded by the number of digits (max 20 for 64-bit numbers), which is safe for stack usage.

#### Decision 3: Why Return Character Count?

The return value of `printf` is crucial for:
- Error detection in chained operations
- Formatted output to fixed-size buffers
- Logging and progress tracking
- Compatibility with existing code patterns

---

## 💡 Usage Examples

### Basic Examples

```c
#include "ft_printf.h"

int main(void)
{
    // String formatting
    ft_printf("Hello, %s!\n", "World");
    // Output: Hello, World!

    // Integer formatting
    ft_printf("The answer is %d\n", 42);
    // Output: The answer is 42

    // Hexadecimal formatting
    ft_printf("Hex: %x, Upper: %X\n", 255, 255);
    // Output: Hex: ff, Upper: FF

    // Pointer formatting
    int x = 42;
    ft_printf("Address: %p\n", &x);
    // Output: Address: 0x7fff5fbff8ac (address varies)

    return 0;
}
```

### Complex Formatting

```c
#include "ft_printf.h"

int main(void)
{
    // Multiple specifiers
    ft_printf("%s %d %s\n", "Number:", 42, "is the answer");
    // Output: Number: 42 is the answer

    // Negative numbers
    ft_printf("Temperature: %d°C\n", -15);
    // Output: Temperature: -15°C

    // Unsigned handling
    ft_printf("Max unsigned: %u\n", 4294967295);
    // Output: Max unsigned: 4294967295

    // Percent literal
    ft_printf("Success rate: 100%%\n");
    // Output: Success rate: 100%

    return 0;
}
```

### Return Value Usage

```c
#include "ft_printf.h"

int main(void)
{
    int len;

    // Capture return value
    len = ft_printf("Hello\n");
    ft_printf("Characters written: %d\n", len);
    // Output: Hello
    //         Characters written: 6

    return 0;
}
```

### Edge Cases

```c
#include "ft_printf.h"

int main(void)
{
    // NULL string
    ft_printf("Null: %s\n", NULL);
    // Output: Null: (null)

    // NULL pointer
    ft_printf("NULL ptr: %p\n", NULL);
    // Output: NULL ptr: (nil)

    // Integer limits
    ft_printf("INT_MAX: %d\n", 2147483647);
    ft_printf("INT_MIN: %d\n", -2147483648);
    // Output: INT_MAX: 2147483647
    //         INT_MIN: -2147483648

    return 0;
}
```

---

## 🔧 Technical Details

### Header File Structure

```c
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>    // Variadic argument macros
# include <unistd.h>     // write() system call
# include <stdint.h>    // Fixed-width integer types

int ft_printf(const char *s, ...);

#endif
```

### Function Signature Compatibility

The function signature exactly matches the standard library:

```c
int ft_printf(const char *format, ...);
```

This ensures:
- Binary compatibility with code written for `printf`
- Transparent replacement capability
- Standard calling convention compliance

### Platform Considerations

| Aspect | Implementation Choice | Reason |
|--------|----------------------|--------|
| System call | `write(1, ...)` | Direct stdout, no buffering |
| Integer type | `long` for intermediate | Avoid overflow in negation |
| Pointer type | `unsigned long` | Handle 64-bit addresses |

---

## 📚 Resources

### Official Documentation

- [GNU libc Manual: Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output-Functions.html)
- [ISO C11 Standard (draft)](https://port70.net/~nsz/c/c11/n1570.html) — Section 7.21.6.4 (The printf function)
- [POSIX printf specification](https://pubs.opengroup.org/onlinepubs/9699919799/functions/printf.html)

### Variadic Functions

- [C99 Standard: Variable Arguments `<stdarg.h>`](https://en.cpreference.com/w/c/variadic)
- [GCC Built-in Variadic Functions](https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html)

### Related 42 Projects

- [libft](https://github.com/42School/libft) — Foundation library with string and memory functions
- [get_next_line](https://github.com/42School/get_next_line) — Line reading utility

### External References

| Resource | Description |
|----------|-------------|
| [Linux man pages: printf(3)](https://man7.org/linux/man-pages/man3/printf.3.html) | Linux system documentation |
| [What is printf doing?](https://www.slac.stanford.edu/~komron/C/printf.html) | Technical explanation |
| [Format String Attack](https://owasp.org/www-community/attacks/Format_string_attack) | Security considerations |

---

## 🤖 AI Usage Disclosure

### Tasks Where AI Was Utilized

This section documents how AI tools were used during the development of this project.

#### 1. Understanding Variadic Arguments

**Task**: Understanding the `<stdarg.h>` interface and proper `va_list` usage.

**AI Contribution**: AI explained the semantics of `va_start`, `va_arg`, and `va_end` macros, particularly edge cases such as:
- Type promotion rules for variadic arguments
- Portable ways to handle pointer arguments
- Proper cleanup with `va_end`

#### 2. Recursive Number Conversion

**Task**: Implementing number-to-string conversion without using `itoa()` or similar functions.

**AI Contribution**: AI suggested the recursive approach for digit extraction, explaining how recursion naturally handles the "most significant digit first" requirement without requiring a reverse operation.

#### 3. Edge Case Handling

**Task**: Ensuring correct handling of NULL pointers, INT_MIN, and other boundary conditions.

**AI Contribution**: AI identified potential integer overflow issues with `INT_MIN` negation and recommended using `long` as an intermediate type.

#### 4. README Documentation

**Task**: Creating comprehensive project documentation.

**AI Contribution**: AI assisted in structuring this README with proper sections, formatting, and technical explanations.

### Code Implementation Note

All code in `ft_printf.c` was written manually to ensure:
- Understanding of underlying concepts
- Compliance with 42 coding standards
- Proper handling of edge cases
- Performance optimization

AI was used as a learning tool and documentation assistant, not for code generation.

---

## 📁 Project Structure

```
printf/
├── ft_printf.h      # Header file with function declarations
├── ft_printf.c     # Main implementation
├── Makefile        # Build configuration
├── main.c          # Test suite comparing with original printf
├── abc.c           # Additional test code (strjoiner example)
├── README.md       # This documentation
├── libftprintf.a   # Compiled static library (generated)
├── ft_printf.o     # Object file (generated)
└── a.out           # Test executable (generated)
```

### File Descriptions

| File | Purpose |
|------|---------|
| `ft_printf.h` | Public API declarations and includes |
| `ft_printf.c` | Complete implementation of ft_printf |
| `Makefile` | Automated build system |
| `main.c` | Comprehensive test suite |
| `abc.c` | Experimental/test code (not part of main build) |

---

## 🙏 Acknowledgments

### 42 School

This project was developed as part of the curriculum at [42 School](https://42.fr/en/homepage/), a peer-to-peer innovative and inclusive educational methodology.

### The 42 Community

Special thanks to the 42 community for:
- Providing a challenging and rewarding learning environment
- Encouraging collaboration and knowledge sharing
- Promoting self-directed learning and problem-solving skills

### Peer Contributors

Thanks to all 42 students who have shared their knowledge and experiences, contributing to the collective learning journey.

---

## 📄 License

This project is for educational purposes as part of the 42 curriculum. All code follows the 42 School coding standards and guidelines.

---

## 📧 Contact

For questions, suggestions, or collaboration opportunities:

- **Author**: [muhaoz](https://profile.intra.42.fr/users/muhaoz)
- **Institution**: 42 School
- **Project**: ft_printf (Current)

---

<div align="center">

*"Talk is cheap. Show me the code." — Linus Torvalds*

</div>
