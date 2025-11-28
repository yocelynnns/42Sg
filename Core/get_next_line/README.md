# Get Next Line

**Reading a line from a file descriptor is far too tedious** - A function that reads a line from a file descriptor, handling multiple file descriptors and various buffer sizes efficiently.

## Project Information

| Field | Description |
|-------|-------------|
| **Function Name** | `get_next_line` |
| **Prototype** | `char *get_next_line(int fd)` |
| **Files to Submit** | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` |
| **Bonus Files** | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` |
| **External Functions** | `read`, `malloc`, `free` |
| **Forbidden** | `libft`, `lseek`, global variables |

## Function Prototype
```c
char *get_next_line(int fd);
```

## 📋 Features

### Mandatory Requirements
- ✅ Returns one line at a time from a file descriptor
- ✅ Includes terminating `\n` character (except at EOF)
- ✅ Returns `NULL` when nothing left to read or on error
- ✅ Works with files and standard input
- ✅ Uses static variables to maintain state between calls
- ✅ Compiles with `-D BUFFER_SIZE=n` flag

### Bonus Features Implemented
- ✅ **Single static variable** implementation
- ✅ **Multiple file descriptor** management
- ✅ Can read from different FDs interchangeably without losing state

## 🏗️ Architecture Overview

### Core Components
- **`get_next_line()`** - Main function that returns next line
- **Static Buffer Management** - Maintains leftover data between calls
- **Line Extraction** - Finds and returns complete lines
- **Multiple FD Support** - Tracks reading state for each file descriptor

### Key Design Features
- **Single Static Variable** - Efficient memory usage
- **Arbitrary BUFFER_SIZE** - Works with any buffer size (1 to 10000000+)
- **Memory Efficient** - Only reads necessary data, minimal allocations
- **Robust Error Handling** - Proper cleanup on errors

## 🛠️ Build Instructions

### Mandatory Part
```bash
# Compile with specific buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Or use provided Makefile
make
```

### Bonus Part
```bash
# Compile bonus version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c

# Or use Makefile bonus rule
make bonus
```

## 📝 Usage Examples

### Basic File Reading
```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Multiple File Descriptors (Bonus)
```c
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;
    
    // Read interchangeably from both files
    line = get_next_line(fd1);  // First line from file1
    line = get_next_line(fd2);  // First line from file2  
    line = get_next_line(fd1);  // Second line from file1
    line = get_next_line(fd2);  // Second line from file2
    
    close(fd1);
    close(fd2);
    return (0);
}
```

### Standard Input
```c
#include "get_next_line.h"

int main(void)
{
    char *line;
    
    printf("Enter text (Ctrl+D to end):\n");
    while ((line = get_next_line(0)) != NULL)  // FD 0 = stdin
    {
        printf("You entered: %s", line);
        free(line);
    }
    return (0);
}
```

## 🧪 Comprehensive Testing Strategy

### Buffer Size Tests
```bash
# Test with various buffer sizes
cc -D BUFFER_SIZE=1 get_next_line*.c test.c
cc -D BUFFER_SIZE=10 get_next_line*.c test.c
cc -D BUFFER_SIZE=42 get_next_line*.c test.c
cc -D BUFFER_SIZE=9999 get_next_line*.c test.c
cc -D BUFFER_SIZE=1000000 get_next_line*.c test.c
```

### Edge Case Testing
```c
// Empty file
// Files with no newline at end
// Very long lines
// Mixed line endings
// Binary files (undefined behavior)
// Invalid file descriptors
```

### Multiple FD Testing
```c
// Test bonus functionality
void test_multiple_fd(void)
{
    int fd1, fd2, fd3;
    char *line;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    
    // Read lines interchangeably
    line = get_next_line(fd1);
    line = get_next_line(fd2); 
    line = get_next_line(fd3);
    line = get_next_line(fd1);
    // ... etc
    
    close(fd1);
    close(fd2);
    close(fd3);
}
```

## 🎯 Evaluation Demonstration

### Key Points to Demonstrate
```c
// Show it works with different buffer sizes
// Demonstrate multiple FD management (bonus)
// Prove no memory leaks with valgrind
// Show proper newline handling
```

### Expected Questions & Answers
- **How do static variables work?** - Maintain state between function calls
- **How do you handle multiple FDs?** - Linked list tracking each FD's buffer
- **What happens with BUFFER_SIZE=1?** - Many read calls but still works
- **How about very large BUFFER_SIZE?** - Fewer reads, efficient for large files
- **Memory management?** - All allocated memory properly freed

### Test Commands for Defense
```bash
# Memory leak check
valgrind --leak-check=full ./gnl_test

# Multiple FD test
./multiple_fd_test

# Various buffer sizes
./buffer_size_test

# Compare with standard input
echo -e "line1\nline2\nline3" | ./gnl_stdin_test
```

## 🔧 Technical Implementation Details

### Algorithm Overview
1. **Check static buffer** for leftover data from previous call
2. **Read from FD** if no complete line in buffer
3. **Extract complete line** up to newline
4. **Save leftover data** in static buffer for next call
5. **Return line** (must be freed by caller)

### Bonus Implementation
- **Linked list** of file descriptor data
- **Each FD** maintains its own buffer state
- **Automatic cleanup** when FD is closed
- **Efficient lookup** for FD data

## ⚠️ Important Notes

- **Caller must free** returned strings
- **Undefined behavior** for binary files
- **No lseek allowed** - must read sequentially
- **Global variables forbidden** - use static variables instead
- **Test thoroughly** with edge cases and various buffer sizes

---

**Pro Tip**: The key to a successful GNL is efficient buffer management and proper handling of the static variable. Test extensively with BUFFER_SIZE=1 as it's the most challenging case!
