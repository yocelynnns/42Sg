#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_node {
    int data;
    struct s_node *next;
    struct s_node *prev;
} t_node;

typedef struct s_median
{
    int value;
    int index;
} t_median;

t_node *last_node = NULL;

static int wordlen(const char *s, char c) {
    int i = 0, wlen = 0;
    while (s[i] && s[i] != c) {
        wlen++;
        i++;
    }
    return wlen;
}

static char *writeword(char const *s, int len) {
    char *word = (char *)malloc((len + 1) * sizeof(char));
    if (!word) return NULL;
    for (int i = 0; i < len; i++) {
        word[i] = s[i];
    }
    word[len] = '\0';
    return word;
}

static char **free_array(char **ptr, int i) {
    while (i > 0) {
        free(ptr[i - 1]);
        i--;
    }
    free(ptr);
    return NULL;
}

static char **split_words(const char *s, char c, int word_count) {
    char **result = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!result) return NULL;
    int i = 0, j = 0;
    while (s[i]) {
        while (s[i] == c) i++;
        if (s[i]) {
            result[j] = writeword(s + i, wordlen(s + i, c));
            if (!result[j]) return free_array(result, j);
            i += wordlen(s + i, c);
            j++;
        }
    }
    result[j] = NULL;
    return result;
}

char **ft_split(char const *s, char c) {
    int word_count = 0, i = 0;
    if (!s) return NULL;
    while (s[i]) {
        if (!(s[i] == c) && ((s[i + 1] == c) || !(s[i + 1]))) {
            word_count++;
        }
        i++;
    }
    return split_words(s, c, word_count);
}

t_node *create_node(int value) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node) return NULL;
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

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

void add_back(t_node **stack, t_node *new_node) {
    if (!*stack) {
        *stack = new_node;
        last_node = new_node;
        return;
    }
    t_node *temp = *stack;
    while (temp->next) temp = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
    last_node = new_node;
}

void free_n_error(t_node **stack) {
    (void)stack;
    printf("Error\n");
    exit(EXIT_FAILURE);
}

