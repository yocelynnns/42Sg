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

void	rra(t_node **stack_a)
{
	t_node	*prev;
	t_node	*curr;

	prev = NULL;
	curr = *stack_a;
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
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

int	check_sorted(t_node *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->data > stack->next->data) 
			return (0); //Check if curr node value > next node
		stack = stack->next; 
	}
	return (1);
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

// Function to print a list with labels for clarity
void print_list_with_label(t_node *stack, const char *label)
{
    t_node *current = stack;

    printf("%s: ", label);
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

void process_nodesb(t_node **stack_a, t_node **stack_b, int median_value)
{
    int total_nodes = count_nodes(*stack_b); // Count total nodes in stack_a
    int nodes_processed = 0;

    while (nodes_processed < total_nodes)
    {
        t_node *current = *stack_b;

        if (current->data > median_value)
        {
            pa(stack_b, stack_a); // Move node to stack B
        }
        else
        {
            // Check if all remaining nodes in stack A are greater than or equal to the median
            t_node *temp = *stack_b;
            int has_bigger = 0;

            // Look ahead to see if there are still nodes smaller than the median
            while (temp)
            {
                if (temp->data > median_value)
                {
                    has_bigger = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!has_bigger)
                break; // Stop rotating if all remaining nodes are >= median_value

            rb(stack_b); // Rotate current node to the end
        }

        nodes_processed++;
    }
}

void process_nodes_for_b(t_node **stack_a, t_node **stack_b)
{
    t_node *temp_stack;
    t_median median;

    // Keep processing until stack A is small enough or empty
    while (count_nodes(*stack_b) > 1)
    {

        if (count_nodes(*stack_b) == 2)
        {
            break;
        }
        // Copy the current stack A
        temp_stack = copy_list(*stack_b);
        if (!temp_stack)
        {
            printf("Memory allocation failed\n");
            return;
        }

        // Sort the copied list
        temp_stack = sort_list(temp_stack);

        // Print the temporary sorted list
        print_list_with_label(temp_stack, "Temporary Sorted List");

        // Find the median of the sorted list
        median = find_median(temp_stack);

        printf("New Median value: %d\n", median.value);

        if (check_sorted(*stack_a))
        {
            break;
        }
        // Process nodes based on the new median value
        process_nodesb(stack_a, stack_b, median.value);

        // Print the final state of both stacks after each iteration
        print_list_with_label(*stack_a, "Stack A after processing new median");
        print_list_with_label(*stack_b, "Stack B");

        // Free the temporary stack
        free_list(temp_stack);
    }
}

void process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
    t_node *temp_stack;
    t_median median;

    // Keep processing until stack A is small enough or empty
    while (count_nodes(*stack_a) > 1)
    {
        // Stop if stack A is left with 2 nodes
        if (count_nodes(*stack_a) == 2)
        {
            if (check_sorted(*stack_a))
            {
                process_nodes_for_b(stack_a, stack_b);
            }
        }

        // Copy the current stack A
        temp_stack = copy_list(*stack_a);
        if (!temp_stack)
        {
            printf("Memory allocation failed\n");
            return;
        }

        // Sort the copied list
        temp_stack = sort_list(temp_stack);

        // Print the temporary sorted list
        print_list_with_label(temp_stack, "Temporary Sorted List");

        // Find the median of the sorted list
        median = find_median(temp_stack);

        printf("New Median value: %d\n", median.value);

        // Process nodes based on the new median value
        process_nodes(stack_a, stack_b, median.value);

        // Print the final state of both stacks after each iteration
        print_list_with_label(*stack_a, "Stack A after processing new median");
        print_list_with_label(*stack_b, "Stack B");

        // Free the temporary stack
        free_list(temp_stack);
    }
}

int main(int argc, char **argv)
{
    (void)argc; // To suppress unused parameter warning
    t_node *stack_a = NULL;
    t_node *stack_b = NULL;

    if (argc < 2)
    {
        printf("Usage: %s <numbers>\n", argv[0]);
        return EXIT_FAILURE;
    }

    initial_a(&stack_a, &argv[1]);

    printf("Initial Stack A: ");
    print_list(stack_a);

    process_nodes_with_new_median(&stack_a, &stack_b);

    // Free remaining nodes
    free_list(stack_a);
    free_list(stack_b);

    return EXIT_SUCCESS;
}
