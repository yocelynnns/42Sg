# Libft

**Your very first own library** - A custom C library reimplementing standard functions and adding useful utilities for 42 projects.

## Project Information

| Field | Description |
|-------|-------------|
| **Program Name** | `libft.a` |
| **Files to Submit** | `Makefile`, `libft.h`, `ft_*.c` |
| **Makefile Targets** | `NAME`, `all`, `clean`, `fclean`, `re`, `bonus` |
| **External Functions** | `malloc`, `free`, `write` |
| **Description** | Create your own library: a collection of functions that will serve as a useful tool throughout your cursus. |

## Architecture Overview

### Part 1 - Libc Functions (Mandatory)
Reimplementation of standard C library functions with `ft_` prefix:

**Character Classification:**
- `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`

**String Manipulation:**
- `ft_strlen`, `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`
- `ft_strlcpy`, `ft_strlcat`, `ft_toupper`, `ft_tolower`
- `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_memchr`, `ft_memcmp`
- `ft_strnstr`, `ft_atoi`

**Memory Allocation:**
- `ft_calloc`, `ft_strdup`

### Part 2 - Additional Functions (Mandatory)
Extended utility functions for string and memory operations:

- **String Operations:** `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`
- **String Iteration:** `ft_strmapi`, `ft_striteri`
- **File Descriptor Output:** `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

### Part 3 - Bonus Functions (Linked Lists)
Complete linked list implementation:

- **List Creation:** `ft_lstnew`
- **List Manipulation:** `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstdelone`, `ft_lstclear`
- **List Information:** `ft_lstsize`, `ft_lstlast`
- **List Iteration:** `ft_lstiter`, `ft_lstmap`

## Build

```bash
# Compile mandatory part
make

# Compile mandatory + bonus parts
make bonus

# Clean object files
make clean

# Full clean (objects + library)
make fclean

# Rebuild
make re
```

## Usage

Include in your projects:
```c
#include "libft.h"

// Compile with:
cc -Wall -Wextra -Werror main.c -L. -lft
```
## 🎯 Demonstration Guide

During evaluation, showcase these key features:

```bash
# Show library compilation
make && make bonus

# Demonstrate basic functionality
echo "Test string" | ./test_program

# Show memory cleanliness with valgrind
valgrind --leak-check=full ./test_program

```

## Testing Strategy

**Comprehensive validation approach:**
- **Unit Tests:** Individual function testing with edge cases
- **Integration Tests:** Function combinations and real-world scenarios
- **Memory Tests:** Valgrind checks for leaks and errors
- **Performance Tests:** Benchmark against standard libc functions

**Key test cases:**
- NULL pointer handling
- Empty string operations
- Boundary conditions
- Memory allocation failures
- Integer overflow scenarios

## Notes / Implementation Tips

- **Start Simple:** Begin with character classification functions (isalpha, etc.)
- **Memory Management:** Pay special attention to malloc/calloc/strdup implementations
- **Edge Cases:** Test thoroughly with NULL pointers, empty strings, and boundary values
- **Linked Lists:** Implement bonus functions after completing mandatory part
- **Norm Compliance:** Ensure all code follows 42 Norm standards

## File Structure
```
libft/
├── Makefile
├── libft.h
├── ft_*.c (mandatory functions)
├── ft_*_bonus.c (bonus linked list functions)
└── README.md
```

This library serves as the foundation for all future C projects at 42. Build it carefully and test it thoroughly - you'll be using it extensively throughout your curriculum!
