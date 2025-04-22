/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:09:05 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/22 16:59:44 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	md_free(int **num)
{
	int i;

	i = 0;
	while (num[i])
		free(num[i++]);
	free(num);
}

// void print_node(t_env *my_env)
// {
// 	while (my_env)
// 	{
// 		printf("%s = %s\n", my_env->key, my_env->value);
// 		my_env = my_env->next;
// 	}
// }
// void print_node2(t_list *my_env)
// {
// 	while (my_env)
// 	{
// 		printf("%s -> [%d]\n", my_env->data, my_env->type);
// 		my_env = my_env->next;
// 	}
// }

// ______________________________________________________

// char	**create_full_cmd(t_list *nodes)
// {
// 	char *tmp;
// 	char **full_cmd;

// 	full_cmd = NULL;
// 	tmp = NULL;
// 	while (nodes)
// 	{
// 		if (nodes->type == 5)
// 			break ;
// 		if (nodes->type == 1 || nodes->type == 2 || nodes->type == 3 || nodes->type == 4)
// 		{
//             nodes = nodes->next;
//             continue ; 
//         }
// 		tmp = md_strjoin(tmp, nodes->data);
// 		tmp = md_strjoin(tmp, " ");
// 		nodes = nodes->next;
// 	}
// 	full_cmd = md_split(tmp, ' ');
// 	free(tmp);
// 	return (full_cmd);
// }