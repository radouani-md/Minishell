/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:26:39 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/25 18:11:36 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_close(void)
{
	int	i;

	i = 4;
	while (i < OPEN_MAX)
	{
		close(i);
		i++;
	}
}

char	**fetch_path(t_env *my_env)
{
	char	*path_value;
	char	**paths;

	while (my_env)
	{
		if (ft_strncmp(my_env->key, "PATH", 4) == 0)
		{
			path_value = my_env->value;
			paths = md_split(path_value, ':');
			return (paths);
		}
		my_env = my_env->next;
	}
	return (NULL);
}
