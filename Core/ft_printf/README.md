# ft_printf

**Because ft_putnbr() and ft_putstr() aren't enough** - A custom implementation of the printf function from libc, handling variable arguments and multiple format specifiers.

## Project Information

| Field | Description |
|-------|-------------|
| **Program Name** | `libftprintf.a` |
| **Files to Submit** | `Makefile`, `*.h`, `*/*.h`, `*.c`, `*/*.c` |
| **Makefile Targets** | `NAME`, `all`, `clean`, `fclean`, `re` |
| **External Functions** | `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end` |
| **Libft Authorized** | Yes |
| **Description** | Write a library that contains ft_printf(), a function that will mimic the original printf() |

## Function Prototype
```c
int ft_printf(const char *format, ...);
```

## 📋 Mandatory Conversions Implemented

| Conversion | Description | Example |
|------------|-------------|---------|
| `%c` | Prints a single character | `ft_printf("%c", 'A')` → `A` |
| `%s` | Prints a string | `ft_printf("%s", "hello")` → `hello` |
| `%p` | Prints a void pointer in hexadecimal | `ft_printf("%p", ptr)` → `0x7ffeeb39a820` |
| `%d` | Prints a decimal (base 10) number | `ft_printf("%d", 42)` → `42` |
| `%i` | Prints an integer in base 10 | `ft_printf("%i", -42)` → `-42` |
| `%u` | Prints an unsigned decimal number | `ft_printf("%u", 255)` → `255` |
| `%x` | Prints hexadecimal lowercase | `ft_printf("%x", 255)` → `ff` |
| `%X` | Prints hexadecimal uppercase | `ft_printf("%X", 255)` → `FF` |
| `%%` | Prints a percent sign | `ft_printf("%%")` → `%` |

## 🏗️ Architecture Overview

### Core Components
- **`ft_printf()`** - Main function that parses format string and processes conversions
- **Parser** - Handles format string and identifies conversion specifiers
- **Conversion Handlers** - Individual functions for each conversion type
- **Utils** - Helper functions for number conversions, string operations

### Key Design Features
- **Variable Arguments** - Uses `stdarg.h` for handling `...` parameters
- **Modular Design** - Separate functions for each conversion type
- **Memory Efficient** - Minimal heap allocation, proper memory management
- **Extensible** - Easy to add new conversions or bonus features

## 🛠️ Build Instructions

```bash
# Compile the library
make

# Clean object files
make clean

# Full clean (objects + library)
make fclean

# Rebuild
make re
```

## 📝 Usage Example

```c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    count = ft_printf("Hello %s! Number: %d, Hex: %x\n", "world", 42, 255);
    ft_printf("Printed %d characters\n", count);
    return (0);
}
```

Compile with:
```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf
```

## 🧪 Testing Strategy

### Basic Functionality Tests
```c
// Character and string
ft_printf("Char: %c, String: %s\n", 'A', "test");

// Numbers
ft_printf("Decimal: %d, Integer: %i, Unsigned: %u\n", 42, -42, 255);

// Pointers and hex
int x = 42;
ft_printf("Pointer: %p, Hex lower: %x, Hex upper: %X\n", &x, 255, 255);

// Percent sign
ft_printf("100%% complete\n");
```

### Edge Case Testing
```c
// NULL pointer for %s
ft_printf("NULL string: %s\n", NULL);

// Zero and negative numbers
ft_printf("Zero: %d, Negative: %d\n", 0, -42);

// Maximum values
ft_printf("Max int: %d, Max unsigned: %u\n", INT_MAX, UINT_MAX);
```

### Comparison with Original printf
```c
#include <stdio.h>

void compare_printf(void)
{
    int my_count, std_count;
    
    my_count = ft_printf("ft_printf: %s %d %x\n", "test", 42, 255);
    std_count = printf("printf:    %s %d %x\n", "test", 42, 255);
    
    printf("ft_printf returned: %d\n", my_count);
    printf("printf returned:    %d\n", std_count);
}
```

## 🚀 Premium Features - Implementation Highlights

### 1. Robust Error Handling
```c
// Handles NULL format string gracefully
count = ft_printf(NULL); // Returns -1 like standard printf

// Manages memory allocation failures
// Properly frees allocated memory on error
```

### 2. Efficient Number Conversion
```c
// Custom number to string conversion without stdlib
// Handles all integer types: int, unsigned, hex
// Supports both lowercase and uppercase hex
```

## 🎯 Evaluation Demonstration

During defense, be prepared to:

### Explain Key Concepts
```c
// Variable arguments usage
va_list args;
va_start(args, format);
// Process each argument
va_end(args);

// Return value calculation
// Each conversion returns character count
```

### Demonstrate Functionality
```bash
# Show basic conversions work
./test_basic

# Prove return values match standard printf
./test_return_values

# Demonstrate edge case handling
./test_edge_cases
```

### Answer Technical Questions
- **How do variable arguments work?**
- **What's the difference between %d and %i?**
- **How do you handle pointer conversion?**
- **What's your approach to number base conversion?**

## 📊 Performance Considerations

- **Minimal syscalls** - Buffers output where possible
- **Efficient algorithms** - Optimized number conversions
- **Memory management** - No leaks, proper error recovery
- **Code readability** - Clean, maintainable structure

## 🔧 Integration with Libft

Since libft is authorized, you can use:
- `ft_putchar_fd`, `ft_putstr_fd` for output
- `ft_itoa` for number conversions (or implement custom)
- `ft_strlen` for string operations
- Other utility functions as needed

## ⚠️ Important Notes

- **No buffer management** required (unlike original printf)
- **Return value** must match character count exactly
- **Memory leaks** will result in grade 0
- **Norm compliance** is strictly enforced
- **Test thoroughly** with various inputs and edge cases

---

**Pro Tip**: Start with the simplest conversions (`%c`, `%s`, `%%`) and gradually add more complex ones. Test each conversion thoroughly before moving to the next!
