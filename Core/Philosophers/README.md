# Philosophers

## 📋 Project Overview
A multithreading simulation of the dining philosophers problem, where philosophers alternate between eating, thinking, and sleeping while avoiding starvation using mutex synchronization.

## 🏗️ Project Structure
```
Philosophers/
├── Makefile
├── philo.h
├── philo.c
├── init.c
├── simulation.c
├── monitor.c
├── utils.c
├── ft_libft.c
└── en.subject.pdf
```

## 🚀 Program Usage

### Compilation
```bash
make
```

### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments
- `number_of_philosophers`: Number of philosophers and forks (≥1)
- `time_to_die`: Time in ms before philosopher dies if not eating
- `time_to_eat`: Time in ms philosopher spends eating
- `time_to_sleep`: Time in ms philosopher spends sleeping
- `[number_of_times_each_philosopher_must_eat]`: Optional - stops simulation when all philosophers reach this meal count

## 🔧 Core Features

### Thread Management
- Each philosopher runs as a separate thread
- Dedicated monitor thread for death detection
- Proper thread creation, joining, and cleanup

### Synchronization
- Mutex protection for each fork
- Print mutex to prevent output interleaving
- Meal count and state mutexes for data consistency

### Simulation Rules
- Philosophers must acquire both adjacent forks to eat
- Even-numbered philosophers start by taking right fork first
- Odd-numbered philosophers start by taking left fork first
- Simulation stops when any philosopher dies or all reach meal target

## 📊 Output Format
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

## 🎯 Example Usage

### Basic Simulation
```bash
./philo 5 800 200 200
```
5 philosophers with 800ms time to die, 200ms eating time, 200ms sleeping time

### Simulation with Meal Limit
```bash
./philo 4 410 200 200 5
```
4 philosophers, stops when each has eaten 5 times

### Single Philosopher (Edge Case)
```bash
./philo 1 800 200 200
```
Single philosopher dies immediately (cannot eat with one fork)

## ⚠️ Important Notes

- **No global variables** used in implementation
- **No data races** - proper mutex protection
- **Strict Norm compliance** required
- **Proper memory management** - no leaks
- **Error handling** for invalid inputs and system calls

## 🔍 Testing Examples

### Basic Functionality
```bash
# Normal simulation
./philo 3 600 200 200

# With meal limit
./philo 4 800 200 200 3

# Large number test
./philo 10 800 200 200
```

### Edge Cases
```bash
# Single philosopher (should die)
./philo 1 800 200 200

# Very short times
./philo 2 200 100 100

# Meal count only
./philo 3 1000 200 200 1
```

### Error Cases
```bash
# Invalid number of philosophers
./philo 0 800 200 200

# Negative times
./philo 3 -100 200 200

# Too many arguments
./philo 3 800 200 200 5 10
```

## 🛠️ Technical Implementation

### Data Structures
```c
typedef struct s_philo {
    int             id;
    int             meals_count;
    long            last_meal;
    pthread_t       thread_id;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *next_fork;
    pthread_mutex_t meal_mutex;
    t_table         *table;
} t_philo;

typedef struct s_table {
    int             philo_nbr;
    long            die_time;
    long            eat_time;
    long            sleep_time;
    long            start_time;
    int             max_meals;
    int             alive;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mtx;
    pthread_mutex_t state_mutex;
    pthread_t       monitor_thread;
    t_philo         *philo;
} t_table;
```

### Execution Flow
1. **Initialization**: Parse arguments, create mutexes, initialize philosophers
2. **Thread Creation**: Create philosopher threads and monitor thread
3. **Simulation**: Philosophers run their lifecycle routines
4. **Monitoring**: Continuous death checking and meal count verification
5. **Cleanup**: Join threads, destroy mutexes, free memory

### Key Functions
- `philo_routine()`: Main philosopher lifecycle
- `monitoring()`: Death detection and simulation control
- `take_forks()`: Fork acquisition with deadlock prevention
- `eat()`: Eating phase with meal tracking
- `sleep_and_think()`: Resting phases

## 🧪 Validation

### Memory Leak Checking
```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 3 800 200 200
```

### Race Condition Testing
```bash
# Run multiple times to check for consistency
for i in {1..10}; do ./philo 4 410 200 200 5; done
```

### Performance Testing
```bash
# Test with many philosophers
./philo 50 800 200 200

# Test with tight timing constraints
./philo 5 400 200 200
```

## 🎓 Learning Objectives

- **Multithreading** with pthreads
- **Mutex synchronization** and deadlock prevention
- **Resource management** in concurrent systems
- **Real-time simulation** and timing control
- **Error handling** in multithreaded environments

---

**Evaluation Tip**: Focus on demonstrating proper synchronization, deadlock prevention, and robust error handling during defense. Test edge cases thoroughly!