long ft_atol(const char *str) {
    long result = 0;
    int sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13)) str++;
    if (*str == '+' || *str == '-') {
        if (*str == '-') sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

int check_dup(t_node *stack, int value) {
    while (stack) {
        if (stack->data == value) return 1;
        stack = stack->next;
    }
    return 0;
}

int error_argvs(char *arg) {
    for (int i = 0; arg[i]; i++) {
        if ((arg[i] < '0' || arg[i] > '9') && arg[i] != '-' && arg[i] != '+')
            return 1;
    }
    return 0;
}

void initial_a(t_node **stack_a, char **argv) {
    long value;
    int i = 0;

    while (argv[i]) {
        if (error_argvs(argv[i])) free_n_error(stack_a);
        value = ft_atol(argv[i]);
        if (value > INT_MAX || value < INT_MIN) free_n_error(stack_a);
        if (check_dup(*stack_a, (int)value)) free_n_error(stack_a);
        t_node *new_node = create_node((int)value);
        if (!new_node) free_n_error(stack_a);
        add_back(stack_a, new_node);
        i++;
    }
}

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
        // printf("Error: Stack B is empty\n");
        return;
    }

    if (!stack_a || !*stack_a)
    {
        // printf("Error: Stack A is empty\n");
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

int find_min_index(t_node *stack) 
{
    int index = 0;
    int min_index = 0;
    long smallest = LONG_MAX;
    t_node *current = stack;

    while (current)
    {
        if (current->data < smallest)
        {
            smallest = current->data;
            min_index = index;
        }
        index++;
        current = current->next;
    }
    return min_index; // Return the index of the smallest element
}


void	sort_three(t_node **stack_a) 
{
	t_node	*biggest; 

	biggest = find_max(*stack_a);
	if (biggest == *stack_a)
		ra(stack_a); //If the 1st node is the biggest rotate to bottom
	else if ((*stack_a)->next == biggest) 
		rra(stack_a); //If the 2nd node is the biggest rerotate bottom to top
	if ((*stack_a)->data > (*stack_a)->next->data) 
		sa(stack_a); //If the bottom node is the biggest, but the top node is higher than the second node, swap 
}

void sort_five(t_node **stack_a, t_node **stack_b)
{
    // Step 1: Push the two smallest elements to stack_b
    int min_index;

    while (count_nodes(*stack_a) > 3) // Loop until only 3 elements are left in stack_a
    {
        min_index = find_min_index(*stack_a); // Find index of the smallest element
        
        if (min_index == 0)
            pb(stack_a, stack_b); // Push the smallest element to stack_b
        else if (min_index <= count_nodes(*stack_a) / 2)
            ra(stack_a); // Rotate until the smallest is at the top
        else
            rra(stack_a); // Reverse rotate until the smallest is at the top
    }

    // Step 2: Sort the remaining three elements in stack_a
    sort_three(stack_a); // Sort the three elements left in stack_a (using your sort_three function)

    // Step 3: Push back the two smallest elements from stack_b to stack_a
    pa(stack_a, stack_b); // Push the smaller element back
    pa(stack_a, stack_b); // Push the other element back

    // Final step: If needed, sort stack_a again
    if ((*stack_a)->data > (*stack_a)->next->data)
        sa(stack_a); // Swap the first two elements if they are out of order
}

void print_list(t_node *stack) {
    t_node *current = stack;
    if (!stack) {
        printf("List is empty\n");
        return;
    }
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
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

t_node *find_last_node(t_node *stack)
{
    if (!stack)
        return NULL;
    while (stack->next != NULL)
        stack = stack->next;
    return stack;
}

t_node *find_second_last_node(t_node *stack)
{
    if (!stack || !stack->next)
        return NULL;
    while (stack->next->next != NULL)
        stack = stack->next;
    return stack;
}

void sort_group1(t_node **stack_a, t_node **stack_b) {
    int pushed_count = 0;
    int total_pushed = 0;

    t_node *current = *stack_a;
    while (current) {
        if (current->data >= 21 && current->data <= 40) {
            total_pushed++;
        }
        current = current->next;
    }
    while (*stack_a && pushed_count < total_pushed)
    {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);

        if (current->data >= 21 && current->data <= 40)
        {
            pb(stack_a, stack_b);
            pushed_count++;
        }
        if (last_node->data >= 21 && last_node->data <= 40)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 21 && second_last_node->data <= 40)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else
        {
            ra(stack_a);
        }
    }
}

void sort_group2(t_node **stack_a, t_node **stack_b) {
    int pushed_count = 0;
    int total_pushed = 0;

    t_node *current = *stack_a;
    while (current)
    {
        if ((current->data >= 1 && current->data <= 20) \
        || (current->data >= 41 && current->data <= 60)) {
            total_pushed++;
        }
        current = current->next;
    }
    while (*stack_a && pushed_count < total_pushed) {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);

        if (current->data >= 1 && current->data <= 20)
        {
            pb(stack_a, stack_b);
            rb(stack_b);
            pushed_count++;
        }
        if (last_node->data >= 1 && last_node->data <= 20)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 1 && second_last_node->data <= 20)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (current->data >= 41 && current->data <= 60)
        {
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (last_node->data >= 41 && last_node->data <= 60)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 41 && second_last_node->data <= 60)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else {
            ra(stack_a);
        }
    }
}

void sort_group3(t_node **stack_a, t_node **stack_b) {
    int pushed_count = 0;
    int total_pushed = 0;

    t_node *current = *stack_a;
    while (current) {
        if (current->data >= 61 && current->data <= 80) {
            total_pushed++;
        }
        current = current->next;
    }
    while (*stack_a && pushed_count < total_pushed) {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);

        if (current->data >= 61 && current->data <= 80) {
            pb(stack_a, stack_b);
            pushed_count++;
        }
        if (last_node->data >= 61 && last_node->data <= 80)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 61 && second_last_node->data <= 80)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else {
            ra(stack_a);
        }
    }
}

