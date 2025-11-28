# C++ - Module 08

## 📋 Project Overview
This module focuses on templated containers, iterators, and algorithms using the STL.

## 🏗️ Project Structure
```
cpp08/
├── ex00/ - Easy Find
│   ├── Makefile
│   ├── inc/
│   │   └── easyfind.hpp
│   └── src/
│       └── main.cpp
├── ex01/ - Span
│   ├── Makefile
│   ├── inc/
│   │   └── Span.hpp
│   └── src/
│       ├── Span.cpp
│       └── main.cpp
├── ex02/ - Mutant Stack
│   ├── Makefile
│   ├── inc/
│   │   └── MutantStack.hpp
│   └── src/
│       ├── MutantStack.tpp
│       └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Easy Find
**Objective**: Create a function template to find elements in containers.

**Files**: `Makefile`, `easyfind.hpp`, `main.cpp`

**Function Template**:
```cpp
template<typename T>
typename T::iterator easyfind(T& container, int value);
```

**Requirements**:
- Works with any container of integers
- Returns iterator to first occurrence
- Throws exception if value not found
- Should work with vector, list, deque, etc.

**Example Output**:
```
$> ./easyfind
Testing with vector: 1 3 5 7 9 
Found value 5 at position 2
Value 4 not found in container!
Testing with list: 2 4 6 8 10 
Found value 8 at position 3
```

**Key Concepts**:
- Function templates with containers
- Iterator types and operations
- Exception handling
- STL container interfaces

### Exercise 01: Span
**Objective**: Implement a class that stores numbers and calculates spans.

**Files**: `Makefile`, `Span.hpp`, `Span.cpp`, `main.cpp`

**Class Features**:
- Stores maximum N integers
- `addNumber()` to add single numbers
- `shortestSpan()` and `longestSpan()` methods
- Range-based constructor for adding multiple numbers
- Exception handling for full capacity and insufficient elements

**Example Output**:
```
$> ./span
=== Basic Test ===
Shortest span: 2
Longest span: 14

=== Large Dataset Test ===
Added 10000 numbers
Shortest span: 1
Longest span: 99999

=== Exception Tests ===
Error: Container is full!
Error: Not enough elements to calculate span!

=== Range Test ===
Added 50 numbers using iterator range
Shortest span: 0
Longest span: 49
```

**Key Concepts**:
- STL container design
- Iterator ranges
- Algorithm implementation
- Exception safety

### Exercise 02: Mutant Stack
**Objective**: Make std::stack iterable by creating a derived class.

**Files**: `Makefile`, `MutantStack.hpp`, `main.cpp`

**Class Features**:
- Inherits from std::stack
- Provides iterators (begin, end, rbegin, rend)
- Maintains all original stack functionality
- Should behave like other STL containers when iterated

**Example Output**:
```
$> ./mutantstack
=== Stack Operations ===
Top element: 17
Stack size: 1

=== Iterator Test ===
Stack elements: 5 3 5 737 0 
Reverse iteration: 0 737 5 3 5 

=== Comparison with List ===
List elements: 5 3 5 737 0 
Outputs match: YES

=== Copy Test ===
Original: 5 3 5 737 0 
Copy: 5 3 5 737 0 
All operations successful!
```

**Key Concepts**:
- STL container adapters
- Iterator implementation
- Inheritance from STL classes
- Template specialization

## 🔧 Compilation
**Each exercise has its own Makefile** with the following standard rules:
- `make` or `make all` - compiles the program
- `make clean` - removes object files
- `make fclean` - removes object files and executable
- `make re` - recompiles everything

```bash
# Compile with C++98 standard
c++ -Wall -Wextra -Werror -std=c++98

# Example compilation for each exercise:
cd ex00 && make
cd ex01 && make
cd ex02 && make
```

## ⚠️ Important Notes
- **STL usage is mandatory and required** - this is the main focus of the module
- Use appropriate STL containers and algorithms
- No `using namespace` allowed
- Memory leaks are strictly forbidden
- Template implementations can be in header files or .tpp files
- Follow good exception handling practices
- Each exercise must demonstrate thorough testing

## 🔧 Key Learning Points
- STL containers (vector, list, stack, etc.)
- Iterator concepts and usage
- STL algorithms
- Template programming with STL
- Container adapter patterns
- Exception handling in STL contexts
- Performance considerations with large datasets

## 🎯 Module-Specific Rules
- **You must use the STL** - especially containers and algorithms
- Using STL is precisely the goal of this module
- Apply STL wherever appropriate throughout the exercises
- Exercises should be solved USING standard containers and algorithms
- Failure to use STL will result in poor grades even if code works
