/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:47:14 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/27 10:50:16 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void conut_dabel_singel_qoutition(char c, t_ha	*ha)
{
	if (c == '\'' && ha->dablla_qoute % 2 == 0)
		(ha->singl_qoute)++;
	else if (c == '\"' && ha->singl_qoute % 2 == 0)
		(ha->dablla_qoute)++;
}

t_ha	*helper_varia()
{
	t_ha	*new_node;

	new_node = malloc(sizeof(t_ha));
	if (!new_node)
		return (NULL);
	new_node->dest_index = 0;
	new_node->read_index = 0;
	new_node->quote_count = 0;
	new_node->singl_qoute = 0;
	new_node->dablla_qoute = 0;
	new_node->next = NULL;
	return (new_node);
}

t_handel	*helper_variables(int i)
{
	t_handel	*new_node;

	new_node = malloc(sizeof(t_handel));
	if (!new_node)
		return (NULL);
	new_node->t = 0;
	new_node->a = 0;
	new_node->q = 1;
	new_node->quote_count = 1;
	new_node->next = NULL;
	return (new_node);
}

int	ft_Check_key(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else if (c == 95)
		return (1);
	return(0);
}

char	*ft_cpy_key(int i, t_node *nodes)
{
	char	*str;
	int		a;

	a = 0;
	str = malloc(count_key(i, nodes) + 1);
	if(!str)
		return (NULL);
	if(nodes->data[0] >= '0' && nodes->data[0] <= '9')
	{
		printf("eroor ft_cpy_key\n"); //free
		exit(1);
	}
	while (ft_Check_key(nodes->data[i]))
	{
		str[a++] = nodes->data[(i)++];
	}
	str[a] = '\0';
	return (str);
}
char *ft_copy_add_dabel_qoutes(char *str)
{
	char	*copy;
	int		read_index;
	int		dest_index;

	read_index = 0;
	dest_index = 0;
	copy = malloc(md_strlen(str) + 3);
	copy[dest_index++] = '\"';
	while(str[read_index])
	{
		copy[dest_index++] = str[read_index++];
	}
	copy[dest_index++] = '\"';
	copy[dest_index] = '\0';
	free(str);
	return(copy);
}

char *ft_cpy_value(int *i, t_node *nodes, t_env *my_env)
{
	char	*str;

	str = malloc(count_value(*i, nodes, my_env) + 2);
	if(!str)
		return (NULL);
	while(ft_Check_key(nodes->data[*i]))
		(*i)++;
	if(nodes->data[*i] == '+' && nodes->data[(*i) + 1] == '+')
	{
		printf("mhd: export: `%s': not a valid identifier\n", nodes->data);
		return (free(str), NULL);
	}
	if(nodes->data[*i] == '+' && nodes->data[(*i) + 1] == '=')
	{
		*i = *i + 2;
		my_env->type = 1;
		str = md_strjoin(my_env->value, nodes->data + (*i));
		yl_strlen(nodes->data, i);
	}
	else if(nodes->data[*i] == '=')
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
