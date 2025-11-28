# C++ - Module 01

## 📋 Project Overview
This module focuses on memory allocation, pointers to members, references, and switch statements.

## 🏗️ Project Structure
```
cpp01/
├── ex00/ - BraiiiiiiinnnzzzZ
│   ├── Makefile
│   ├── Zombie.cpp
│   ├── Zombie.hpp
│   ├── NewZombie.cpp
│   ├── RandomChump.cpp
│   └── main.cpp
├── ex01/ - Moar brainz!
│   ├── Makefile
│   ├── Zombie.cpp
│   ├── Zombie.hpp
│   ├── ZombieHorde.cpp
│   └── main.cpp
├── ex02/ - HI THIS IS BRAIN
│   ├── Makefile
│   └── main.cpp
├── ex03/ - Unnecessary violence
│   ├── Makefile
│   ├── Weapon.cpp
│   ├── Weapon.hpp
│   ├── HumanA.cpp
│   ├── HumanA.hpp
│   ├── HumanB.cpp
│   ├── HumanB.hpp
│   └── main.cpp
├── ex04/ - Sed is for losers
│   ├── Makefile
│   ├── main.cpp
│   ├── main.hpp
│   └── test.sh
├── ex05/ - Harl 2.0
│   ├── Makefile
│   ├── Harl.cpp
│   ├── Harl.hpp
│   └── main.cpp
├── ex06/ - Harl filter
│   ├── Makefile
│   ├── Harl.cpp
│   ├── Harl.hpp
│   └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: BraiiiiiiinnnzzzZ
**Objective**: Understand stack vs heap allocation with Zombie class.

**Files**: `Makefile`, `Zombie.cpp`, `Zombie.hpp`, `main.cpp`

**Key Functions**:
- `randomChump()` - stack allocation
- `newZombie()` - heap allocation

**Example Output**:
```
$> ./zombie
BraiiiiiiinnnzzzZ...
Mooorrreee BraiiiiiiinnnzzzZ...
```

**Key Concepts**:
- Stack vs heap allocation
- Destructors and memory management
- Object lifecycle

### Exercise 01: Moar brainz!
**Objective**: Create zombie hordes with single allocation.

**Files**: `Makefile`, `Zombie.cpp`, `Zombie.hpp`, `main.cpp`

**Key Functions**:
```cpp
Zombie* zombieHorde(int N, std::string name);
```

**Example Output**:
```
$> ./zombieHorde 5 "Walker"
Walker: BraiiiiiiinnnzzzZ...
Walker: BraiiiiiiinnnzzzZ...
Walker: BraiiiiiiinnnzzzZ...
Walker: BraiiiiiiinnnzzzZ...
Walker: BraiiiiiiinnnzzzZ...
```

**Key Concepts**:
- Array allocation with `new[]`
- Batch object creation
- Memory management for arrays

### Exercise 02: HI THIS IS BRAIN
**Objective**: Demonstrate pointers vs references.

**Files**: `Makefile`, `main.cpp`

**Example Output**:
```
$> ./brain
String value: HI THIS IS BRAIN
Pointer value: HI THIS IS BRAIN
Reference value: HI THIS IS BRAIN

String address: 0x7ffd12345678
Pointer address: 0x7ffd12345678
Reference address: 0x7ffd12345678
```

**Key Concepts**:
- String pointers vs references
- Memory address comparison
- Dereferencing and address-of operators

### Exercise 03: Unnecessary violence
**Objective**: Implement Weapon, HumanA, and HumanB classes.

**Files**: `Makefile`, `Weapon.cpp/hpp`, `HumanA.cpp/hpp`, `HumanB.cpp/hpp`, `main.cpp`

**Key Differences**:
- `HumanA`: Weapon as reference (always armed)
- `HumanB`: Weapon as pointer (may not have weapon)

**Example Output**:
```
$> ./violence
HumanA attacks with their crude spiked club
HumanB attacks with their crude spiked club
HumanB attacks with their bare hands
HumanA attacks with their crude spiked club
```

**Key Concepts**:
- Reference members in classes
- Pointer members in classes
- Constructor initialization lists

### Exercise 04: Sed is for losers
**Objective**: Create a file replacement program.

**Files**: `Makefile`, `main.cpp`

**Usage**:
```bash
./sed_is_for_losers filename s1 s2
```

**Example Output**:
```
$> cat test.txt
hello world hello
$> ./sed test.txt hello goodbye
$> cat test.txt.replace
goodbye world goodbye
```

**Features**:
- File I/O operations
- String replacement
- Error handling for file operations

### Exercise 05: Harl 2.0
**Objective**: Implement complaint system using pointers to member functions.

**Files**: `Makefile`, `Harl.cpp`, `Harl.hpp`, `main.cpp`

**Complaint Levels**:
- DEBUG, INFO, WARNING, ERROR

**Example Output**:
```
$> ./harl
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!

[ INFO ]
I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!

[ WARNING ]
I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Key Concepts**:
- Pointers to member functions
- Function pointer arrays
- Dynamic method invocation

### Exercise 06: Harl filter
**Objective**: Filter Harl's complaints using switch statements.

**Files**: `Makefile`, `Harl.cpp`, `Harl.hpp`, `main.cpp`

**Usage**:
```bash
./harlFilter "WARNING"
```

**Example Output**:
```
$> ./harlFilter "DEBUG"
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!

[ INFO ]
I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!

[ WARNING ]
I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now.

$> ./harlFilter "WARNING"
[ WARNING ]
I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now.

$> ./harlFilter "ERROR"
[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Key Concepts**:
- Switch statement usage
- Complaint level filtering
- Conditional execution flow

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
# ... and so on for all exercises
```

## ⚠️ Important Notes
- No `using namespace` allowed
- No STL containers or algorithms
- Memory leaks are strictly forbidden
- Proper use of `new` and `delete` required
- Header files must have include guards
- Each exercise is self-contained with its own Makefile

## 🔧 Key Learning Points
- Memory management (new/delete)
- References vs pointers
- Member function pointers
- File manipulation
- Switch statement usage
- Object-oriented design patterns
