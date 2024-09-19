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
    int mid_position = node_count / 5;
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
    if (!stack_b || !*stack_b)
    {
        printf("Error: Stack B is empty\n");
        return;
    }

    if (!stack_a || !*stack_a)
    {
        printf("Error: Stack A is empty\n");
        return;
    }

    t_node *first_b = *stack_b;
    *stack_b = (*stack_b)->next;
    first_b->next = *stack_a;
    *stack_a = first_b;
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

void rrb(t_node **stack_b)
{
    if (!stack_b || !*stack_b || !(*stack_b)->next)
    {
        printf("Error: Stack B is empty or has only one node\n");
        return;
    }

    t_node *last = *stack_b;
    while (last->next->next)
        last = last->next;

    t_node *second_last = last;
    last = last->next;
    second_last->next = NULL;
    last->next = *stack_b;
    *stack_b = last;
    printf("rrb\n");
}

void rra(t_node **stack_a)
{
    if (!stack_a || !*stack_a || !(*stack_a)->next)
    {
        printf("Error: Stack A is empty or has only one node\n");
        return;
    }

    t_node *last = *stack_a;
    while (last->next->next)
        last = last->next;

    t_node *second_last = last;
    last = last->next;
    second_last->next = NULL;
    last->next = *stack_a;
    *stack_a = last;
    printf("rra\n");
}

void sa(t_node **stack_a)
{
    if (!stack_a || !*stack_a || !(*stack_a)->next)
    {
        printf("Error: Stack A is empty or has only one node\n");
        return;
    }

    t_node *first = *stack_a;
    t_node *second = (*stack_a)->next;
    *stack_a = second;
    first->next = second->next;
    second->next = first;
    printf("sa\n");
}

void	sb(t_node **stack_b)
{
	if (*stack_b && (*stack_b)->next)
	{
		t_node	*first;
		t_node	*second;

		first = *stack_b;
		second = first->next;
		if (*stack_b == NULL || (*stack_b)->next == NULL)
		    return ;
        first->next = second->next;
        second->next = first;
        *stack_b = second;
		printf("sb\n");
    }
}

int	stack_size(t_node *stack) 
{
	int	count;

	if (!stack) 
		return (0);
	count = 0;
	while (stack) 
	{
		stack = stack->next; 
		count++;
	}
	return (count);
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

int	stack_sorted(t_node *stack)
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

void print_list_with_label(t_node *stack, const char *label)
{
    if (!stack)
    {
        printf("%s: List is empty\n", label);
        return;
    }

    printf("%s: ", label);
    t_node *current = stack;
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

t_node	*find_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next != NULL)
		stack = stack->next;
	return (stack);
}

t_node	*find_max(t_node *stack) 
{
	long			largest; //largest value
	t_node	*largest_n; //pointer to largest number

	if (!stack)
		return (NULL);
	largest = LONG_MIN; 
	while (stack) 
	{
		if (stack->data > largest) 
		{
			largest = stack->data; 
			largest_n = stack; 
		}
		stack = stack->next;
	}
	return (largest_n);
}

t_node	*find_min(t_node *stack) 
{
	long			smallest; //smallest value
	t_node	*smallest_n; //pointer to smallest number

	if (!stack)
		return (NULL);
	smallest = LONG_MAX;
	while (stack)
	{
		if (stack->data < smallest) 
		{
			smallest = stack->data; 
			smallest_n = stack; 
		}
		stack = stack->next;
	}
	return (smallest_n); 
}

void	sort_three(t_node **stack_a) 
{
	t_node	*biggest; 

	biggest = find_max(*stack_a);
	if (*stack_a == biggest)
		ra(stack_a); //If the 1st node is the biggest rotate to bottom
	else if ((*stack_a)->next == biggest) 
		rra(stack_a); //If the 2nd node is the biggest rerotate bottom to top
	if ((*stack_a)->data > (*stack_a)->next->data) 
		sa(stack_a); //If the bottom node is the biggest, but the top node is higher than the second node, swap 
}

