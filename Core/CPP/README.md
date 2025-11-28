# C++ Modules 00-09

## 📚 Overview
This repository contains all C++ modules from 00 to 09 of the 42 School curriculum. Each module builds upon the previous one, gradually introducing Object-Oriented Programming concepts from basic C++ features to advanced topics like STL containers and algorithms.

## 🏗️ Repository Structure
```
CPP/
├── CPP00/ - Basic C++ features, classes, I/O
├── CPP01/ - Memory management, references, pointers
├── CPP02/ - Operator overloading, Orthodox Canonical Form
├── CPP03/ - Inheritance, polymorphism
├── CPP04/ - Abstract classes, interfaces, deep copying
├── CPP05/ - Exception handling, custom exceptions
├── CPP06/ - Type casting, serialization, RTTI
├── CPP07/ - Templates, generic programming
├── CPP08/ - STL containers
├── CPP09/ - STL algorithms
└── README.md
```

## 🎯 Learning Progression

| Module | Focus Area | Key Concepts |
|--------|------------|--------------|
| **CPP00** | C++ Fundamentals | Namespaces, classes, member functions, streams |
| **CPP01** | Memory & References | Allocation, pointers, references, file I/O |
| **CPP02** | Ad-hoc Polymorphism | Operator overloading, fixed-point arithmetic |
| **CPP03** | Inheritance | Class hierarchies, multiple inheritance |
| **CPP04** | Polymorphism | Abstract classes, interfaces, deep copying |
| **CPP05** | Exceptions | Custom exceptions, error handling |
| **CPP06** | Type System | Casting, serialization, type identification |
| **CPP07** | Generic Programming | Function/class templates |
| **CPP08** | STL Containers | Vector, list, map, stack, queue |
| **CPP09** | STL Algorithms | Sorting, searching, transformations |

## 🔧 Common Requirements

### Compilation Standards
```bash
# All modules must compile with:
c++ -Wall -Wextra -Werror -std=c++98

# Makefile must include:
all, clean, fclean, re rules
```

### Code Standards
- **No `using namespace std;`** - Must use std:: prefix
- **No C++11 features** - Strict C++98 compliance
- **No STL** until Modules 08-09 (except std::string, iostreams)
- **Orthodox Canonical Form** (Modules 02-09)
- **Memory leak prevention** - All heap allocations must be freed

---

# 📖 Detailed Module Breakdown

## CPP00 - Basic C++ Features
**Objective**: Introduction to C++ syntax and basic OOP concepts.

### Exercises:
- **ex00**: Megaphone - String manipulation and command-line arguments
- **ex01**: PhoneBook - Class implementation with fixed arrays
- **ex02**: Account - Static members and logging system

**Key Learning**: Classes, member functions, std::string, I/O streams

## CPP01 - Memory Management & References
**Objective**: Understand memory allocation, pointers, and references.

### Exercises:
- **ex00**: Zombie - Stack vs heap allocation
- **ex01**: Zombie Horde - Array allocation
- **ex02**: HI THIS IS BRAIN - Pointers vs references
- **ex03**: Weapon System - Reference vs pointer members
- **ex04**: File Sed - File I/O operations
- **ex05**: Harl - Pointers to member functions
- **ex06**: Harl Filter - Switch statements

**Key Learning**: new/delete, references, member function pointers, file operations

## CPP02 - Ad-hoc Polymorphism
**Objective**: Master operator overloading and Orthodox Canonical Form.

### Exercises:
- **ex00**: Fixed Point Class (Basic) - Orthodox Canonical Form
- **ex01**: Fixed Point Class (Enhanced) - Conversion constructors
- **ex02**: Fixed Point Class (Operators) - Arithmetic operations

**Key Learning**: Operator overloading, Orthodox Canonical Form, fixed-point arithmetic

## CPP03 - Inheritance
**Objective**: Learn class inheritance and polymorphism.

### Exercises:
- **ex00**: ClapTrap - Base class with combat mechanics
- **ex01**: ScavTrap - Single inheritance
- **ex02**: FragTrap - Another derived class
- **ex03**: DiamondTrap - Multiple inheritance (diamond problem)

