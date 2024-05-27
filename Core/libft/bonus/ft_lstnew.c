#include "libft.h"

t_list *ft_lstnew(void *content)
{
    t_list  *newnode;

    newnode = (t_list *)malloc(sizeof(t_list));
    newnode->content=content;
    newnode->next=NULL;
    return (newnode);
}