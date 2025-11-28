# C++ - Module 03

## 📋 Project Overview
This module introduces inheritance concepts in C++.

## 🏗️ Project Structure
```
cpp03/
├── ex00/ - ClapTrap
│   ├── Makefile
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   └── main.cpp
├── ex01/ - ScavTrap
│   ├── Makefile
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── ScavTrap.cpp
│   ├── ScavTrap.hpp
│   └── main.cpp
├── ex02/ - FragTrap
│   ├── Makefile
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── FragTrap.cpp
│   ├── FragTrap.hpp
│   └── main.cpp
├── ex03/ - DiamondTrap
│   ├── Makefile
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── ScavTrap.cpp
│   ├── ScavTrap.hpp
│   ├── FragTrap.cpp
│   ├── FragTrap.hpp
│   ├── DiamondTrap.cpp
│   ├── DiamondTrap.hpp
│   └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: ClapTrap
**Objective**: Create base robot class with combat mechanics.

**Files**: `Makefile`, `ClapTrap.cpp`, `ClapTrap.hpp`, `main.cpp`

**Attributes**:
- Hit points: 10
- Energy points: 10
- Attack damage: 0

**Methods**:
- `attack()`, `takeDamage()`, `beRepaired()`

**Example Output**:
```
$> ./claptrap
ClapTrap Default constructor called
ClapTrap Name constructor called
ClapTrap Copy constructor called
ClapTrap Copy assignment operator called
ClapTrap Attack function called
ClapTrap Bob attacks Alice, causing 0 points of damage!
ClapTrap Take damage function called
ClapTrap Alice takes 5 damage, now has 5 hit points
ClapTrap Be repaired function called
ClapTrap Alice repairs itself for 3 hit points, now has 8 hit points
ClapTrap Destructor called
ClapTrap Destructor called
ClapTrap Destructor called
```

**Key Concepts**:
- Base class implementation
- Resource management (hit points, energy)
- Combat mechanics

### Exercise 01: ScavTrap
**Objective**: Create derived class from ClapTrap.

**Files**: `Makefile`, `ClapTrap.cpp/hpp`, `ScavTrap.cpp/hpp`, `main.cpp`

**Inheritance**: `ScavTrap` → `ClapTrap`

**Modified Attributes**:
- Hit points: 100
- Energy points: 50
- Attack damage: 20

**Special Ability**: `guardGate()`

**Example Output**:
```
$> ./scavtrap
ClapTrap Default constructor called
ScavTrap Default constructor called
ClapTrap Name constructor called
ScavTrap Name constructor called
ScavTrap GuardGate function called
ScavTrap ScavTrap is now in Gate keeper mode
ScavTrap Attack function called
ScavTrap Bob attacks Alice, causing 20 points of damage!
ClapTrap Take damage function called
ClapTrap Alice takes 20 damage, now has 80 hit points
ScavTrap Destructor called
ClapTrap Destructor called
ScavTrap Destructor called
ClapTrap Destructor called
```

**Key Concepts**:
- Single inheritance
- Constructor/destructor chaining
- Method overriding

### Exercise 02: FragTrap
**Objective**: Create another derived class from ClapTrap.

**Files**: `Makefile`, `ClapTrap.cpp/hpp`, `FragTrap.cpp/hpp`, `main.cpp`

**Inheritance**: `FragTrap` → `ClapTrap`

**Modified Attributes**:
- Hit points: 100
- Energy points: 100
- Attack damage: 30

**Special Ability**: `highFivesGuys()`

**Example Output**:
```
$> ./fragtrap
ClapTrap Default constructor called
FragTrap Default constructor called
ClapTrap Name constructor called
FragTrap Name constructor called
FragTrap HighFivesGuys function called
FragTrap FragTrap requests a positive high five!
FragTrap Attack function called
FragTrap Bob attacks Alice, causing 30 points of damage!
ClapTrap Take damage function called
ClapTrap Alice takes 30 damage, now has 70 hit points
FragTrap Destructor called
ClapTrap Destructor called
FragTrap Destructor called
ClapTrap Destructor called
```

**Key Concepts**:
- Multiple derived classes from same base
- Different attribute values in derived classes
- Specialized member functions

### Exercise 03: DiamondTrap
**Objective**: Implement multiple inheritance with diamond problem.

**Files**: `Makefile`, `ClapTrap.cpp/hpp`, `ScavTrap.cpp/hpp`, `FragTrap.cpp/hpp`, `DiamondTrap.cpp/hpp`, `main.cpp`

**Inheritance**: `DiamondTrap` → `FragTrap`, `ScavTrap`

**Key Challenge**:
- Virtual inheritance to avoid duplicate ClapTrap
- Name resolution with same variable names
- Constructor chaining

**Example Output**:
```
$> ./diamondtrap
ClapTrap Default constructor called
ScavTrap Default constructor called
FragTrap Default constructor called
DiamondTrap Default constructor called
ClapTrap Name constructor called
ScavTrap Name constructor called
FragTrap Name constructor called
DiamondTrap Name constructor called
DiamondTrap whoAmI function called
DiamondTrap My name is DiamondBob and my ClapTrap name is DiamondBob_clap_name
DiamondTrap Attack function called
ScavTrap Attack function called
DiamondTrap Bob attacks Alice, causing 20 points of damage!
DiamondTrap GuardGate function called
DiamondTrap HighFivesGuys function called
DiamondTrap Destructor called
FragTrap Destructor called
ScavTrap Destructor called
ClapTrap Destructor called
DiamondTrap Destructor called
FragTrap Destructor called
ScavTrap Destructor called
ClapTrap Destructor called
```

**Key Concepts**:
- Multiple inheritance
- Virtual inheritance
- Diamond problem resolution
- Name ambiguity resolution

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
- Pay attention to constructor/destructor order

## 🔧 Inheritance Concepts
- Constructor/destructor chaining
- Access specifiers (public/protected/private)
- Virtual inheritance
- Method overriding
- Multiple inheritance challenges
- Name resolution in inheritance hierarchies
