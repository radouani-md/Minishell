/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:29:50 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/26 19:42:13 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_key(int i, t_node *nodes)
{
	int	a;

	a = 0;
	while (ft_Check_key(nodes->data[i]))
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
		(i)++;
	if (nodes->data[i] == '+' && nodes->data[(i) + 1] == '+')
		return (0);
	if (nodes->data[i] == '+' && nodes->data[(i) + 1] == '=')
	{
		i = i + 2;
		a = md_strlen(my_env->value);
		a += yl_strlen(nodes->data, &i);
	}
	else
	{
		(i)++;
		a += yl_strlen(nodes->data, &i);
	}
	return (a);
}

void	add_value_export(t_env *my_env, t_node *nodes)
{
	t_env	*cpy_env;
	t_env	*cpy_env1;
	char *fre;
	int		i;

	nodes = nodes->next;
	while (nodes)
	{
		i = 0;
		cpy_env = my_env;
		cpy_env1 = my_env;
		while (cpy_env)
		{
			fre = ft_cpy_key(i, nodes);
			if (!ft_strcmp(cpy_env->key, fre))
			{
				free(fre);
				fre = cpy_env->value;
				cpy_env->value = ft_cpy_value(&i, nodes, cpy_env);
				free(fre);
				break ;
			}
			cpy_env = cpy_env->next;
		}
		if (cpy_env == NULL)
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
		nodes = nodes->next;
	}
}

int	implement_export(t_env *my_env, t_node *nodes)
{
	if (nodes->next == NULL && !ft_strcmp(nodes->data, "export"))
	{
		while (my_env)
		{
			if(my_env->key)
				printf("declare -x %s", my_env->key);
			if(my_env->type == 1)
				printf("=\"%s\"\n", my_env->value);
			else
				printf("\n");
			my_env = my_env->next;
		}
	}
	else
	{
		add_value_export(my_env, nodes);
	}
	return (1);
}
