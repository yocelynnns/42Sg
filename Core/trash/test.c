#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_node {
    int data;
    struct s_node *next;
} t_node;

typedef struct s_median {
    int value;
} t_median;

// Helper functions for stack management
int stack_size(t_node *stack) {
    int size = 0;
    while (stack) {
        size++;
        stack = stack->next;
    }
    return size;
}

t_node *find_last_node(t_node *stack) {
    while (stack && stack->next) {
        stack = stack->next;
    }
    return stack;
}

t_node *find_max(t_node *stack) {
    long biggest = LONG_MIN;
    t_node *max_node = NULL;

    while (stack) {
        if (stack->data > biggest) {
            biggest = stack->data;
            max_node = stack;
        }
        stack = stack->next;
    }
    return max_node;
}

t_median find_median(t_node *sorted_list) {
    int node_count = stack_size(sorted_list);
    int mid_position = node_count / 2; // Use a simple midpoint for median
    t_node *current = sorted_list;

    for (int i = 0; i < mid_position; i++) {
        current = current->next;
    }

    t_median median;
    median.value = current->data;
    return median;
}

t_node *copy_list(t_node *stack) {
    t_node *new_list = NULL;
    t_node *new_node;
    t_node *temp;

    while (stack) {
        new_node = malloc(sizeof(t_node));
        if (!new_node)
            return NULL;
        new_node->data = stack->data;
        new_node->next = NULL;

        if (!new_list) {
            new_list = new_node;
            temp = new_list;
        } else {
            temp->next = new_node;
            temp = temp->next;
        }
        stack = stack->next;
    }
    return new_list;
}

void free_stack(t_node **stack) {
    t_node *temp;

    while (*stack) {
        temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
}

// Rotate cost calculation
int get_rotate_cost(t_node *stack, t_node *target) {
    int index = 0;
    t_node *current = stack;
    
    while (current != target) {
        current = current->next;
        index++;
    }

    int rotate_cost = index; // Forward rotation cost
    int reverse_rotate_cost = stack_size(stack) - index; // Backward rotation cost
    return (rotate_cost <= reverse_rotate_cost) ? rotate_cost : reverse_rotate_cost;
}

void rotate_stack_to_target(t_node **stack, t_node *target) {
    int forward_cost = get_rotate_cost(*stack, target);
    int reverse_cost = stack_size(*stack) - forward_cost;

    if (forward_cost <= reverse_cost) {
        for (int i = 0; i < forward_cost; i++) {
            ra(stack); // Rotate forward
        }
    } else {
        for (int i = 0; i < reverse_cost; i++) {
            rra(stack); // Rotate backward
        }
    }
}

// Push swap operations
void pb(t_node **stack_a, t_node **stack_b) {
    // Push top of A to B
}

void pa(t_node **stack_a, t_node **stack_b) {
    // Push top of B to A
}

void ra(t_node **stack_a) {
    // Rotate stack A forward
}

void rra(t_node **stack_a) {
    // Reverse rotate stack A
}

void rb(t_node **stack_b) {
    // Rotate stack B forward
}

void rrb(t_node **stack_b) {
    // Reverse rotate stack B
}

// Main sorting algorithm
void process_nodes(t_node **stack_a, t_node **stack_b, int median_value) {
    int total_nodes = stack_size(*stack_a);
    int nodes_processed = 0;

    while (nodes_processed < total_nodes) {
        if ((*stack_a)->data < median_value) {
            pb(stack_a, stack_b); // Push to stack B
        } else {
            t_node *last_node = find_last_node(*stack_a);
            rotate_stack_to_target(stack_a, last_node); // Use rotation cost optimization
        }
        nodes_processed++;
    }
}

void find_and_push_biggest(t_node **stack_a, t_node **stack_b) {
    while (*stack_b) {
        t_node *biggest = find_max(*stack_b);
        rotate_stack_to_target(stack_b, biggest); // Rotate stack B to bring biggest to top
        pa(stack_a, stack_b); // Push biggest from B to A
    }
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

void process_nodes_with_new_median(t_node **stack_a, t_node **stack_b) {
    t_node *temp_stack;
    t_median median;

    while (stack_size(*stack_a) > 5) {
        temp_stack = copy_list(*stack_a);
        if (!temp_stack) {
            printf("Memory allocation failed\n");
            return;
        }
        median = find_median(temp_stack);
        process_nodes(stack_a, stack_b, median.value);
        free_stack(&temp_stack);
    }
    // Sort the last 5 or fewer elements directly
    sort_five(stack_a, stack_b);
}

void sort_stacks(t_node **stack_a, t_node **stack_b) {
    process_nodes_with_new_median(stack_a, stack_b);
    find_and_push_biggest(stack_a, stack_b);
}

void sort_five(t_node **stack_a, t_node **stack_b) {
    // Implement the logic for sorting 5 or fewer elements in stack_a
}