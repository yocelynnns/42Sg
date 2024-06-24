#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list  *head;
    t_list  *tempnode;

    head = *lst;
    while (head)
    {
        tempnode = head->next;
        (*del)(head->content);
        free(head);
        head = tempnode;
    }
    *lst = NULL;
}