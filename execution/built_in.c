/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:32:53 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/01 16:03:19 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    implement_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	implement_pwd()
{
	char pwd[PATH_MAX];
	
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

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
	t_env *head;
	head = *env;
	while (head)
	{
		if (ft_strcmp(head->key, pwd_searched) == 0)
		{
			free(head->value);
			head->value = md_strdup(pwd_updated);
			if (!head->value)
				return (1);
			return (0);
		}
		head = head->next;
	}
	return (0);
}

int	cd_absoulute(char *abs_path, char *oldpwd, t_env **env)
{
	char cwd[PATH_MAX];

	if (chdir(abs_path) == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (set_env(env, "OLDPWD", oldpwd) == 1)
		return (1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	if (set_env(env, "PWD", cwd) == 1)
		return (1);
	free(oldpwd);
	return (0);
}

int	helper_cd(char *home, t_env **env, char *oldpwd, char *cwd)
{
	home = fetch_home(env);
	if (!home || chdir(home) == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (set_env(env, "OLDPWD", oldpwd) == 1)
		return (1);
	cwd = getcwd(NULL, 0);
	set_env(env, "PWD", cwd);
	free(cwd);
	free(oldpwd);
	return (0);
}

int	implement_cd(t_env **env, t_node *nodes)
{
	char *oldpwd;
	char *home;
	char *cwd;

	home = NULL;
	cwd = NULL;
	while (nodes && ft_strcmp(nodes->data, "cd") != 0)
		nodes = nodes->next;
    oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (nodes->next && nodes->next->next)
		return (free(oldpwd), write(2, "cd: too many arguments\n", 24), 1);
    if (!nodes->next || !nodes->next->data)
    {
		if (helper_cd(home, env, oldpwd, cwd) == 1)
			return (1);
    }
    else
    {
		if (cd_absoulute(nodes->next->data, oldpwd, env) == 1)
			return (1);
	}
    return (0);
}
