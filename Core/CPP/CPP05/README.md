# C++ - Module 05

## 📋 Project Overview
This module focuses on repetition and exceptions, implementing a bureaucratic system with custom exception handling and form management.

## 🏗️ Project Structure
```
cpp05/
├── ex00/ - Bureaucrat Class
│   ├── Makefile
│   ├── inc/
│   │   └── Bureaucrat.hpp
│   └── src/
│       ├── Bureaucrat.cpp
│       └── main.cpp
├── ex01/ - Form Class
│   ├── Makefile
│   ├── inc/
│   │   ├── Bureaucrat.hpp
│   │   └── Form.hpp
│   └── src/
│       ├── Bureaucrat.cpp
│       ├── Form.cpp
│       └── main.cpp
├── ex02/ - Abstract Forms
│   ├── Makefile
│   ├── inc/
│   │   ├── AForm.hpp
│   │   ├── Bureaucrat.hpp
│   │   ├── PresidentialPardonForm.hpp
│   │   ├── RobotomyRequestForm.hpp
│   │   └── ShrubberyCreationForm.hpp
│   └── src/
│       ├── AForm.cpp
│       ├── Bureaucrat.cpp
│       ├── PresidentialPardonForm.cpp
│       ├── RobotomyRequestForm.cpp
│       ├── ShrubberyCreationForm.cpp
│       └── main.cpp
├── ex03/ - Intern Class
│   ├── Makefile
│   ├── inc/
│   │   ├── AForm.hpp
│   │   ├── Bureaucrat.hpp
│   │   ├── Intern.hpp
│   │   ├── PresidentialPardonForm.hpp
│   │   ├── RobotomyRequestForm.hpp
│   │   └── ShrubberyCreationForm.hpp
│   └── src/
│       ├── AForm.cpp
│       ├── Bureaucrat.cpp
│       ├── Intern.cpp
│       ├── PresidentialPardonForm.cpp
│       ├── RobotomyRequestForm.cpp
│       ├── ShrubberyCreationForm.cpp
│       └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Bureaucrat Class
**Objective**: Implement Bureaucrat class with grade validation and exception handling.

**Files**: `Makefile`, `Bureaucrat.cpp`, `Bureaucrat.hpp`, `main.cpp`

**Key Features**:
- Constant name and grade (1-150 range)
- Custom exceptions: `GradeTooHighException`, `GradeTooLowException`
- Increment/decrement methods with exception throwing
- Orthodox Canonical Form

**Example Output**:
```
$> ./bureaucrat
Bureaucrat constructor called: Bob (grade 2)
Bureaucrat constructor called: Alice (grade 149)

Bob: Bob, bureaucrat grade 2
Alice: Alice, bureaucrat grade 149

Attempting to increment Bob's grade...
Bob: Bob, bureaucrat grade 1

Attempting to increment Bob's grade again...
Exception: Grade too high!

Attempting to decrement Alice's grade...
Alice: Alice, bureaucrat grade 150

Attempting to decrement Alice's grade again...
Exception: Grade too low!

Bureaucrat destructor called: Alice
Bureaucrat destructor called: Bob
```

**Key Concepts**:
- Custom exception classes
- Grade validation and range checking
- Orthodox Canonical Form with constants

### Exercise 01: Form Class
**Objective**: Create Form class that can be signed by Bureaucrats.

**Files**: `Makefile`, `Bureaucrat.cpp/hpp`, `Form.cpp/hpp`, `main.cpp`

**Form Requirements**:
- Constant name, sign grade, execute grade
- Boolean signed status
- `beSigned()` method with grade validation
- `signForm()` method in Bureaucrat class

**Example Output**:
```
$> ./forms
Bureaucrat constructor called: Bob (grade 5)
Form constructor called: Tax Form (sign grade: 10, exec grade: 50)

Form: Tax Form, signed: false, sign grade: 10, exec grade: 50

