/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:51:37 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/14 11:08:54 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fetch_home(t_env **env)
{
	char	*home;
	t_env	*head;

	head = *env;
	home = NULL;
	while (head)
	{
		if (ft_strcmp(head->key, "HOME") == 0)
		{
			home = head->value;
			break ;
		}
		head = head->next;
	}
	return (home);
}

int	set_env(t_env **env, char *pwd_searched, char *pwd_updated)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->key, pwd_searched) == 0)
		{
			head->value = md_strdup(pwd_updated);
			return (0);
		}
		head = head->next;
	}
	return (0);
}

char	*set_oldpwd(t_env *env, t_cd *cd)
{
	cd->oldpwd = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			if (env->value)
				cd->oldpwd = md_strdup(env->value);
			return (cd->oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}
