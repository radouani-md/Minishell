/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:37:29 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/13 10:48:19 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}				t_env;

typedef struct t_list
{
	char			*data;
    int				type;
    struct t_list	*next;
}				t_list;

t_env		*ft_lstnew(char *env_key, char *env_value);
void		ft_lstadd_front(t_env **lst, t_env *new_l);
int			ft_lstsize(t_env *lst);
void		ft_lstadd_back(t_env **lst, t_env *new);
void		ft_lstclear(t_env **lst);

t_list	*ft_lstneww(char *lst, int typ_e);
t_list	*ft_lstlastt(t_list *lst);
void	ft_lstadd_backk(t_list **lst, t_list *new);


size_t	ft_strlcpy(char *src, size_t dstsize);
size_t	md_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*md_strdup(char *src);
char	*md_strjoin(char *s1, char *s2);


#endif