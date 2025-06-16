/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:32:53 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/15 18:24:11 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	implement_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char	*get_env_value(t_env *env, char *pwd)
{
	char	*env_v;

	env_v = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, pwd) == 0)
		{
			if (env->value)
				env_v = env->value;
			break ;
		}
		env = env->next;
	}
	return (env_v);
}

int	implement_pwd(t_env *env)
{
	char	*cwd;

	cwd = safe_getcwd();
	if (!cwd)
	{
		cwd = get_env_value(env, "PWD");
		if (cwd)
			printf("%s\n", cwd);
		else
		{
			perror("pwd");
			return (1);
		}
	}
	else
		printf("%s\n", cwd);
	return (0);
}
