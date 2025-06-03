/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:47:14 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/03 12:21:38 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	conut_dabel_singel_qoutition(char c, t_ha	*ha)
{
	if (c == '\'' && ha->dablla_qoute % 2 == 0)
		(ha->singl_qoute)++;
	else if (c == '\"' && ha->singl_qoute % 2 == 0)
		(ha->dablla_qoute)++;
}

t_ha	*helper_varia(void)
{
	t_ha	*new_node;

	new_node = gc_malloc(sizeof(t_ha), 1);
	new_node->dest_index = 0;
	new_node->read_index = 0;
	new_node->quote_count = 0;
	new_node->singl_qoute = 0;
	new_node->dablla_qoute = 0;
	new_node->next = NULL;
	return (new_node);
}

t_handel	*helper_variables(void)
{
	t_handel	*new_node;

	new_node = gc_malloc(sizeof(t_handel), 1);
	new_node->t = 0;
	new_node->a = 0;
	new_node->q = 1;
	new_node->quote_count = 1;
	new_node->next = NULL;
	return (new_node);
}

int ft_Check_key(char c)
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
			return (0);
	}
	return (1);
}

char	*ft_cpy_key(int i, t_node *nodes)
{
	char	*str;
	int		a;

	a = 0;
	str = gc_malloc(count_key(i, nodes) + 1, 1);//count_key(i, nodes) + 1
	if(nodes->data[0] >= '0' && nodes->data[0] <= '9')
	{
		printf("eroor ft_cpy_key\n");
		gc_malloc(0, 0);
		exit(1);
	}
	while (nodes->data[i] != '+' && nodes->data[i] != '=' && nodes->data[i]) //ft_Check_key(nodes->data[i])
	{
		str[a++] = nodes->data[(i)++];
	}
	str[a] = '\0';
	if (!key_check(str))
	{
		printf("export: `%s': not a valid identifier\n", nodes->data);
		gc_malloc(0, 0);
		exit(1);
	}
	return (str);
}

char	*ft_copy_add_dabel_qoutes(char *str)
{
	char	*copy;
	int		read_index;
	int		dest_index;

	read_index = 0;
	dest_index = 0;
	copy = gc_malloc(md_strlen(str) + 3, 1);
	copy[dest_index++] = '\"';
	while (str[read_index])
	{
		copy[dest_index++] = str[read_index++];
	}
	copy[dest_index++] = '\"';
	copy[dest_index] = '\0';
	return (copy);
}

char	*ft_cpy_value(int *i, t_node *nodes, t_env *my_env)
{
	char	*str;

	str = gc_malloc(count_value(*i, nodes, my_env) + 2, 1);
	while (ft_Check_key(nodes->data[*i]))
		(*i)++;
	if (nodes->data[*i] == '+' && nodes->data[(*i) + 1] != '=')
	{
		printf("mhd: export: `%s': not a valid identifier\n", nodes->data);
		return (NULL);
	}
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
		my_env->type = 0;
	return (str);
}
