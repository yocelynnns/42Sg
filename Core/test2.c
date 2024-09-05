#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
    struct s_node *prev;
} t_node;

typedef struct s_median
{
    int value;
    int index;
} t_median;

// Function to create a new node
t_node *create_node(int value)
{
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Function to add a node to the back of the list
void add_back(t_node **stack, t_node *new_node)
{
    t_node *temp;

    if (!*stack)
    {
        *stack = new_node;
        return;
    }
    temp = *stack;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
}

// Error handling function
void free_n_error(t_node **stack)
{
    (void)stack; // Mark stack as unused to avoid warning
    printf("Error\n");
    exit(EXIT_FAILURE);
}

// Utility function to convert string to long
long ft_atol(const char *str)
{
    long result = 0;
    int sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

// Function to check for duplicate values
int check_dup(t_node *stack, int value)
{
    while (stack)
    {
        if (stack->data == value)
            return 1;
        stack = stack->next;
    }
    return 0;
}

// Simple argument validation function
int error_argvs(char *arg)
{
    for (int i = 0; arg[i]; i++)
    {
        if ((arg[i] < '0' || arg[i] > '9') && arg[i] != '-' && arg[i] != '+')
            return 1; // Error found
    }
    return 0;
}

// Function to initialize stack A
void initial_a(t_node **stack_a, char **argv)
{
    t_node *new_node;
    long value;
    int i = 0;

    while (argv[i])
    {
        if (error_argvs(argv[i]))
            free_n_error(stack_a);
        value = ft_atol(argv[i]);
        if (value > INT_MAX || value < INT_MIN)
            free_n_error(stack_a);
        if (check_dup(*stack_a, (int)value))
            free_n_error(stack_a);
        new_node = create_node((int)value); // Create a new node with the converted value
        if (!new_node)
            free_n_error(stack_a);
        add_back(stack_a, new_node);
        i++;
    }
}

// Function to sort the list
t_node *sort_list(t_node *stack_a)
{
    int swap;
    t_node *i;
    t_node *j;
    t_node *end = NULL;

    if (!stack_a)
        return NULL;

    // Outer loop for each pass
    while (end != stack_a->next)
    {
        i = stack_a;
        // Inner loop for comparing adjacent nodes
        while (i->next != end)
        {
            j = i->next;
            if (i->data > j->data)
            {
                // Swap data between i and j
                swap = i->data;
                i->data = j->data;
                j->data = swap;
            }
            i = i->next;
        }
        // After each pass, the largest element is in its correct place
        end = i;
    }
    return stack_a;
}


// Function to count nodes in the list
int count_nodes(t_node *stack)
{
    int count = 0;
    while (stack)
    {
        count++;
        stack = stack->next;
    }
    return count;
}

t_median find_median(t_node *sorted_list)
{
    int node_count = count_nodes(sorted_list);
    t_node *current = sorted_list;
    t_median median;

    if (node_count == 0)
    {
        median.value = 0;
        median.index = 0;
        return median;
    }

    // Traverse to the middle of the list
    int mid_position = node_count / 2;
    int i = 0;
    while (i < mid_position)
    {
        current = current->next;
        i++;
    }

    // if (node_count % 2 == 0)
    // {
    //     // Average of the two middle values
    //     median.value = (current->data + current->prev->data) / 2.0; // Use 2.0 for floating point division
    //     median.index = mid_position - 1; // Index of the first middle value
    // }
    if (node_count % 2 == 0 ||!(node_count % 2 == 0))
    {
        median.value = current->data;
        median.index = mid_position; // Index of the middle value
    }

    return median;
}

// // Function to push node from stack B to stack A
void pb(t_node **stack_a, t_node **stack_b)
{
    t_node *top_a;

    if (*stack_a == NULL)
        return;

    top_a = *stack_a;
    *stack_a = top_a->next;

    if (*stack_a)
        (*stack_a)->prev = NULL;

    top_a->next = *stack_b;
    if (*stack_b)
        (*stack_b)->prev = top_a;

    *stack_b = top_a;
    printf("pb\n");
}

// // Function to rotate stack A
void ra(t_node **stack_a)
{
    t_node *first;
    t_node *last;

    first = *stack_a;
    last = first;
    if (*stack_a == NULL || (*stack_a)->next == NULL)
        return;
    while (last->next != NULL)
        last = last->next;
    *stack_a = first->next;
    first->next = NULL;
    last->next = first;
    printf("ra\n");
}

void process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
    int nodes_processed = 0;
    int total_nodes = count_nodes(*stack_a); // Count total nodes in stack_a

    while (nodes_processed < total_nodes)
    {
        t_node *current = *stack_a;

        if (current->data < median_value)
        {
            pb(stack_a, stack_b); // Move current node to stack B
        }
        else
        {
            ra(stack_a); // Rotate nodes with data >= median_value to the end
        }

        nodes_processed++; // Increase the count of processed nodes
    }
}


// Function to print a list
void print_list(t_node *stack)
{
    t_node *current = stack;

    if (!stack)
    {
        printf("List is empty\n");
        return;
    }

    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free all nodes in a list
void free_list(t_node *stack)
{
    t_node *next;

    while (stack)
    {
        next = stack->next;
        free(stack);
        stack = next;
    }
}


t_node *copy_list(t_node *src)
{
    t_node *new_list = NULL;
    t_node *current = src;
    t_node *new_node;

    while (current)
    {
        new_node = create_node(current->data);
        if (!new_node)
            return NULL;
        add_back(&new_list, new_node);
        current = current->next;
    }
    return new_list;
}

int main(int argc, char **argv)
{
    (void)argc; // Mark argc as unused
    t_node *stack_a = NULL;
    t_node *stack_b = NULL;
    t_node *temp_stack;
    t_median median;

    // Initialize stack A with values from argv
    initial_a(&stack_a, argv + 1);

    // Print the original stack_a
    printf("Original Stack A: ");
    print_list(stack_a);

    // Create a copy of stack_a for sorting
    temp_stack = copy_list(stack_a);
    if (!temp_stack)
    {
        printf("Memory allocation failed\n");
        free_list(stack_a);
        return 1;
    }

    // Sort the copied list
    temp_stack = sort_list(temp_stack);

    // Print the sorted list
    printf("Sorted List (Temporary): ");
    print_list(temp_stack);

    // Find the median of the sorted list
    median = find_median(temp_stack);

    printf("Median value: %d\n", median.value);
    printf("Median index: %d\n", median.index);

    // Process nodes based on median value
    process_nodes(&stack_a, &stack_b, median.value);

    // Print the final states of both stacks
    printf("Final Stack A: ");
    print_list(stack_a);

    printf("Stack B (Nodes moved from A): ");
    print_list(stack_b);

    // Free the memory for temp_stack, stack_a, and stack_b
    free_list(temp_stack);
    free_list(stack_a);
    free_list(stack_b);

    return 0;
}
