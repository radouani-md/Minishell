/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:37:29 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/14 15:27:38 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}				t_env;

typedef struct s_list
{
	char			*data;
    int				type;
    struct s_list	*next;
}				t_list;

// typedef struct s_cmds {
// 	t_list *cmd;
// 	struct s_cmds *next;
// } t_cmds;

t_env		*ft_lstnew(char *env_key, char *env_value);
void		ft_lstadd_front(t_env **lst, t_env *new_l);
int			ft_lstsize(t_env *lst);
void		ft_lstadd_back(t_env **lst, t_env *new);
void		ft_lstclear(t_env **lst);

t_list	*ft_lstneww(char *lst, int typ_e);
t_list	*ft_lstlastt(t_list *lst);
void	ft_lstadd_backk(t_list **lst, t_list *new);

// void	ft_lstadd_bck(t_cmds **lst, t_cmds *new);
// t_cmds	*ft_lstlas(t_cmds *lst);
// t_cmds	*ft_lstnw(char *command);



size_t	ft_strlcpy(char *src, size_t dstsize);
size_t	md_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*md_strdup(char *src);
char	*md_strjoin(char *s1, char *s2);
char	**md_split(char const *s, char c);


#endif