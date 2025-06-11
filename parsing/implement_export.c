/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:29:50 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/11 21:57:18 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (ft_Check_key(nodes->data[i]))
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

// void ft_youssef(t_node *nodes, t_env	*cpy_env1, int *i)
// {
// 	ft_lstadd_back_env(&cpy_env1, ft_lstnew_env());
// 	while (cpy_env1)
// 	{
// 		if (cpy_env1->next == NULL)
// 		{
// 			printf("youssef is error\n");
// 			cpy_env1->key = ft_cpy_key(*i, nodes);
// 			printf("youssef is error111?\n");
// 			cpy_env1->value = ft_cpy_value(i, nodes, cpy_env1);
// 		}
// 		cpy_env1 = cpy_env1->next;
// 	}
// }

void	add_value_export(t_env *my_env, t_node *nodes)
{
	t_env	*cpy_env;
	t_env	*cpy_env1;
	char *str;
	char *str1;
	int		i;

	nodes = nodes->next;
	while (nodes)
	{
		i = 0;
		cpy_env = my_env;
		cpy_env1 = my_env;
		while (cpy_env)
		{
			if (!ft_strcmp(cpy_env->key, ft_cpy_key(i, nodes)))
			{
				str1 = ft_cpy_value(&i, nodes, cpy_env);
				if(str1 != NULL)
					cpy_env->value = str1;
				else
					cpy_env->type = 1;
				break ;
			}
			cpy_env = cpy_env->next;
		}
		if (cpy_env == NULL)
		{
			// ft_youssef(nodes, cpy_env1, &i);
			str = ft_cpy_key(i, nodes);
			if(str != NULL)
			{
				ft_lstadd_back_env(&cpy_env1, ft_lstnew_env());
				while (cpy_env1)
				{
					if (!cpy_env1->next)
					{
						cpy_env1->key = ft_cpy_key(i, nodes);
						cpy_env1->value = ft_cpy_value(&i, nodes, cpy_env1);
					}
					cpy_env1 = cpy_env1->next;
				}
			}
			else
				write(2, "not a valid identifier\n", 23);
		}
		nodes = nodes->next;
	}
}

int	implement_export(t_env *my_env, t_node *nodes)
{
	char	*str_print;
	if (nodes->next == NULL || (nodes->next && nodes->next->type != 0))
	{
		while (my_env)
		{
			str_print = NULL;
			if (my_env->key)
			{
				str_print = md_strjoin(str_print, "declare -x ");
				str_print = md_strjoin(str_print, my_env->key);
			}
			if (my_env->type == 1)
			{
				str_print = md_strjoin(str_print, "=\"");
				str_print = md_strjoin(str_print, my_env->value);
				str_print = md_strjoin(str_print, "\"\n");
			}
			else
				str_print = md_strjoin(str_print, "\n");
			write(1, str_print, md_strlen(str_print));
			my_env = my_env->next;
		}
	}
	else
		add_value_export(my_env, nodes);
	return (0);
}
