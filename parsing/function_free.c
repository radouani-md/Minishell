#include "../minishell.h"

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

void	md_free_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void free_group(t_node *group)
{
    t_node *tmp;

    while (group)
    {
        tmp = group->next;
        if (group->data)
            free(group->data);
        free(group);
        group = tmp;
    }
}