void process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
    int total_nodes = count_nodes(*stack_a); // Count total nodes in stack_a
    int nodes_processed = 0;

    while (nodes_processed < total_nodes)
    {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);
        if (current->data < median_value)
        {
            pb(stack_a, stack_b); // Move node to stack B
            // printf("Initial Stack A: ");
            // print_list(*stack_a);
            // printf("\nInitial Stack B: ");
            // print_list(*stack_b);
        }
        if (last_node->data < median_value)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            // printf("Initial Stack A: ");
            // print_list(*stack_a);
            // printf("\nInitial Stack B: ");
            // print_list(*stack_b);
        }
        else if (second_last_node->data < median_value)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b); // Move node to stack B
            // printf("Initial Stack A: ");
            // print_list(*stack_a);
            // printf("\nInitial Stack B: ");
            // print_list(*stack_b);
        }
        else
        {
            ra(stack_a); // Rotate from the top node
        }
        nodes_processed++; // Increment the nodes_processed variable
    }
}

void process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
    t_node *temp_stack;
    t_median median;

    while (count_nodes(*stack_a) > 1)
    {
        if (count_nodes(*stack_a) <= 5)
        {
            sort_five(stack_a, stack_b);
            break;
        }

        temp_stack = copy_list(*stack_a);
        if (!temp_stack)
        {
            printf("Memory allocation failed\n");
            return;
        }

        temp_stack = sort_list(temp_stack);

        // printf("Initial Stack A: ");
        // print_list(*stack_a);

        // Print the temporary sorted list
        // print_list_with_label(temp_stack, "Temporary Sorted List");

        median = find_median(temp_stack);

        // printf("New Median value: %d\n", median.value);

        process_nodes(stack_a, stack_b, median.value);

        // print_list_with_label(*stack_a, "Stack A after processing new median");
        // print_list_with_label(*stack_b, "Stack B");

        if (temp_stack)
            free_list(temp_stack);
    }
}

void find_and_push_biggest(t_node **stack_a, t_node **stack_b)
{
    while (*stack_b)
    {
        t_node *max_node = find_max(*stack_b);
        t_node *current = *stack_b;
        t_node *last_node = find_last_node(*stack_b);
        t_node *second_last_node = find_second_last_node(*stack_b);

        if (current == max_node)
        {
            pa(stack_a, stack_b); // Push the biggest number to stack A
        }
        else if (last_node == max_node)
        {
            rrb(stack_b); // Rotate the stack to move the last node to the top
            pa(stack_a, stack_b); // Push the biggest number to stack A
        }
        else if (second_last_node == max_node)
        {
            rrb(stack_b); // Rotate the stack to move the second last node to the top
            rrb(stack_b); // Rotate the stack again to move the second last node to the top
            pa(stack_a, stack_b); // Push the biggest number to stack A
        }
        else
        {
            rb(stack_b); // Rotate the stack from the top node
        }
    }
}

int main(int argc, char **argv) {
    t_node *stack_a = NULL;
    t_node *stack_b = NULL;

    if (argc == 1 || (argc == 2 && !argv[1][0])) return 1;
    else if (argc == 2) argv = ft_split(argv[1], ' ');

    initial_a(&stack_a, &argv[1]);

    printf("Initial Stack A: ");
    print_list(stack_a);

    sort_group1(&stack_a, &stack_b);
    // printf("Final Stack A: ");
    // print_list(stack_a);
    // printf("\nFinal Stack B: ");
    // print_list(stack_b);
    sort_group2(&stack_a, &stack_b);
    // printf("Final Stack A: ");
    // print_list(stack_a);
    // printf("\nFinal Stack B: ");
    // print_list(stack_b);
    sort_group3(&stack_a, &stack_b);
    process_nodes_with_new_median(&stack_a, &stack_b);
    find_and_push_biggest(&stack_a, &stack_b);

    // printf("Final Stack A: ");
    // print_list(stack_a);
    // printf("Final Stack B: ");
    // print_list(stack_b);

    // Free the lists
    free_list(stack_a);
    free_list(stack_b);

    return EXIT_SUCCESS;
}

