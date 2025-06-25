/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:45:50 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/24 13:00:47 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_helper(t_cd *cd, t_env **env)
{
	t_env		*head;
	static int	entered = 0;
	int			not_in;

	not_in = 1;
	head = *env;
	cd->oldpwd = safe_getcwd();
	if (!cd->oldpwd)
		cd->oldpwd = (*env)->cww;
	if (!entered)
	{
		entered = 1;
		ft_lstadd_back12(env, ft_lstnewt("OLDPWD", (*env)->cww));
		return ;
	}
	while (head)
	{
		if (ft_strcmp(head->key, "OLDPWD") == 0)
			not_in = 0;
		head = head->next;
	}
	if (not_in)
		ft_lstadd_back12(env, ft_lstnewt("OLDPWD", (*env)->cww));
}

void	update_pwd(t_env **env, int entred)
{
	t_env	*head;

	entred++;
	head = *env;
	while (head)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
			break ;
		head = head->next;
	}
	if (!head)
		ft_lstadd_back12(env, ft_lstnewt("PWD", (*env)->cww));
}

void	save_cwd(t_env **env)
{
	char		*cwd;
	char		*old;
	static int	entred = 0;

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
	if (!entred)
		update_pwd(env, entred);
}

int	implement_cd_child(t_env **env, t_node *nodes, t_ha *err)
{
	t_cd		*cd;
	int			entered;

	entered = 0;
	cd = gc_malloc(sizeof(t_cd), 1);
	while (nodes && ft_strcmp(nodes->data, "cd") != 0)
		nodes = nodes->next;
	if (nodes->next && nodes->next->next)
		return (write(2, "cd: too many arguments\n", 24),
			err->err_status = 1, 1);
	cd_helper(cd, env);
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
	update_pwd(env, entered);
	return (0);
}

void	alloc_arm(t_var	**arm)
{
	*arm = gc_malloc(sizeof(t_var), 1);
	(*arm)->in_var = 0;
	(*arm)->out_var = 0;
	(*arm)->append_var = 0;
}
