/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:50:21 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/04 16:52:06 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_cd(char *cwd, char *abs_path, t_env **env)
{
	char	*temp;

	temp = NULL;
	ft_printf("cd: error retrieving current directory:");
	ft_printf(" getcwd: cannot access parent directories:");
	ft_printf(" No such file or directory\n");
	temp = md_strjoin(cwd, "/");
	cwd = md_strjoin(temp, abs_path);
	if (set_env(env, "PWD", cwd) == 1)
		return (1);
	return (0);
}

int	cd_absoulute(char *abs_path, char *oldpwd, t_env **env)
{
	char	*cwd;

	cwd = NULL;
	if (chdir(abs_path) == -1)
	{
		perror("mhd :");
		return (0);
	}
	cwd = getcwd(cwd, 4096);
	if (cwd == NULL)
	{
		if (handel_cd(oldpwd, abs_path, env) == 1)
			return (1);
	}
	else
	{
		if (set_env(env, "PWD", cwd) == 1)
			return (free(cwd), 1);
	}
	if (set_env(env, "OLDPWD", oldpwd) == 1)
		return (free(cwd), 1);
	free(cwd);
	return (0);
}

int	helper_cd(char *home, t_env **env, char *oldpwd, char *cwd)
{
	home = fetch_home(env);
	if (!home || chdir(home) == -1)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (0);
	}
	if (set_env(env, "OLDPWD", oldpwd) == 1)
		return (1);
	cwd = getcwd(NULL, 0);
	if (set_env(env, "PWD", cwd) == 1)
		return (1);
	return (0);
}

int	implement_cd(t_env **env, t_node *nodes, t_err *err)
{
	char	*oldpwd;
	char	*home;
	char	*cwd;

	home = NULL;
	cwd = NULL;
	while (nodes && ft_strcmp(nodes->data, "cd") != 0)
		nodes = nodes->next;
	if (nodes->next && nodes->next->next)
		return (write(2, "cd: too many arguments\n", 24), err->err_status = 1, 0);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = set_oldpwd(*env, oldpwd);
	if (!nodes->next || !nodes->next->data)
	{
		if (helper_cd(home, env, oldpwd, cwd) == 1)
			return (free(oldpwd), 1);
	}
	else if (nodes->next || nodes->next->data)
	{
		if (cd_absoulute(nodes->next->data, oldpwd, env) == 1)
			return (free(oldpwd), 1);
	}
	free(oldpwd);
	return (0);
}
