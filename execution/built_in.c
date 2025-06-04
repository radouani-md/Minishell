/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:32:53 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/04 16:51:47 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	implement_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char	*get_env_value(t_env *env, char *pwd)
{
	char	*env_value;

	env_value = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, pwd) == 0)
		{
			if (env->value)
				env_value = env->value;
			break ;
		}
		env = env->next;
	}
	return (env_value);
}

int	implement_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = get_env_value(env, "PWD");
		if (cwd)
			ft_printf("%s\n", cwd);
		else
		{
			perror("pwd");
			return (1);
		}
	}
	else
		ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