**Key Learning**: Inheritance, virtual functions, multiple inheritance, constructor chaining

## CPP04 - Polymorphism & Abstract Classes
**Objective**: Deep dive into polymorphism and interfaces.

### Exercises:
- **ex00**: Animal Polymorphism - Virtual functions
- **ex01**: Brain Class - Deep copy semantics
- **ex02**: Abstract Animal - Pure virtual functions
- **ex03**: Materia System - Interfaces and factory pattern

**Key Learning**: Abstract classes, deep copying, interfaces, factory pattern

## CPP05 - Exceptions & Bureaucracy
**Objective**: Master exception handling in complex systems.

### Exercises:
- **ex00**: Bureaucrat Class - Custom exceptions
- **ex01**: Form Class - Form signing system
- **ex02**: Specialized Forms - Abstract form hierarchy
- **ex03**: Intern Class - Dynamic form creation

**Key Learning**: Exception hierarchy, custom exceptions, form validation

## CPP06 - Type System & Casting
**Objective**: Understand C++ casting and type identification.

### Exercises:
- **ex00**: ScalarConverter - Type conversion with casting
- **ex01**: Serialization - Pointer to integer conversion
- **ex02**: Type Identification - Runtime type info without typeinfo

**Key Learning**: C++ casts, serialization, type identification, RTTI

## CPP07 - Templates
**Objective**: Introduction to generic programming with templates.

### Exercises:
- **ex00**: Function Templates - swap, min, max
- **ex01**: Iter Template - Function application to arrays
- **ex02**: Array Template - Generic container class

**Key Learning**: Function templates, class templates, generic programming

## CPP08 - STL Containers
**Objective**: Master Standard Template Library containers and iterators.

### Exercises:
- **ex00**: Easy Find - Function template for container search
- **ex01**: Span - Container class with span calculations
- **ex02**: Mutant Stack - Iterable stack adapter

**Key Learning**: STL containers, iterators, container adapters, algorithms

## CPP09 - STL Algorithms
**Objective**: Master STL algorithms and container operations through practical applications.

### Exercises:
- **ex00**: Bitcoin Exchange - File parsing and date/value processing
- **ex01**: Reverse Polish Notation - Stack-based expression evaluation  
- **ex02**: PmergeMe - Merge-insert sort algorithm with multiple containers

**Key Learning**: File I/O, stack operations, sorting algorithms, container performance comparison

---

## ⚠️ Important Technical Constraints

### Memory Management
- **Zero memory leaks** - All allocations must be properly freed
- **RAII principle** - Resource acquisition is initialization
- **Deep copying** where resources are owned

### Orthodox Canonical Form (Modules 02-09)
Every class must implement:
```cpp
class ClassName {
public:
    ClassName();                           // Default constructor
    ClassName(const ClassName& other);     // Copy constructor
    ClassName& operator=(const ClassName& other); // Copy assignment
    ~ClassName();                          // Destructor
};
```

### File Organization
- **Headers**: `.hpp` or `.h` with include guards
- **Sources**: `.cpp` with implementations
- **Makefile**: Standard rules (all, clean, fclean, re)

### Testing Requirements
- Each exercise must include comprehensive tests
- Constructors/destructors should display meaningful messages
- Edge cases and error conditions must be handled

---

## 🚀 Getting Started

### Prerequisites
- C++98 compatible compiler (g++, clang++)
- Make utility
- Basic understanding of C programming

### Compilation Example
```bash
cd CPP00/ex00
make
./megaphone "hello world"
```

### Development Workflow
1. Read the subject thoroughly
2. Plan your class design
3. Implement Orthodox Canonical Form first
4. Add functionality incrementally
5. Test extensively
6. Check for memory leaks
7. Submit for evaluation

## 📚 Resources
- [cplusplus.com C++98 Reference](http://www.cplusplus.com/)
- [C++ Super-FAQ](https://isocpp.org/faq)
- [42 Intra C++ Modules](https://intra.42.fr)

---

*This curriculum systematically builds C++ expertise from basic syntax to advanced generic programming, preparing students for professional C++ development.*
