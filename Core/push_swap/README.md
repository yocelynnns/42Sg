# Push_swap

**Because Swap_push doesn't feel as natural** - A sorting algorithm project that sorts data on a stack with a limited set of instructions, aiming for the lowest possible number of operations.

## Project Information

| Field | Description |
|-------|-------------|
| **Program Name** | `push_swap` |
| **Files** | `Makefile`, `*.h`, `*.c` |
| **Makefile Targets** | `NAME`, `all`, `clean`, `fclean`, `re` |
| **Arguments** | Stack A: A list of integers |
| **External Functions** | `read`, `write`, `malloc`, `free`, `exit`, `ft_printf` or equivalent |
| **Libft Authorized** | Yes |

## 🎯 Project Overview

This project involves sorting integers on Stack A using only a limited set of operations with Stack B as auxiliary storage. The goal is to find the most efficient sequence of operations to sort the stack.

### Performance Achieved: 94/100
- **100 numbers**: Under 700 operations ✅
- **500 numbers**: Under 5500 operations ✅  
- Efficient algorithm with room for minor optimizations

## 🏗️ Architecture & File Structure

```
push_swap/
├── Makefile
├── inc/
│   └── push_swap.h
└── src/
    ├── commands/
    │   ├── push.c          # pa, pb operations
    │   ├── rev_rotate.c    # rra, rrb, rrr operations
    │   ├── rotate.c        # ra, rb, rr operations
    │   └── swap.c          # sa, sb, ss operations
    ├── push_swap/
    │   ├── ft_libft.c      # Custom libft functions
    │   ├── ft_split.c      # String splitting
    │   ├── handle_errors.c # Error handling
    │   ├── lists.c         # Linked list operations
    │   ├── push_swap.c     # Main program
    │   ├── stack_init.c    # Stack initialization
    │   └── utils.c         # Utility functions
    └── sorting/
        ├── sort_stacks.c   # Main sorting logic
        ├── sorting.c       # Small stack sorting (3, 5 elements)
        ├── stack_a_to_b.c  # Pushing from A to B
        └── stack_b_to_a.c  # Pushing from B to A
```

## 🔧 Operations Available

| Operation | Description |
|-----------|-------------|
| `sa`, `sb` | Swap first two elements |
| `ss` | `sa` and `sb` simultaneously |
| `pa`, `pb` | Push from one stack to another |
| `ra`, `rb` | Rotate stack upward |
| `rr` | `ra` and `rb` simultaneously |
| `rra`, `rrb` | Reverse rotate stack downward |
| `rrr` | `rra` and `rrb` simultaneously |

## 🚀 Sorting Strategy

### For Small Stacks (2-5 elements)
- **2 elements**: Single `sa` if needed
- **3 elements**: Custom algorithm to sort in max 2 operations
- **4-5 elements**: Push smallest to B, sort remaining 3, push back

### For Large Stacks (6+ elements)
**Chunk-based Algorithm:**
1. **Index Assignment**: Assign each number a position index
2. **Range-based Pushing**: Push elements in ranges from A to B
3. **Smart Sorting**: Push back from B to A in correct order
4. **Optimized Rotations**: Minimize operations using double rotations

## 🛠️ Build & Usage

### Compilation
```bash
make
```

### Basic Usage
```bash
# Sort numbers
./push_swap 4 67 3 87 23

# Check operation count
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

# Validate sorting
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
```

## 📊 Performance Metrics

### Current Performance (94/100)
- **3 numbers**: 2 operations max
- **5 numbers**: 12 operations max  
- **100 numbers**: ~650 operations (under 700 limit)
- **500 numbers**: ~5200 operations (under 5500 limit)

### Optimization Targets
- Reduce rotation counts in chunk management
- Improve range selection algorithm
- Optimize double operation usage (rr, rrr, ss)

## 🔍 Key Functions

### Core Data Structures
```c
typedef struct s_node {
    int             data;
    int             index;
    struct s_node   *next;
    struct s_node   *prev;
} t_node;

typedef struct s_median {
    int value;
    int index;
} t_median;
```

### Main Sorting Logic
```c
void sort_stacks(t_node **stack_a, t_node **stack_b);
void process_nodes_with_fixed_ranges(t_node **stack_a, t_node **stack_b, int total_elements);
void find_and_push_biggest(t_node **stack_a, t_node **stack_b);
```

## 🧪 Testing Commands

### Basic Validation
```bash
# Test with provided checker
ARG="2 1 3"; ./push_swap $ARG | ./checker_OS $ARG

# Test error handling
./push_swap "1" "2" "abc"          # Should show "Error"
./push_swap "1" "2" "1"            # Should show "Error" (duplicate)
./push_swap "2147483648" "1" "2"   # Should show "Error" (overflow)
```

## 🎯 Evaluation Guide

### During Defense
1. **Explain your algorithm** - Chunk-based approach with range optimization
2. **Demonstrate sorting** - Show it works for various input sizes
3. **Discuss optimizations** - Range selection, rotation minimization
4. **Handle modifications** - Be prepared to tweak the algorithm

### Common Questions
- **Why chunk-based approach?** - Balances efficiency and simplicity
- **How do you choose chunk sizes?** - Based on sqrt(n) with adjustments
- **What's your rotation strategy?** - Prefer double rotations, minimize singles
- **How handle edge cases?** - Special algorithms for small stacks

## 📈 Potential Improvements

### For 100% Score
- **Turbo Mode**: Implement more aggressive chunk optimization
- **Rotation Counting**: Better cost analysis for rotation decisions  
- **Adaptive Ranges**: Dynamic range adjustment based on stack state
- **Lookahead**: Consider future operations in current decisions

### Code Optimizations
- Reduce function call overhead
- Optimize linked list traversals
- Improve memory access patterns

## ⚠️ Important Notes

- **Error Handling**: Properly handles duplicates, overflows, invalid input
- **Memory Management**: No leaks, all allocated memory freed
- **Norm Compliance**: Follows 42 coding standards
- **Efficiency**: Meets operation count requirements for grading

---

**Pro Tip**: The key to push_swap is balancing between pushing elements to B and bringing them back sorted. Focus on minimizing expensive operations like single rotations and maximizing double operations!
