# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

// Define your t_node structure and function prototypes
typedef struct s_node {
    int data;
    struct s_node *next;
} t_node;

// Function prototypes for the helper functions you are using
// void pb(t_node **stack_a, t_node **stack_b);
// void pa(t_node **stack_a, t_node **stack_b);
// void sa(t_node **stack_a);
// void ra(t_node **stack_a);
// t_node *find_min(t_node *stack_a);
// t_node *find_last_node(t_node *stack);
// int stack_size(t_node *stack);
// int check_sorted(t_node *stack_a);
// void sort_three(t_node **stack_a);
// void sort_five(t_node **stack_a, t_node **stack_b);

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_b;

	top_b = *stack_b;
	if (*stack_b == NULL)
		return ;
	*stack_b = top_b->next;
	top_b->next = *stack_a;
	*stack_a = top_b;
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;

	top_a = *stack_a;
	if (*stack_a == NULL)
		return ;
	*stack_a = top_a->next;
	top_a->next = *stack_b;
	*stack_b = top_a;
}

void	ra(t_node **stack_a)
{
	t_node	*first;
	t_node	*last;

	first = *stack_a;
	last = first;
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	while (last->next != NULL)
		last = last->next;
	*stack_a = first->next;
	first->next = NULL;
	last->next = first;
	printf("ra\n");
}

void	sa(t_node **stack_a)
{
	if (*stack_a && (*stack_a)->next)
	{
		t_node	*first;
		t_node	*second;

		first = *stack_a;
		second = first->next;
		if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
        first->next = second->next;
        second->next = first;
        *stack_a = second;
		printf("sa\n");
    }
}

void sb(t_node **stack_b)
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

t_node	*find_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next != NULL)
		stack = stack->next;
	return (stack);
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

// Helper function to create a new node
t_node *create_node(int data) {
    t_node *new_node = malloc(sizeof(t_node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Helper function to add node at the back of the list
void add_back(t_node **stack, int data) {
    t_node *new_node = create_node(data);
    if (!*stack) {
        *stack = new_node;
    } else {
        t_node *temp = *stack;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Helper function to print the stack
void print_stack(t_node *stack) {
    while (stack) {
        printf("%d ", stack->data);
        stack = stack->next;
    }
    printf("\n");
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
    while (!check_sorted(*stack_a))
    {
        // If stack A is not sorted, rotate or swap as needed
        if ((*stack_a)->data > (*stack_a)->next->data)
            sa(stack_a);
        else
            ra(stack_a);
    }
}


int main(void) {
    t_node *stack_a = NULL;
    t_node *stack_b = NULL;

    // Add elements to stack_a (modify these values to test with different inputs)
    add_back(&stack_a, 97);
    add_back(&stack_a, 100);
    add_back(&stack_a, 96);
    add_back(&stack_a, 99);
    add_back(&stack_a, 98);

    // Print the original stack_a
    printf("Original stack A: ");
    print_stack(stack_a);

    // Call the sort_five function to sort stack_a
    sort_five(&stack_a, &stack_b);

    // Print the sorted stack_a
    printf("Sorted stack A: ");
    print_stack(stack_a);

    return 0;
}
