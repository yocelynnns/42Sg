# C++ - Module 00

## 📋 Project Overview
This module introduces fundamental C++ concepts including namespaces, classes, member functions, stdio streams, initialization lists, static, const, and other basic C++ features.

## 🏗️ Project Structure
```
cpp00/
├── ex00/ - Megaphone
│   ├── Makefile
│   └── megaphone.cpp
├── ex01/ - My Awesome PhoneBook
│   ├── Makefile
│   ├── main.cpp
│   ├── PhoneBook.cpp
│   ├── PhoneBook.hpp
│   ├── Contact.cpp
│   └── Contact.hpp
├── ex02/ - The Job Of Your Dreams
│   ├── Makefile
│   ├── Account.cpp
│   ├── Account.hpp
│   └── tests.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Megaphone
**Objective**: Create a program that converts input to uppercase.

**Files**: `Makefile`, `megaphone.cpp`

**Usage**:
```bash
./megaphone "hello world"
# Output: HELLO WORLD

./megaphone
# Output: * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

**Key Concepts**:
- Command line arguments
- String manipulation
- Standard output

### Exercise 01: My Awesome PhoneBook
**Objective**: Implement a simple phonebook application using classes.

**Files**: `Makefile`, `*.cpp`, `*.{h, hpp}`

**Classes**:
- `PhoneBook`: Manages up to 8 contacts
- `Contact`: Stores contact information

**Commands**:
- `ADD`: Add new contact
- `SEARCH`: Display and search contacts
- `EXIT`: Quit program

**Features**:
- Fixed array storage (no dynamic allocation)
- Formatted output with column alignment
- Input validation

**Example Output**:
```
PHONEBOOK
> ADD
Enter first name: John
Enter last name: Doe
Enter nickname: JD
Enter phone number: 1234567890
Enter darkest secret: afraid of spiders
Contact added!

> SEARCH
     INDEX|FIRST NAME| LAST NAME|  NICKNAME
         0|      John|       Doe|        JD
         1|     Alice|     Smith|      Alie
Enter index: 1
First Name: Alice
Last Name: Smith  
Nickname: Alie
Phone: 0987654321
Darkest Secret: hates carrots
```

### Exercise 02: The Job Of Your Dreams
**Objective**: Recreate a missing `Account.cpp` file based on provided header and log output.

**Files**: `Makefile`, `Account.cpp`, `Account.hpp`, `tests.cpp`

**Key Concepts**:
- Static member variables and functions
- Constructor/destructor behavior
- Logging and debugging

**Example Output**:
```bash
$> ./account
19920104_091532: accounts:8;total:20049;deposits:0;withdrawals:0
19920104_091532: index:0;amount:42;deposits:0;withdrawals:0
19920104_091532: index:1;amount:54;deposits:0;withdrawals:0
19920104_091532: index:2;amount:957;deposits:0;withdrawals:0
19920104_091532: index:3;amount:432;deposits:0;withdrawals:0
19920104_091532: index:4;amount:1234;deposits:0;withdrawals:0
19920104_091532: index:5;amount:0;deposits:0;withdrawals:0
19920104_091532: index:6;amount:754;deposits:0;withdrawals:0
19920104_091532: index:7;amount:16576;deposits:0;withdrawals:0

19920104_091532: index:0;p_amount:42;deposit:5;amount:47;withdrawal:0
19920104_091532: index:1;p_amount:54;deposit:765;amount:819;withdrawal:0
19920104_091532: index:2;p_amount:957;deposit:564;amount:1521;withdrawal:0
19920104_091532: index:3;p_amount:432;deposit:2;amount:434;withdrawal:0
19920104_091532: index:4;p_amount:1234;deposit:87;amount:1321;withdrawal:0
19920104_091532: index:5;p_amount:0;deposit:23;amount:23;withdrawal:0
19920104_091532: index:6;p_amount:754;deposit:9;amount:763;withdrawal:0
19920104_091532: index:7;p_amount:16576;deposit:20;amount:16596;withdrawal:0
19920104_091532: total:21524;deposits:1475;withdrawals:0

19920104_091532: index:0;p_amount:47;deposit:0;amount:47;withdrawal:4
19920104_091532: index:1;p_amount:819;deposit:0;amount:819;withdrawal:34
19920104_091532: index:2;p_amount:1521;deposit:0;amount:1521;withdrawal:657
19920104_091532: index:3;p_amount:434;deposit:0;amount:434;withdrawal:4
19920104_091532: index:4;p_amount:1321;deposit:0;amount:1321;withdrawal:76
19920104_091532: index:5;p_amount:23;deposit:0;amount:23;withdrawal:12
19920104_091532: index:6;p_amount:763;deposit:0;amount:763;withdrawal:657
19920104_091532: index:7;p_amount:16596;deposit:0;amount:16596;withdrawal:7654
19920104_091532: total:19024;deposits:0;withdrawals:9098

19920104_091532: accounts:8;total:19024;deposits:1475;withdrawals:9098
```

## 🔧 Compilation
**Each exercise has its own Makefile** with the following standard rules:
- `make` or `make all` - compiles the program
- `make clean` - removes object files
- `make fclean` - removes object files and executable
- `make re` - recompiles everything

```bash
# Compile with C++98 standard (enforced by Makefile)
c++ -Wall -Wextra -Werror -std=c++98

# Example compilation for each exercise:
cd ex00 && make
cd ex01 && make  
cd ex02 && make
```

## ⚠️ Important Notes
- No `using namespace` allowed
- No STL containers or algorithms
- Follow Orthodox Canonical Form (starting Module 02)
- Memory leaks are strictly forbidden
- All heap memory must be properly freed
- Header files must have include guards
- Each header should include its own dependencies
- **Each exercise is self-contained with its own Makefile**
