#include "minishell.h"

void ft_free(t_list **lst)
{
    t_list *temp;
    while(*lst)
    {
         temp = (*lst)->next;
         free((*lst)->content);
         free(*lst);
         *lst = temp;
    }
}

