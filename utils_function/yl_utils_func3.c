/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:24:48 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/22 23:23:16 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else if (c == 95 || c == ' ')
		return (1);
	return (0);
}

int	key_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			i++;
		else if (str[i] >= 65 && str[i] <= 90)
			i++;
		else if (str[i] >= 48 && str[i] <= 57)
			i++;
		else if (str[i] == 95)
			i++;
		else
		{
			return (0);
		}
	}
	return (1);
}

char	*ft_cpy_key(int i, t_node *nodes)
{
	char	*str;
	int		a;

	a = 0;
	str = gc_malloc(count_key(i, nodes) + 1, 1);
	if ((nodes->data[0] >= '0' && nodes->data[0] <= '9')
		|| (nodes->data[0] == '+' || nodes->data[0] == '='))
	{
		return (NULL);
	}
	while (nodes->data[i] != '+' && nodes->data[i] != '=' && nodes->data[i])
	{
		str[a++] = nodes->data[(i)++];
	}
	str[a] = '\0';
	if (!key_check(str))
	{
		return (NULL);
	}
	return (str);
}

char	*ft_cpy_value(int *i, t_node *nodes, t_env *my_env, t_ha *err)
{
	char	*str;

	str = gc_malloc(count_value(*i, nodes, my_env) + 2, 1);
	while (check_key(nodes->data[*i]))
		(*i)++;
	if (nodes->data[*i] == '+' && nodes->data[(*i) + 1] != '=')
		return (err->err_status = 1, ft_print_erorr("bash: export: `",
				nodes->data, "': not a valid identifier\n", NULL), NULL);
	if (nodes->data[*i] == '+' && nodes->data[(*i) + 1] == '=')
	{
		*i = *i + 2;
		my_env->type = 1;
		str = md_strjoin(my_env->value, nodes->data + (*i));
		yl_strlen(nodes->data, i);
	}
	else if (nodes->data[*i] == '=')
	{
		(*i)++;
		my_env->type = 1;
		str = yl_strcpy(str, nodes->data + (*i));
		yl_strlen(nodes->data, i);
	}
	else
		return (my_env->type = 0, NULL);
	return (str);
}

char	*ft_cpy_value13(int *i, t_node *nodes, t_env *my_env, t_ha *err)
{
	char	*str;

	str = gc_malloc(count_value13(*i, nodes) + 2, 1);
	while (check_key(nodes->data[*i]))
		(*i)++;
	if (nodes->data[*i] == '+' && nodes->data[(*i) + 1] != '=')
		return (err->err_status = 1, ft_print_erorr("bash: export: `",
				nodes->data, "': not a valid identifier\n", NULL), NULL);
	if (nodes->data[*i] == '='
		|| (nodes->data[*i] == '+' && nodes->data[(*i) + 1] == '='))
	{
		if (nodes->data[*i] == '+' && nodes->data[*i + 1] == '=')
			(*i)++;
		(*i)++;
		my_env->type = 1;
		str = yl_strcpy(str, nodes->data + (*i));
		yl_strlen(nodes->data, i);
	}
	else
		return (my_env->type = 0, NULL);
	return (str);
}
