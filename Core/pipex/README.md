# Pipex

**Handling UNIX pipes** - A C program that replicates the behavior of shell pipes, allowing command execution with input/output redirection.

## Project Information

| Field | Description |
|-------|-------------|
| **Program Name** | `pipex` |
| **Files** | `Makefile`, `*.h`, `*.c` |
| **Makefile Targets** | `NAME`, `all`, `clean`, `fclean`, `re` |
| **Arguments** | `file1 cmd1 cmd2 file2` |
| **External Functions** | `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid` |
| **Libft Authorized** | Yes |

## 🎯 Project Overview

Pipex replicates the behavior of the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

The program:
- Takes input from `file1`
- Executes `cmd1` with the input
- Pipes the output to `cmd2`
- Writes the final output to `file2`

## 🏗️ Architecture & Implementation

### File Structure
```
pipex/
├── Makefile
├── pipex.h           # Header file with prototypes and includes
├── pipex.c           # Main program, process management
├── utils.c           # Command execution and path finding
├── ft_libft.c        # Custom libft functions
└── ft_split.c        # String splitting utility
```

### Core Components

#### Main Process Flow (`pipex.c`)
```c
int main(int argc, char **argv, char **env)
{
    // Argument validation
    // Pipe creation
    // Fork child process for cmd1
    // Parent process handles cmd2
    // Wait for completion
}
```

#### Command Execution System (`utils.c`)
- **Path Resolution**: Finds command in PATH environment
- **Command Splitting**: Parses command strings into executable format
- **Absolute Path Support**: Handles commands with full paths
- **Error Handling**: Comprehensive error checking and reporting

## 🛠️ Build & Usage

### Compilation
```bash
make
```

### Basic Usage
```bash
./pipex file1 "cmd1" "cmd2" file2
```

### Examples
```bash
# Equivalent to: < input.txt grep "hello" | wc -l > output.txt
./pipex input.txt "grep hello" "wc -l" output.txt

# Equivalent to: < file.txt ls -l | head -5 > result.txt
./pipex file.txt "ls -l" "head -5" result.txt

# Equivalent to: < data.txt cat | sort > sorted.txt
./pipex data.txt "cat" "sort" sorted.txt
```

## 🔧 Technical Implementation

### Process Management
```c
void childp(char **argv, int *pipe_fd, char **env)
{
    // Handles cmd1 execution
    // Redirects stdin from file1
    // Redirects stdout to pipe
}

void parentp(char **argv, int *pipe_fd, char **env)
{
    // Handles cmd2 execution  
    // Redirects stdin from pipe
    // Redirects stdout to file2
}
```

### Command Execution
```c
void execute(char *argv, char **envp)
{
    // Determines if command has absolute path
    // Splits command and arguments
    // Finds command in PATH
    // Executes with execve
}
```

### PATH Resolution
```c
char *find_path(char *cmd, char **envp)
{
    // Extracts PATH from environment
    // Searches each directory in PATH
    // Checks command accessibility
    // Returns full path to executable
}
```

## 📋 Key Features

### Mandatory Requirements
- ✅ **Process Management**: Fork, pipe, and process coordination
- ✅ **File Redirection**: Input from file1, output to file2
- ✅ **Command Execution**: PATH resolution and execve
- ✅ **Error Handling**: Comprehensive error messages and cleanup
- ✅ **Memory Management**: No leaks, proper resource freeing

### Command Support
- **Relative Commands**: `ls`, `grep`, `wc`, etc. (found in PATH)
- **Absolute Commands**: `/bin/ls`, `/usr/bin/grep`, etc.
- **Command Arguments**: `ls -l`, `grep "pattern"`, `wc -l`

## 🧪 Testing & Validation

### Basic Functionality Tests
```bash
# Test with simple commands
./pipex input.txt "cat" "wc -l" output.txt

# Test with grep and word count
./pipex textfile.txt "grep error" "wc -w" result.txt

# Test with sort
./pipex data.txt "sort" "uniq" unique_data.txt
```

### Error Handling Tests
```bash
# Non-existent input file
./pipex nofile.txt "cat" "wc -l" output.txt

# Invalid command
./pipex input.txt "invalid_cmd" "wc -l" output.txt

# Insufficient arguments
./pipex file1 cmd1
```

### Comparison with Shell
```bash
# Test equivalence with shell command
./pipex input.txt "ls -l" "head -5" output.txt
< input.txt ls -l | head -5 > shell_output.txt
diff output.txt shell_output.txt
```

## 🚀 Implementation Highlights

### Robust Error Handling
```c
// Comprehensive error checking at each step
if (infile == -1) {
    perror("Error Infile");
    exit(1);
}
```

### Memory Management
```c
void free_mem(char **tab)
{
    // Properly frees 2D arrays
    // Prevents memory leaks
}
```

### PATH Resolution Algorithm
1. Extract PATH from environment variables
2. Split PATH into individual directories
3. Check each directory for the command
4. Return first accessible path found

## 🎯 Evaluation Guide

### During Defense
1. **Explain Process Flow**: Fork, pipe, redirection sequence
2. **Demonstrate Command Execution**: PATH resolution, execve usage
3. **Show Error Handling**: Various error scenarios
4. **Discuss Memory Management**: Allocation and freeing strategy

### Key Technical Points
- **Process Creation**: fork() and waitpid() usage
- **File Descriptor Management**: dup2() for redirection
- **Command Parsing**: Argument splitting and preparation
- **PATH Searching**: Efficient command location

## ⚠️ Important Notes

- **Argument Count**: Exactly 4 arguments required
- **File Permissions**: Input file must be readable, output file will be created/truncated
- **Command Availability**: Commands must be in PATH or use absolute paths
- **Error Reporting**: Uses perror() for system error messages
- **Exit Codes**: Returns appropriate exit status based on command execution

---

**Pro Tip**: The key to pipex is understanding file descriptor manipulation. Master dup2() for redirecting stdin/stdout and ensure proper pipe communication between processes!
