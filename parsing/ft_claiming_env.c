/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_claiming_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:12:48 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/16 11:41:34 by ylagzoul         ###   ########.fr       */
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

void	claiming_env_helper(t_env **my_env)
{
	ft_lstadd_back12(my_env, ft_lstnewt("OLDPWD",
			"/home/mradouan/Desktop/minishell"));
	ft_lstadd_back12(my_env, ft_lstnewt("PWD",
			"/home/mradouan/Desktop/minishell"));
	ft_lstadd_back12(my_env, ft_lstnewt("PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"));
	ft_lstadd_back12(my_env, ft_lstnewt("_", "./minishell"));
}

int	check_env(char *env_p)
{
	if (!ft_strncmp(env_p, "PWD=", 4)
		|| !ft_strncmp(env_p, "OLDPWD", 6)
		|| !ft_strncmp(env_p, "PATH=", 5))
		return (1);
	return (0);
}

void	claiming_env(char **env_p, t_env **my_env, int is_entered)
{
	char	*tmp_key;
	char	*tmp_value;
	int		in_equal;
	int		i;

	i = 0;
	if (!is_entered)
		claiming_env_helper(my_env);
	while (env_p[i])
	{
		if (check_env(env_p[i]) == 1)
		{
			i++;
			continue ;
		}
		in_equal = ft_strlcpy(env_p[i], md_strlen(env_p[i]));
		tmp_key = gc_malloc(((in_equal + 1) * sizeof(char)), 1);
		filling_tmp(tmp_key, env_p[i], in_equal);
		tmp_value = NULL;
		tmp_value = gc_malloc((md_strlen(env_p[i]) - in_equal) + 1, 1);
		if (env_p[i][in_equal] == '=')
			tmp_value = md_strdup(env_p[i] + in_equal + 1);
		ft_lstadd_back12(my_env, ft_lstnewt(tmp_key, tmp_value));
		i++;
	}
}
