/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:32:53 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/18 11:43:47 by mradouan         ###   ########.fr       */
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
	char *cwd = getcwd(NULL, 0);
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
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
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
				return (perror("malloc "), 1);
			return (0);
		}
		head = head->next;
	}
	return (0);
}

void	handel_cd(char *cwd, char *abs_path, t_env **env)
{
	printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
	cwd = md_strjoin(cwd, "/");
	cwd = md_strjoin(cwd, abs_path);
	set_env(env, "PWD", abs_path);
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
	// if (set_env(env, "OLDPWD", oldpwd) == 1)
	// 	return (free(oldpwd), 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		handel_cd(cwd, abs_path, env);
		// if (set_env(env, "PWD", abs_path) == 1)
        // 	return (free(oldpwd), 1);
	}
	else
	{
    	if (set_env(env, "PWD", cwd) == 1)
        	return (free(oldpwd), 1);
	}
	// if (set_env(env, "PWD", cwd) == 1)
	// 	return (free(oldpwd), 1);
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
	if (set_env(env, "PWD", cwd) == 1)
		return (free(cwd), free(oldpwd), 1);
	free(cwd);
	free(oldpwd);
	return (0);
}

void	set_oldpwd(t_env *env, char *oldpwd)
{
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD"))
		{
			if (env->value)
				oldpwd = md_strdup(env->value);
			break ;
		}
		env = env->next;
	}
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
		set_oldpwd(*env, oldpwd);
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
