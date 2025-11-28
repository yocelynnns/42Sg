# C++ - Module 07

## 📋 Project Overview
This module introduces C++ templates for generic programming.

## 🏗️ Project Structure
```
cpp07/
├── ex00/ - Function Templates
│   ├── Makefile
│   ├── inc/
│   │   └── whatever.hpp
│   └── src/
│       └── main.cpp
├── ex01/ - Iter Template
│   ├── Makefile
│   ├── inc/
│   │   └── iter.hpp
│   └── src/
│       └── main.cpp
├── ex02/ - Array Template Class
│   ├── Makefile
│   ├── inc/
│   │   └── Array.hpp
│   └── src/
│       ├── Array.tpp
│       └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Function Templates
**Objective**: Implement basic function templates.

**Files**: `Makefile`, `inc/whatever.hpp`, `src/main.cpp`

**Templates Required**:
- `swap` - Swaps two values
- `min` - Returns smaller value (returns second if equal)
- `max` - Returns larger value (returns second if equal)

**Requirements**:
- Templates defined in header files
- Support any comparable types

**Example Output**:
```
$> ./templates
=== Integer Tests ===
a = 2, b = 3
After swap: a = 3, b = 2
min(a, b) = 2
max(a, b) = 3

=== String Tests ===
c = chaine1, d = chaine2
After swap: c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2

=== Float Tests ===
e = 2.1, f = 2.2
After swap: e = 2.2, f = 2.1
min(e, f) = 2.1
max(e, f) = 2.2

=== Equal Values Test ===
x = 5, y = 5
min(x, y) = 5 (returns second when equal)
max(x, y) = 5 (returns second when equal)
```

**Key Concepts**:
- Function template syntax
- Template type deduction
- Generic programming
- Template instantiation

### Exercise 01: Iter Template
**Objective**: Create function template that applies function to array elements.

**Files**: `Makefile`, `inc/iter.hpp`, `src/main.cpp`

**Function Signature**:
```cpp
template<typename T>
void iter(T* array, size_t length, void (*func)(T&));
```

**Features**:
- Works with any array type
- Supports const and non-const elements
- Applies function to each element

**Example Output**:
```
$> ./iter
=== Integer Array ===
Original: 1 2 3 4 5 
After increment: 2 3 4 5 6 

=== String Array ===
Original: hello world template c++ 
After uppercase: HELLO WORLD TEMPLATE C++ 

=== Float Array ===
Original: 1.1 2.2 3.3 4.4 5.5 
After multiply by 2: 2.2 4.4 6.6 8.8 11 

=== Const Array Test ===
Const array: 10 20 30 40 50 
Printing const elements: 10 20 30 40 50 

All function applications successful!
```

**Key Concepts**:
- Function pointers with templates
- Array processing
- Template specialization for const types
- Generic algorithms

### Exercise 02: Array Template Class
**Objective**: Implement a generic array class template.

**Files**: `Makefile`, `inc/Array.hpp`, `src/Array.tpp`, `src/main.cpp`

**Key Features**:
- Dynamic size array
- Bounds checking with exceptions
- Copy semantics (deep copy)
- `size()` member function
- `operator[]` with bounds checking

**Exception Handling**:
- Throws `std::exception` on out-of-bounds access

**Example Output**:
```
$> ./array
=== Default Constructor Test ===
Empty array size: 0

=== Size Constructor Test ===
Int array size: 5
Float array size: 3

=== Assignment Test ===
Original: 1 2 3 4 5 
Copy: 1 2 3 4 5 
After modifying copy: 10 20 30 40 50 
Original unchanged: 1 2 3 4 5 

=== Bounds Checking Test ===
Accessing element 2: 3
Accessing element 10: 
Exception caught: Index out of bounds!
Accessing element -1: 
Exception caught: Index out of bounds!

=== String Array Test ===
String array: one two three 
Modified: ONE two three 

=== Copy Constructor Test ===
Original: 100 200 300 
Copy: 100 200 300 
Independent copies verified!

All array tests completed successfully!
```

**Key Concepts**:
- Class templates
- Template implementation in .tpp files
- Deep copy semantics
- Exception handling in templates
- Operator overloading in templates

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
- Template definitions must be in header files
- No `using namespace` allowed
- Proper exception handling required
- Deep copy semantics for Array class
- Bounds checking for array access
- Template code must be generic and reusable

## 🔧 Key Learning Points
- Function templates and class templates
- Template syntax and instantiation
- Generic programming principles
- Template specialization
- Exception handling in template classes
- Deep copy implementation for templates
- Operator overloading in templates
