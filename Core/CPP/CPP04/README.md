# C++ - Module 04

## 📋 Project Overview
This module covers subtype polymorphism, abstract classes, and interfaces.

## 🏗️ Project Structure
```
cpp04/
├── ex00/ - Polymorphism
│   ├── Makefile
│   ├── inc/
│   │   ├── Animal.hpp
│   │   ├── Cat.hpp
│   │   ├── Dog.hpp
│   │   ├── WrongAnimal.hpp
│   │   └── WrongCat.hpp
│   └── src/
│       ├── Animal.cpp
│       ├── Cat.cpp
│       ├── Dog.cpp
│       ├── WrongAnimal.cpp
│       ├── WrongCat.cpp
│       └── main.cpp
├── ex01/ - Deep Copies and Brain Class
│   ├── Makefile
│   ├── inc/
│   │   ├── Animal.hpp
│   │   ├── Brain.hpp
│   │   ├── Cat.hpp
│   │   └── Dog.hpp
│   └── src/
│       ├── Animal.cpp
│       ├── Brain.cpp
│       ├── Cat.cpp
│       ├── Dog.cpp
│       └── main.cpp
├── ex02/ - Abstract Classes
│   ├── Makefile
│   ├── inc/
│   │   ├── AAnimal.hpp
│   │   ├── Cat.hpp
│   │   └── Dog.hpp
│   └── src/
│       ├── AAnimal.cpp
│       ├── Cat.cpp
│       ├── Dog.cpp
│       └── main.cpp
├── ex03/ - Interface & Recap
│   ├── Makefile
│   ├── inc/
│   │   ├── AMateria.hpp
│   │   ├── Character.hpp
│   │   ├── Cure.hpp
│   │   ├── ICharacter.hpp
│   │   ├── IMateriaSource.hpp
│   │   ├── Ice.hpp
│   │   └── MateriaSource.hpp
│   └── src/
│       ├── AMateria.cpp
│       ├── Character.cpp
│       ├── Cure.cpp
│       ├── Ice.cpp
│       ├── MateriaSource.cpp
│       └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Polymorphism
**Objective**: Implement basic polymorphism with animal classes.

**Files**: `Makefile`, `Animal.cpp/hpp`, `Dog.cpp/hpp`, `Cat.cpp/hpp`, `WrongAnimal.cpp/hpp`, `WrongCat.cpp/hpp`, `main.cpp`

**Class Hierarchy**:
- `Animal` (base class)
- `Dog` → `Animal`
- `Cat` → `Animal`
- `WrongAnimal` (non-virtual for comparison)
- `WrongCat` → `WrongAnimal`

**Example Output**:
```
$> ./polymorphism
Animal constructor called
Dog constructor called
Cat constructor called
Animal constructor called
WrongAnimal constructor called
WrongCat constructor called

Dog sound: Woof!
Cat sound: Meow!
Animal sound: ... (should be animal sound)
WrongCat sound: Wrong meow! (not polymorphic)

Dog type: Dog
Cat type: Cat
Animal type: Animal

Dog destructor called
Animal destructor called
Cat destructor called
Animal destructor called
WrongCat destructor called
WrongAnimal destructor called
```

**Key Concepts**:
- Virtual functions for runtime polymorphism
- Virtual destructors
- Difference between virtual and non-virtual methods

### Exercise 01: Deep Copies and Brain Class
**Objective**: Implement deep copy semantics with Brain class.

**Files**: `Makefile`, `Animal.cpp/hpp`, `Dog.cpp/hpp`, `Cat.cpp/hpp`, `Brain.cpp/hpp`, `main.cpp`

**New Class**: `Brain` with 100 string ideas array

**Deep Copy Requirements**:
- Copy constructors must create new Brain instances
- Assignment operators must handle proper copying
- No memory leaks

**Example Output**:
```
$> ./deepcopy
Animal constructor called
Brain constructor called
Dog constructor called
Animal constructor called
Brain constructor called
Dog copy constructor called
Animal constructor called
Brain constructor called
Dog assignment operator called

Original dog ideas:
Idea 0: I want to play!
Idea 1: I'm hungry!
...
Copied dog ideas:
Idea 0: I want to play!
Idea 1: I'm hungry!
...

Memory addresses different: true (proves deep copy)

Dog destructor called
Brain destructor called
Animal destructor called
Dog destructor called
Brain destructor called
Animal destructor called
Dog destructor called
Brain destructor called
Animal destructor called
```

**Key Concepts**:
- Deep vs shallow copying
- Copy constructors and assignment operators
- Memory management with composition

### Exercise 02: Abstract Classes
**Objective**: Make Animal class abstract.

**Files**: `Makefile`, `Animal.cpp/hpp`, `Dog.cpp/hpp`, `Cat.cpp/hpp`, `Brain.cpp/hpp`, `main.cpp`

**Key Change**:
- Pure virtual functions in Animal class
- Cannot instantiate Animal directly
- Derived classes must implement abstract methods

**Example Output**:
```
$> ./abstract
Animal constructor called (abstract)
Brain constructor called
Dog constructor called
Animal constructor called (abstract)
Brain constructor called
Cat constructor called

// This would cause compilation error:
// Animal animal;  // Error: cannot declare variable of abstract type

Dog sound: Woof!
Cat sound: Meow!

Dog type: Dog
Cat type: Cat

Cat destructor called
Brain destructor called
Animal destructor called
Dog destructor called
Brain destructor called
Animal destructor called
```

**Key Concepts**:
- Pure virtual functions
- Abstract base classes
- Interface enforcement

### Exercise 03: Interface Implementation
**Objective**: Create game-like system with materials and characters.

**Files**: `Makefile`, `AMateria.cpp/hpp`, `Ice.cpp/hpp`, `Cure.cpp/hpp`, `ICharacter.hpp`, `Character.cpp/hpp`, `IMateriaSource.hpp`, `MateriaSource.cpp/hpp`, `main.cpp`

**Main Classes**:
- `AMateria` (abstract base)
- `Ice`, `Cure` (concrete materials)
- `ICharacter`, `Character`
- `IMateriaSource`, `MateriaSource`

**Example Output**:
```
$> ./interface
MateriaSource constructor called
Character constructor called
Ice constructor called
Cure constructor called

* Materia learning and creation *
Learned Ice materia
Learned Cure materia
Creating Ice materia...
Creating Cure materia...

* Character inventory management *
Character Bob equipped with Ice in slot 0
Character Bob equipped with Cure in slot 1

* Materia usage *
Bob: \"* shoots an ice bolt at target *\"
Bob: \"* heals target's wounds *\"

* Copy and assignment tests *
Copy constructor called - deep copy verified
Assignment operator called - deep copy verified

* Cleanup *
Character destructor called
Unequipping and deleting Ice
Unequipping and deleting Cure
MateriaSource destructor called
Ice destructor called
Cure destructor called
```

**Key Patterns**:
- Interface implementation
- Factory pattern with MateriaSource
- Inventory management
- Deep copy semantics

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
cd ex03 && make
```

## ⚠️ Important Notes
- No `using namespace` allowed
- No STL containers or algorithms
- Memory leaks are strictly forbidden
- Orthodox Canonical Form required for all classes
- Header files must have include guards
- Each exercise is self-contained with its own Makefile
- Pure virtual functions must be implemented in derived classes

## 🔧 Polymorphism Concepts
- Virtual functions and overriding
- Abstract classes and pure virtual functions
- Interface implementation
- Runtime type identification
- Deep vs shallow copying
- Factory pattern
- Inventory management systems
