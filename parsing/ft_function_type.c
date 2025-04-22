#include "minishell.h"

void ft_lstadd_back1(t_node **lst, t_node *new_node)
{
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    t_node *temp = *lst;
    while (temp->next)
        temp = temp->next;

    temp->next = new_node;
}

t_node *ft_lstnew1(char *content, int type)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->data = strdup(content);
    new_node->type = type;
    new_node->next = NULL;
    return new_node;
}