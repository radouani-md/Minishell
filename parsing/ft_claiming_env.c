/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_claiming_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:12:48 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/17 12:36:00 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	filling_tmp(char *key, char *env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
}

void	claiming_env(char **env_p, t_env **my_env)
{
	char	*tmp_key;
	char	*tmp_value;
	int		in_equal;
	int		i;

	i = 0;
	while (env_p[i])
	{
		in_equal = ft_strlcpy(env_p[i], md_strlen(env_p[i]));
		tmp_key = malloc(((in_equal + 1) * sizeof(char)));
		filling_tmp(tmp_key, env_p[i], in_equal);
		tmp_value = NULL;
		tmp_value = malloc((md_strlen(env_p[i]) - in_equal) + 1);
		if (env_p[i][in_equal] == '=')
			tmp_value = md_strdup(env_p[i] + in_equal + 1);
		ft_lstadd_back12(my_env, ft_lstnewt(tmp_key, tmp_value));
		i++;
	}
}