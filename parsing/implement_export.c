/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:29:50 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/14 22:56:31 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_youssef(t_node *nodes, t_env *cpy_env1, int *i)
{
	char	*str;

	str = ft_cpy_key(*i, nodes);
	if (str != NULL)
	{
		ft_lstadd_back_env(&cpy_env1, ft_lstnew_env());
		while (cpy_env1)
		{
			if (!cpy_env1->next)
			{
				cpy_env1->key = str;
				cpy_env1->value = ft_cpy_value(i, nodes, cpy_env1);
			}
			cpy_env1 = cpy_env1->next;
		}
	}
	else
		ft_print_erorr("bash: export: `", nodes->data,
			"': not a valid identifier\n", NULL);
}

void	lagzouli(t_env *cpy_env, t_node *nodes, int *i)
{
	char	*str1;
	int		type;

	type = cpy_env->type;
	str1 = ft_cpy_value(i, nodes, cpy_env);
	if (str1 != NULL)
		cpy_env->value = str1;
	else if (type == 1)
		cpy_env->type = 1;
}

void	add_value_export(t_env *my_env, t_node *nodes)
{
	t_env	*cpy_env;
	t_env	*cpy_env1;
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
				lagzouli(cpy_env, nodes, &i);
				break ;
			}
			cpy_env = cpy_env->next;
		}
		if (cpy_env == NULL)
			ft_youssef(nodes, cpy_env1, &i);
		nodes = nodes->next;
	}
}

char	*ft_str_join_err(char *str1, char *str2, char *str3, char	*str_print)
{
	str_print = md_strjoin(str_print, str1);
	str_print = md_strjoin(str_print, str2);
	str_print = md_strjoin(str_print, str3);
	return (str_print);
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
				str_print = ft_str_join_err("=\"",
						my_env->value, "\"\n", str_print);
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
