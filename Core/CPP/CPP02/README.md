# C++ - Module 02

## 📋 Project Overview
This module covers ad-hoc polymorphism, operator overloading, and the Orthodox Canonical Form.

## 🏗️ Project Structure
```
cpp02/
├── ex00/ - Fixed Point Class (Basic)
│   ├── Makefile
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   └── main.cpp
├── ex01/ - Fixed Point Class (Enhanced)
│   ├── Makefile
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   └── main.cpp
├── ex02/ - Fixed Point Class (Operators)
│   ├── Makefile
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Fixed Point Class (Basic)
**Objective**: Implement fixed-point number class in Orthodox Canonical Form.

**Files**: `Makefile`, `Fixed.cpp`, `Fixed.hpp`, `main.cpp`

**Orthodox Canonical Form Requirements**:
- Default constructor
- Copy constructor
- Copy assignment operator
- Destructor

**Fixed Point Representation**:
- Integer value storage
- 8 fractional bits (constant)

**Example Output**:
```
$> ./fixed
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
```

**Key Concepts**:
- Orthodox Canonical Form
- Fixed-point arithmetic representation
- Bit manipulation

### Exercise 01: Fixed Point Class (Enhanced)
**Objective**: Add conversion constructors and output operator.

**Files**: `Makefile`, `Fixed.cpp`, `Fixed.hpp`, `main.cpp`

**New Features**:
- Integer and float constructors
- Conversion methods: `toFloat()`, `toInt()`
- Output stream operator overload

**Example Output**:
```
$> ./fixed
0
0.00390625
0.00390625
10.1016
10.1016
```

**Key Concepts**:
- Conversion constructors
- Operator overloading (`<<`)
- Fixed-point to float conversion

### Exercise 02: Fixed Point Class (Operators)
**Objective**: Implement arithmetic and comparison operators.

**Files**: `Makefile`, `Fixed.cpp`, `Fixed.hpp`, `main.cpp`

**Operator Overloads**:
- Arithmetic: `+`, `-`, `*`, `/`
- Comparison: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Increment/Decrement: prefix/postfix
- Static min/max functions

**Example Output**:
```
$> ./fixed
a = 1234.43
b = 10
a + b = 1244.43
a - b = 1224.43
a * b = 12344.3
a / b = 123.443

a > b: true
a < b: false
a >= b: true
a <= b: false
a == b: false
a != b: true

Pre-increment: 1235.43
Post-increment: 1235.43
After post-increment: 1236.43

Min: 10
Max: 1236.43
```

**Key Concepts**:
- Arithmetic operator overloading
- Comparison operator overloading
- Increment/decrement operators
- Static member functions

## 🔧 Orthodox Canonical Form
Every class must implement:
```cpp
class ClassName {
public:
    ClassName();                    // Default constructor
    ClassName(const ClassName&);    // Copy constructor
    ClassName& operator=(const ClassName&); // Copy assignment
    ~ClassName();                   // Destructor
};
```

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
- No `using namespace` allowed
- No STL containers or algorithms
- Memory leaks are strictly forbidden
- **Orthodox Canonical Form required for all classes**
- Header files must have include guards
- Each exercise is self-contained with its own Makefile
- Fixed-point representation uses 8 fractional bits

## 🔧 Key Learning Points
- Operator overloading
- Orthodox Canonical Form
- Fixed-point arithmetic
- Const correctness
- Static member functions
- Conversion constructors
