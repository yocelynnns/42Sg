/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:49:37 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/01 17:27:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main()
{
    t_node* stack_a = NULL;
    t_node* stack_b = NULL;

    // Push to stack A
    push(&stack_a, 3);
    push(&stack_a, 2);
    push(&stack_a, 1);

    // Push elements onto stack B
    push(&stack_b, 6);
    push(&stack_b, 5);
    push(&stack_b, 4);

    printf("Original stack A:\n");
    printList(stack_a);
    printf("Original stack B:\n");
    printList(stack_b);

    // Swap the first two elements of stack A
    sa(&stack_a);
    printf("\nStack A after sa:\n");
    printList(stack_a);

    // Swap the first two elements of stack B
    sb(&stack_b);
    printf("\nStack B after sb:\n");
    printList(stack_b);

    // Swap the first two elements of both stacks A and B
    ss(&stack_a, &stack_b);
    printf("\nStack A after ss:\n");
    printList(stack_a);
    printf("Stack B after ss:\n");
    printList(stack_b);

    // Push the top element of stack B to stack A
    pa(&stack_a, &stack_b);
    printf("\nStack A after pa:\n");
    printList(stack_a);
    printf("Stack B after pa:\n");
    printList(stack_b);

    // Push the top element of stack A to stack B
    pb(&stack_a, &stack_b);
    printf("\nStack A after pb:\n");
    printList(stack_a);
    printf("Stack B after pb:\n");
    printList(stack_b);

    // Rotate stack A
    ra(&stack_a);
    printf("\nStack A after ra:\n");
    printList(stack_a);

    // Rotate stack B
    rb(&stack_b);
    printf("\nStack B after rb:\n");
    printList(stack_b);

    // Rotate both stacks A and B
    rr(&stack_a, &stack_b);
    printf("\nStack A after rr:\n");
    printList(stack_a);
    printf("Stack B after rr:\n");
    printList(stack_b);

    // Reverse rotate stack A
    rra(&stack_a);
    printf("\nStack A after rra:\n");
    printList(stack_a);

    // Reverse rotate stack B
    rrb(&stack_b);
    printf("\nStack B after rrb:\n");
    printList(stack_b);

    // Reverse rotate both stacks A and B
    rrr(&stack_a, &stack_b);
    printf("\nStack A after rrr:\n");
    printList(stack_a);
    printf("Stack B after rrr:\n");
    printList(stack_b);

    return (0);
}