void sort_five(t_node **stack_a, t_node **stack_b)
{
    if (stack_size(*stack_a) == 4)
        pb(stack_a, stack_b);  // Push one node to stack B
    else
    {
        pb(stack_a, stack_b);  // Push two nodes to stack B
        pb(stack_a, stack_b);
    }

    sort_three(stack_a);  // Sort the remaining 3 nodes in stack A

    // Ensure the two nodes in stack B are sorted before pushing back to stack A
    if (stack_size(*stack_b) == 2 && (*stack_b)->data < (*stack_b)->next->data)
        sb(stack_b);  // Swap in stack B

    // Push back from stack B to stack A
    pa(stack_a, stack_b);

    // Check if the node just pushed needs to be rotated to its correct position
    if ((*stack_a)->data > find_last_node(*stack_a)->data)
        ra(stack_a);

    pa(stack_a, stack_b);

    // Final check if sorting is needed after all pushes
    if ((*stack_a)->data > (*stack_a)->next->data)
        sa(stack_a);

    // Ensure stack A is fully sorted
    while (!stack_sorted(*stack_a))
    {
        // If stack A is not sorted, rotate or swap as needed
        if ((*stack_a)->data > (*stack_a)->next->data)
            sa(stack_a);
        else
            ra(stack_a);
    }
}


void process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
    t_node *temp_stack;
    t_median median;

    // Keep processing until stack A is small enough or empty
    while (count_nodes(*stack_a) > 1)
    {
        // Stop if stack A is left with 5 or fewer nodes, and handle sorting separately
        if (count_nodes(*stack_a) <= 5)
        {
            sort_five(stack_a, stack_b);  // Use a specialized sort for small lists
            break;
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

        // // Print the temporary sorted list
        // print_list_with_label(temp_stack, "Temporary Sorted List");

        // Find the median of the sorted list
        median = find_median(temp_stack);

        // printf("New Median value: %d\n", median.value);

        // Process nodes based on the new median value
        process_nodes(stack_a, stack_b, median.value);

        // // Print the final state of both stacks after each iteration
        // print_list_with_label(*stack_a, "Stack A after processing new median");
        // print_list_with_label(*stack_b, "Stack B");

        // Free the temporary sorted list
        if (temp_stack)
            free_list(temp_stack);
    }
}

void find_and_push_biggest(t_node **stack_a, t_node **stack_b)
{
    while (*stack_b)
    {
        if (!*stack_b)
            return;

        t_node *biggest = find_max(*stack_b);
        t_node *current = *stack_b;
        t_node *last_node = *stack_b;
        int is_biggest = 0;

        while (last_node && last_node->next != NULL)
                last_node = last_node->next;

        // Traverse the stack to find the biggest number
        while (current->next)
        {
            current = current->next;
            if (current->data > biggest->data)
            {
                biggest = current;
                is_biggest = 0;
            }
        }

        // If the biggest number is not the first node, rotate the stack accordingly
        if (!is_biggest)
        {
            while (biggest != *stack_b)
            {
                if (last_node->data == biggest->data)
                    rrb(stack_b); 
                else
                    rb(stack_b);
            }
        }
        // Push the biggest number to stack A
        pa(stack_a, stack_b);
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

    // printf("Initial Stack A: ");
    // print_list(stack_a);

    if (stack_a)
        process_nodes_with_new_median(&stack_a, &stack_b);

    printf("Final Stack A: ");
    print_list(stack_a);

    printf("Final Stack B: ");
    print_list(stack_b);

    find_and_push_biggest(&stack_a, &stack_b);

    printf("Final Stack A: ");
    print_list(stack_a);

    printf("Final Stack B: ");
    print_list(stack_b);

    // Free remaining nodes
    free_list(stack_a);
    free_list(stack_b);

    return EXIT_SUCCESS;
}

