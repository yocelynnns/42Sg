# C++ - Module 06

## 📋 Project Overview
This module focuses on C++ casts, type conversion, and type identification.

## 🏗️ Project Structure
```
cpp06/
├── ex00/ - ScalarConverter
│   ├── Makefile
│   ├── inc/
│   │   └── ScalarConverter.hpp
│   └── src/
│       ├── ScalarConverter.cpp
│       └── main.cpp
├── ex01/ - Serialization
│   ├── Makefile
│   ├── inc/
│   │   ├── Data.hpp
│   │   └── Serializer.hpp
│   └── src/
│       ├── Serializer.cpp
│       └── main.cpp
├── ex02/ - Type Identification
│   ├── Makefile
│   ├── inc/
│   │   ├── A.hpp
│   │   ├── B.hpp
│   │   ├── Base.hpp
│   │   └── C.hpp
│   └── src/
│       ├── Base.cpp
│       └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: ScalarConverter
**Objective**: Convert string representations to various scalar types.

**Files**: `Makefile`, `inc/ScalarConverter.hpp`, `src/ScalarConverter.cpp`, `src/main.cpp`

**Supported Types**:
- char, int, float, double
- Special values: -inf, +inf, nan

**Key Features**:
- Static class with single convert() method
- Explicit type casting
- Error handling for impossible conversions

**Example Output**:
```
$> ./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0

$> ./convert 42.42
char: Non displayable
int: 42
float: 42.42f
double: 42.42

$> ./convert nan
char: impossible
int: impossible
float: nanf
double: nan

$> ./convert +inff
char: impossible
int: impossible
float: inff
double: inf

$> ./convert "hello"
char: impossible
int: impossible
float: impossible
double: impossible
```

**Key Concepts**:
- Static classes
- Type conversion and casting
- Special floating-point values
- Input validation

### Exercise 01: Serialization
**Objective**: Implement pointer serialization and deserialization.

**Files**: `Makefile`, `inc/Data.hpp`, `inc/Serializer.hpp`, `src/Serializer.cpp`, `src/main.cpp`

**Key Functions**:
```cpp
uintptr_t serialize(Data* ptr);
Data* deserialize(uintptr_t raw);
```

**Purpose**: Convert pointers to integers and back safely

**Example Output**:
```
$> ./serialization
Original Data:
  value: 42
  name: TestData
  pi: 3.14159

Original pointer address: 0x7ffeeb7d8a10

After serialization to uintptr_t: 140736739362320

After deserialization back to Data*: 0x7ffeeb7d8a10

Restored Data:
  value: 42
  name: TestData
  pi: 3.14159

Data comparison: SUCCESS - Pointers are equal after round trip
Data values match: SUCCESS - All values preserved correctly
```

**Key Concepts**:
- Pointer serialization
- `reinterpret_cast`
- Memory address manipulation
- Data integrity verification

### Exercise 02: Type Identification
**Objective**: Identify object types at runtime without typeinfo.

**Files**: `Makefile`, `inc/Base.hpp`, `inc/A.hpp`, `inc/B.hpp`, `inc/C.hpp`, `src/Base.cpp`, `src/main.cpp`

**Class Hierarchy**:
- `Base` (abstract base class)
- `A`, `B`, `C` (derived classes)

**Key Functions**:
- `Base* generate()` - Randomly creates A, B, or C
- `identify(Base* p)` - Identifies type from pointer
- `identify(Base& p)` - Identifies type from reference

**Example Output**:
```
$> ./identify
=== Test 1: Pointer identification ===
Generated object type: A
identify(Base*): A
identify(Base&): A

=== Test 2: Pointer identification ===
Generated object type: B
identify(Base*): B
identify(Base&): B

=== Test 3: Pointer identification ===
Generated object type: C
identify(Base*): C
identify(Base&): C

=== Test 4: Multiple random generations ===
Object 1: B (pointer), B (reference)
Object 2: A (pointer), A (reference)
Object 3: C (pointer), C (reference)
Object 4: A (pointer), A (reference)
Object 5: B (pointer), B (reference)

=== Edge Case: Null pointer ===
identify(nullptr): Cannot identify null pointer

All identifications successful!
```

**Key Concepts**:
- Runtime type identification (RTTI)
- `dynamic_cast` for type checking
- Random object generation
- Pointer vs reference parameter handling

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
- No use of `typeid` or `std::typeinfo` in ex02
- Memory leaks are strictly forbidden
- Proper error handling for invalid conversions
- Use appropriate C++ casts:
  - `static_cast` for well-defined conversions
  - `dynamic_cast` for polymorphic type checking
  - `reinterpret_cast` for low-level pointer manipulation

## 🔧 Key Learning Points
- C++ casting operators and their appropriate use cases
- Type conversion and validation
- Pointer manipulation and serialization
- Runtime type identification without RTTI
- Random object generation and type detection
