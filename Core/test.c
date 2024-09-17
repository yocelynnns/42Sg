#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

typedef struct s_chunk
{
    int *elements;
    int size;
} t_chunk;

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

    median.value = current->data;
    median.index = mid_position; // Index of the middle value

    return median;
}

// Function to push node from stack A to stack B
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

void pa(t_node **stack_a, t_node **stack_b)
{
    t_node *top_b;

    if (*stack_b == NULL)
        return;

    top_b = *stack_b;
    *stack_b = top_b->next;

    if (*stack_b)
        (*stack_b)->prev = NULL;

    top_b->next = *stack_a;
    if (*stack_a)
        (*stack_a)->prev = top_b;

    *stack_a = top_b;
    printf("pa\n");
}

// Function to rotate stack A
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

void rb(t_node **stack_b)
{
    t_node *first;
    t_node *last;

    first = *stack_b;
    last = first;
    if (*stack_b == NULL || (*stack_b)->next == NULL)
        return;
    while (last->next != NULL)
        last = last->next;
    *stack_b = first->next;
    first->next = NULL;
    last->next = first;
    printf("rb\n");
}

void rra(t_node **stack_a)
{
    t_node *prev;
    t_node *curr;

    prev = NULL;
    curr = *stack_a;
    if (*stack_a == NULL || (*stack_a)->next == NULL)
        return;
    while (curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev != NULL)
    {
        prev->next = NULL;
        curr->next = *stack_a;
        *stack_a = curr;
        printf("rra\n");
    }
}

void process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
    int total_nodes = count_nodes(*stack_a); // Count total nodes in stack_a
    int nodes_processed = 0;

    while (nodes_processed < total_nodes)
    {
        t_node *current = *stack_a;

        if (current->data < median_value)
        {
            pb(stack_a, stack_b); // Move node to stack B
        }
        else
        {
            // Check if all remaining nodes in stack A are greater than or equal to the median
            t_node *temp = *stack_a;
            int has_smaller = 0;
            t_node *last_node = *stack_a;

            while (last_node && last_node->next != NULL)
                last_node = last_node->next;
            // Look ahead to see if there are still nodes smaller than the median
            while (temp)
            {
                if (temp->data < median_value)
                {
                    has_smaller = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!has_smaller)
                break; // Stop rotating if all remaining nodes are >= median_value

            if (last_node->data < median_value)
                rra(stack_a); // Rotate current node to the end
            else
                ra(stack_a);
        }

        nodes_processed++;
    }
}

int check_sorted(t_node *stack)
{
    if (!stack)
        return (1);
    while (stack->next)
    {
        if (stack->data > stack->next->data)
            return (0); // Check if curr node value > next node
        stack = stack->next;
    }
    return (1);
}

// Function to print a list
void print_list(t_node *stack)
{
    t_node *current = stack;
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the list
void free_list(t_node *stack)
{
    t_node *temp;
    while (stack)
    {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}

void create_chunk(t_chunk *new_chunk, int *elements, int size)
{
    new_chunk->size = size;
    new_chunk->elements = (int *)malloc(size * sizeof(int));
    if (new_chunk->elements == NULL)
        free_n_error(NULL);
    memcpy(new_chunk->elements, elements, size * sizeof(int));
}

void process_nodes_in_chunks(t_node **stack_a, t_node **stack_b, t_chunk *chunks)
{
    (void)stack_a; // Mark stack_a as unused to avoid warning
    (void)stack_b; // Mark stack_b as unused to avoid warning
    (void)chunks; // Mark chunks as unused to avoid warning
    // Your logic for processing nodes in chunks
}

int main(int argc, char **argv)
{
    t_node *stack_a = NULL;
    t_node *stack_b = NULL;
    t_chunk chunks = {NULL, 0}; // Initialize chunks with NULL and size 0

    if (argc < 2)
    {
        printf("Usage: %s <numbers>\n", argv[0]);
        return (1);
    }

    initial_a(&stack_a, argv + 1);
    stack_a = sort_list(stack_a);
    print_list(stack_a);

    t_median median = find_median(stack_a);
    printf("Median value: %d\n", median.value);

    process_nodes(&stack_a, &stack_b, median.value);
    print_list(stack_a);
    print_list(stack_b);

    // Only free chunks.elements if it was allocated
    if (chunks.elements != NULL)
        free(chunks.elements);

    free_list(stack_a);
    free_list(stack_b);

    return (0);
}
