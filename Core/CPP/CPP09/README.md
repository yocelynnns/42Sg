# C++ - Module 09

## 📋 Project Overview
This module focuses on practical applications of STL algorithms and container operations through real-world problems.

## 🏗️ Project Structure
```
cpp09/
├── ex00/ - Bitcoin Exchange
│   ├── Makefile
│   ├── data.csv
│   ├── input.txt
│   ├── inc/
│   │   └── BitcoinExchange.hpp
│   └── src/
│       ├── BitcoinExchange.cpp
│       └── main.cpp
├── ex01/ - Reverse Polish Notation
│   ├── Makefile
│   ├── inc/
│   │   └── RPN.hpp
│   └── src/
│       ├── RPN.cpp
│       └── main.cpp
├── ex02/ - PmergeMe
│   ├── Makefile
│   ├── inc/
│   │   └── PmergeMe.hpp
│   └── src/
│       ├── PmergeMe.cpp
│       └── main.cpp
└── README.md
```

## 🚀 Exercise Details

### Exercise 00: Bitcoin Exchange
**Objective**: Create a program that calculates Bitcoin values based on historical data.

**Files**: `Makefile`, `BitcoinExchange.hpp/cpp`, `main.cpp`, `data.csv`, `input.txt`

**Program Requirements**:
- Name: `btc`
- Takes input file as argument
- Input format: `date | value`
- Valid date: `Year-Month-Day`
- Valid value: float between 0 and 1000
- Uses closest earlier date if exact date not found

**Example Output**:
```
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

**Key Concepts**:
- File I/O operations
- Date parsing and validation
- Map containers for efficient lookups
- Error handling
- CSV data processing

### Exercise 01: Reverse Polish Notation
**Objective**: Implement a Reverse Polish Notation calculator.

**Files**: `Makefile`, `RPN.hpp/cpp`, `main.cpp`

**Program Requirements**:
- Name: `RPN`
- Takes RPN expression as argument
- Supports operators: `+ - / *`
- Numbers must be less than 10
- Proper error handling

**Example Output**:
```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
$> ./RPN "1 2 3 +"
Error
```

**Key Concepts**:
- Stack-based calculations
- Token parsing
- Arithmetic operations
- Error validation
- Stack container usage

### Exercise 02: PmergeMe
**Objective**: Implement the merge-insertion sort algorithm with multiple containers.

**Files**: `Makefile`, `PmergeMe.hpp/cpp`, `main.cpp`

**Program Requirements**:
- Name: `PmergeMe`
- Sorts positive integer sequences using Ford-Johnson algorithm
- Uses at least two different containers
- Handles at least 3000 integers
- Displays timing comparisons

**Example Output**:
```
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector: 0.00031 us
Time to process a range of 5 elements with std::deque: 0.00014 us

$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr '\n' ' '`
Before: 141 79 526 321 [...]
After: 79 141 321 526 [...]
Time to process a range of 3000 elements with std::vector: 62.14389 us
Time to process a range of 3000 elements with std::deque: 69.27212 us

$> ./PmergeMe "-1" "2"
Error
```

**Key Concepts**:
- Merge-insertion sort algorithm
- Multiple container implementations
- Performance measurement
- Large dataset handling
- Algorithm complexity

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

## ⚠️ Important Module Rules
- **Container Restriction**: Once a container is used in an exercise, it cannot be reused in subsequent exercises
- **Mandatory STL Usage**: Must use standard containers for each exercise
- **Exercise 02**: Requires at least two different containers
- **Performance**: Programs must handle large datasets efficiently (3000+ elements for PmergeMe)
- **Error Handling**: Comprehensive error handling required for all user inputs

## 🔧 Key Learning Points
- STL container selection and usage
- Algorithm implementation and optimization
- File parsing and data processing
- Performance measurement and analysis
- Error handling and input validation
- Real-world problem solving with STL
- Container performance characteristics

## 📊 Container Usage Strategy
- Choose appropriate containers based on exercise requirements
- Consider performance implications of different containers
- Document container choices and reasoning
- Ensure compliance with container reuse restrictions
