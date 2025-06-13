/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:50:21 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/13 17:12:06 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_cd(char *cwd, char *abs_path, t_env **env)
{
	char	*temp;
	char	*str_print;

	temp = NULL;
	str_print = NULL;
	str_print = md_strjoin(str_print,
			"cd: error retrieving current directory:");
	str_print = md_strjoin(str_print,
			" getcwd: cannot access parent directories:");
	str_print = md_strjoin(str_print, " No such file or directory\n");
	write(2, str_print, md_strlen(str_print));
	temp = md_strjoin(cwd, "/");
	cwd = md_strjoin(temp, abs_path);
	if (set_env(env, "PWD", cwd) == 1)
		return (1);
	return (0);
}

int	cd_absoulute(char *abs_path, char *oldpwd, t_env **env, t_ha *err)
{
	char	*cwd;

	cwd = NULL;
	if (chdir(abs_path) == -1)
	{
		perror("mhd :");
		err->err_status = 1;
		return (0);
	}
	cwd = getcwd(NULL, 0);
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

int	helper_cd(t_cd *cd, t_env **env, t_ha *err)
{
	cd->home = fetch_home(env);
	if (!cd->home || chdir(cd->home) == -1)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		err->err_status = 1;
		return (0);
	}
	if (set_env(env, "OLDPWD", cd->oldpwd) == 1)
		return (1);
	cd->cwd = getcwd(NULL, 0);
	if (set_env(env, "PWD", cd->cwd) == 1)
		return (1);
	return (0);
}

int	implement_cd(t_env **env, t_node *nodes, t_ha *err)
{
	t_cd	*cd;

	cd = gc_malloc(sizeof(t_cd), 1);
	while (nodes && ft_strcmp(nodes->data, "cd") != 0)
		nodes = nodes->next;
	if (nodes->next && nodes->next->next)
		return (write(2, "cd: too many arguments\n", 24),
			err->err_status = 1, 0);
	cd->oldpwd = getcwd(NULL, 0);
	if (!cd->oldpwd)
		cd->oldpwd = set_oldpwd(*env, cd->oldpwd);
	if (err->no_cd || !nodes->next->data[0])
		return (0);
	else if (!nodes->next || nodes->next->type != 0)
	{
		if (helper_cd(cd, env, err) == 1)
			return (free(cd->oldpwd), 1);
	}
	else if (nodes->next || nodes->next->data)
	{
		if (cd_absoulute(nodes->next->data, cd->oldpwd, env, err) == 1)
			return (free(cd->oldpwd), 1);
	}
	return (0);
}
