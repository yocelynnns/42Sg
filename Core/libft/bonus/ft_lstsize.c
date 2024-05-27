#include "libft.h"

int ft_lstsize(t_list *lst)
{
    t_list *node;
    int count;

    node = lst;
    count = 0;
    while (node != NULL)
    {
        node = node->next;
        count++;
    }
    return (node);
}