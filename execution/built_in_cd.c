/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:50:21 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/19 16:53:10 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_cd(char *cwd, char *abs_path, t_env **env)
{
	char	*temp;
	char	*new_cwd;

	temp = NULL;
	ft_print_erorr("cd: error retrieving current directory:",
		" getcwd: cannot access parent directories:",
		" No such file or directory", "\n");
	if (!cwd)
		temp = md_strdup("/");
	else
		temp = md_strjoin(cwd, "/");
	new_cwd = md_strjoin(temp, abs_path);
	set_env(env, "PWD", new_cwd);
	return (0);
}

int	cd_absoulute(char *abs_path, char *oldpwd, t_env **env, t_ha *err)
{
	if (chdir(abs_path) == -1)
	{
		perror("mhd :");
		err->err_status = 1;
		return (0);
	}
	set_env(env, "OLDPWD", oldpwd);
	save_cwd(env);
	set_env(env, "PWD", (*env)->cww);
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
	set_env(env, "OLDPWD", (*env)->cww);
	save_cwd(env);
	set_env(env, "PWD", (*env)->cww);
	return (0);
}

char	*safe_getcwd(void)
{
	char	*cwd;
	char	*dup;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	dup = md_strdup(cwd);
	free(cwd);
	return (dup);
}

int	implement_cd(t_env **env, t_node *nodes, t_ha *err)
{
	t_cd	*cd;
	static int entered = 0;

	cd = gc_malloc(sizeof(t_cd), 1);
	while (nodes && ft_strcmp(nodes->data, "cd") != 0)
		nodes = nodes->next;
	if (nodes->next && nodes->next->next)
		return (write(2, "cd: too many arguments\n", 24),
			err->err_status = 1, 0);
	cd->oldpwd = safe_getcwd();
	if (!cd->oldpwd)
		cd->oldpwd = (*env)->cww;
	if (!entered)
	{
		entered = 1;
		ft_lstadd_back12(env, ft_lstnewt("OLDPWD", (*env)->cww));
	}
	if (nodes->next && !nodes->next->data[0])
		return (0);
	else if (!nodes->next || nodes->next->type != 0)
	{
		if (helper_cd(cd, env, err) == 1)
			return (1);
	}
	else if (nodes->next || nodes->next->data)
	{
		if (cd_absoulute(nodes->next->data, cd->oldpwd, env, err) == 1)
			return (1);
	}
	return (0);
}

void	update_pwd(t_env **env)
{
	t_env	*head;
	int		is_her;

	head = *env;
	is_her = 0; 
	while (head)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			is_her = 1;
			break ;
		}
		head = head->next;
	}
	if (!is_her)
		ft_lstadd_back12(env, ft_lstnewt("PWD", (*env)->cww));
}

void    save_cwd(t_env **env)
{
    char    *cwd;
    char    *old;

    cwd = safe_getcwd();
	if (!*env)
        return ;
    old = (*env)->cww;
    if (cwd)
        (*env)->cww = cwd;
    else if (old)
    {
        perror("cd: error retrieving current directory"
            ": getcwd: cannot access parent directories");
        (*env)->cww = md_strjoin(old, "/..");
    }
    else
    {
        printf("getcwd: cannot access parent directories:"
            " No such file or directory\n");
        (*env)->cww = NULL;
    }
	update_pwd(env);
}
