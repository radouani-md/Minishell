/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:24:06 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/22 23:23:57 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	conut_dabel_singel_qoutition(char c, t_ha	*ha)
{
	if (c == '\'' && ha->dbl_qte % 2 == 0)
		(ha->snl_qte)++;
	else if (c == '\"' && ha->snl_qte % 2 == 0)
		(ha->dbl_qte)++;
}

t_node	*ft_lstnew5(void)
{
	t_node	*new_node;

	new_node = gc_malloc(sizeof(t_node), 1);
	new_node->data = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	count_key(int i, t_node *nodes)
{
	int	a;

	a = 0;
	while (nodes->data[i] != '+' && nodes->data[i] != '=' && nodes->data[i])
	{
		a++;
		i++;
	}
	return (a);
}

int	count_value(int i, t_node *nodes, t_env *my_env)
{
	int	a;

	a = 0;
	while (check_key(nodes->data[i]))
		i++;
	if (nodes->data[i] == '+' && nodes->data[i + 1] == '+')
		return (0);
	if (nodes->data[i] == '+' && nodes->data[(i) + 1] == '=')
	{
		i = i + 2;
		a = md_strlen(my_env->value);
		a += yl_strlen(nodes->data, &i);
	}
	else if (nodes->data[i] == '=')
	{
		(i)++;
		a += yl_strlen(nodes->data, &i);
	}
	return (a);
}

int	count_value13(int i, t_node *nodes)
{
	int	a;

	a = 0;
	while (check_key(nodes->data[i]))
		i++;
	if (nodes->data[i] == '+' && nodes->data[i + 1] == '+')
		return (0);
	if (nodes->data[i] == '='
		|| (nodes->data[i] == '+' && nodes->data[i + 1] == '='))
	{
		if (nodes->data[i] == '+' && nodes->data[i + 1] == '=')
			i++;
		i++;
		a += yl_strlen(nodes->data, &i);
	}
	return (a);
}