Bob attempts to sign Tax Form...
Bob signs Tax Form

Form: Tax Form, signed: true, sign grade: 10, exec grade: 50

Creating low-grade bureaucrat...
Bureaucrat constructor called: Intern (grade 150)

Intern attempts to sign Tax Form...
Exception: Grade too low!

Bureaucrat destructor called: Intern
Form destructor called: Tax Form
Bureaucrat destructor called: Bob
```

**Key Concepts**:
- Class relationships (Bureaucrat signs Form)
- Grade validation between classes
- Const member variables

### Exercise 02: Abstract Forms
**Objective**: Create specialized form classes inheriting from abstract AForm.

**Files**: `Makefile`, `Bureaucrat.cpp/hpp`, `AForm.cpp/hpp`, `ShrubberyCreationForm.cpp/hpp`, `RobotomyRequestForm.cpp/hpp`, `PresidentialPardonForm.cpp/hpp`, `main.cpp`

**Concrete Form Classes**:
- `ShrubberyCreationForm`: Creates file with ASCII trees
- `RobotomyRequestForm`: 50% success rate robotomy
- `PresidentialPardonForm`: Pardon from Zaphod Beeblebrox

**Example Output**:
```
$> ./abstract_forms
Bureaucrat constructor called: Bob (grade 1)
AForm constructor called: Shrubbery Creation Form
AForm constructor called: Robotomy Request Form  
AForm constructor called: Presidential Pardon Form

Bob signs Shrubbery Creation Form
Bob signs Robotomy Request Form
Bob signs Presidential Pardon Form

Executing Shrubbery Creation Form...
Creating ASCII trees in home_shrubbery...
File home_shrubbery created successfully!

Executing Robotomy Request Form...
Drilling noises... brrrrrrr
Robotomy successful!

Executing Presidential Pardon Form...
Zaphod Beeblebrox pardons home. All is forgiven!

AForm destructor called: Presidential Pardon Form
AForm destructor called: Robotomy Request Form
AForm destructor called: Shrubbery Creation Form
Bureaucrat destructor called: Bob
```

**Key Concepts**:
- Abstract base class (AForm)
- Pure virtual functions
- Specialized form behavior
- File I/O operations

### Exercise 03: Intern Class
**Objective**: Implement Intern that can create forms dynamically.

**Files**: `Makefile`, `Bureaucrat.cpp/hpp`, `AForm.cpp/hpp`, `ShrubberyCreationForm.cpp/hpp`, `RobotomyRequestForm.cpp/hpp`, `PresidentialPardonForm.cpp/hpp`, `Intern.cpp/hpp`, `main.cpp`

**Key Function**:
```cpp
AForm* makeForm(std::string formName, std::string target);
```

**Forms Created**:
- "shrubbery creation"
- "robotomy request" 
- "presidential pardon"

**Example Output**:
```
$> ./intern
Intern constructor called
Bureaucrat constructor called: Bob (grade 1)

Intern creates shrubbery creation form for garden...
ShrubberyCreationForm constructor called

Intern creates robotomy request form for Marvin...
RobotomyRequestForm constructor called

Intern creates presidential pardon form for Arthur...
PresidentialPardonForm constructor called

Intern attempts to create unknown form...
Exception: Form name not recognized!

Bob signs all forms...
Bob executes all forms...

Creating ASCII trees in garden_shrubbery...
Drilling noises... brrrrrrr
Robotomy successful!
Zaphod Beeblebrox pardons Arthur. All is forgiven!

AForm destructor called: PresidentialPardonForm
AForm destructor called: RobotomyRequestForm  
AForm destructor called: ShrubberyCreationForm
Bureaucrat destructor called: Bob
Intern destructor called
```

**Key Concepts**:
- Factory pattern
- Dynamic object creation
- String-based type creation
- Memory management with pointers

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
- Custom exception classes must inherit from `std::exception`
- Proper handling of const member variables
- Deep copying where required
