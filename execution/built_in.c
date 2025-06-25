/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:32:53 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/25 18:11:05 by mradouan         ###   ########.fr       */
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
		if (env->cww)
			printf("%s\n", env->cww);
		else
			printf("getcwd: cannot access parent directories:"
				" No such file or directory\n");
	}
	else
		printf("%s\n", cwd);
	return (0);
}
