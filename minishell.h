/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:15:29 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/13 16:42:58 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <linux/limits.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

extern int	g_sig_md ;

typedef struct t_malloc
{
	char	*data;
	struct	t_malloc	*next;
}					t_malloc;

typedef struct s_list
{
	char	*content;
	int		type;
	struct	s_list	*next;
}                   t_list;

typedef struct t_node
{
	char	*data;
	int		type;
	int		is_quoted;
	char	*tmp_file;
	struct	t_node	*next;
}                   t_node;

typedef struct s_md
{
	int		pip_fd[2];
	int		prev_fd;
	int		i;
	int		is_entred;
	int		num_groups;
	int		is_twice;
	t_node	**groups;
	char	**cmd;
	char	**cmd2;
	char	*cmd_path;
	pid_t	id;
	pid_t	pid;
}				t_md;

typedef struct s_cd
{
	char	*oldpwd;
	char	*home;
	char	*cwd;
}				t_cd;

typedef struct s_var
{
	int		in_var;
	int		out_var;
	int		append_var;
}				t_var;

typedef struct t_env
{
	char	*key;
	char	*value;
	int		type;
	struct	t_env	*next;
}				t_env;

typedef struct t_export
{
	char	*name;
	char	*value;
	struct	t_export	*next;
}					t_export;

typedef struct t_handel
{
	int		t;
	char	*temp;
	int		q;
	int		quote_count;
	int		a;
	int		singl_qoute;
	int		dablla_qoute;
	int		count;
	struct	t_handel	*next;
}				t_handel;

typedef struct t_ha
{
	char	*line;
	int		quote_count;
	int		read_index;
	int		dest_index;
	int		snl_qte;
	int		dbl_qte;
	int		err_status;
	int		no_cd;
	int		fd;
	int		saved_fd;
	int		saved_fd_in;
	int		saved_fd_out;
	struct	t_ha	*next;
}						t_ha;

void	ft_print_erorr(char *str1, char *str2, char *str3, char *str4);
int		count_cmd1(t_node *lst, t_env *my_env, t_ha *err);

void	*gc_malloc(size_t size, int nbr);
int		implement_unset(t_env **my_env, t_node *nodes);
int		ft_ft1(char *input, int *i, t_handel *handel, int *col);
int		handel_qoutation1(char *input, int *i, t_handel *handel, int *col);
void	handle_multiple_quotes1(char *input, int *i, t_handel *handel, int *col);
int		count_handle_str(char *input, int i);
char	*ft_copy_add_dabel_qoutes(char *str);

// parsing
void	read_and_filling_node(char *input, t_list **lst);
void	ft_handle_string(char	*input, int	*i, t_list	**lst);
void	ft_ft(char *input, int *i, t_handel *handel);
void	ft_handle_double_single(char *input, int *i, t_list **lst);
void	ft_handel_pipe_direction(char *input, int *i, t_list **lst);
void	handle_multiple_quotes(char *input, int *i, t_handel *handel);
void	handel_qoutation(char *input, int *i, t_handel *handel);
int		count_string(char *input, int i, t_handel *handel);

int		syntax_erorr(t_list *lst);
int		tchik_pipe(t_list *lst);

t_node	*typed_nodes(t_list *lst);

void	claiming_env(char **env_p, t_env **my_env);
void	filling_tmp(char *key, char *env, int size);

void	expand_variables(t_node *lst, t_env *my_env, t_ha *err);
void	expanding_function(t_node *lst, t_env *my_env, t_ha *err);
void	count_dollare(t_ha	*ha, char *lst);
int		count_cmd(t_node *lst, t_env *my_env, t_ha *err);
void	copy_env_value(t_node *lst, t_env *my_env, char *dap, t_ha *ha);
char	*env_key(t_ha *ha, char *str);
void	copy_to_dap(char *dap, char *str, t_ha *ha, t_node *lst);
void	ft_functin_env(char *dap, t_ha *ha);
void	fill_up_node(char *dap, t_node *lst);
int		ft_count_env(char *dap, int read_index);

void	delete_qoutation(t_node *arg);
int		ft_count_ec(char *arg);

int		implement_export(t_env *my_env, t_node *nodes);
int		count_value(int i, t_node *nodes, t_env *my_env);
void	add_value_export(t_env *my_env, t_node *nodes);
char	*ft_cpy_value(int *i, t_node *nodes, t_env *my_env);

int		count_key(int i, t_node *nodes);

//utils_function
void	len_env_value_without_space(char *str, t_ha *halel);

void	num_expd_qte(t_node *lst, t_env *my_env, t_ha *halel, t_ha *err);
void	num_expd_out_qte(t_node *lst, t_env *my_env, t_ha *halel, t_ha *err);
int		check_dollar(t_node *lst, t_ha *ha);
int		check_after_dollar(char c);
void	len_env_value(char *str, t_ha *halel);
int		ft_strlen_num_err(t_ha *err);

char	*ft_cpy_value(int *i, t_node *nodes, t_env *my_env);
char	*ft_cpy_key(int i, t_node *nodes);
int		check_key(char c);
t_handel	*helper_variables();
t_ha	*helper_varia(int err);
void	conut_dabel_singel_qoutition(char c, t_ha	*ha);

int		ft_strlen(int a, char *dap);
size_t	md_strlen(char *s);
size_t	ft_strlcpy(char *src, size_t dstsize);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new_node);

t_env	*ft_lstnewt(char *env_key, char	*env_value);
void	ft_lstadd_back_env(t_env **lst, t_env *new_node);
t_env	*ft_lstnew_env(void);
size_t	yl_strlen(char *s, int *i);
char	*yl_strcpy(char *dest, const char *src);

t_node	*ft_lstnew1(char *content, int type);
t_node	*ft_lstnew2(char *content, int type, char *tmp_file);
char	*move_node(t_node *nodes);
void	ft_lstadd_back1(t_node **lst, t_node *new_node);
void	ft_lstadd_front(t_node **lst, t_node *new);
t_node	*ft_lstnew5(void);
void	ft_lstadd_back12(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);

char	*random_num(void);
void	alloc_arm(t_var	**arm);
char	*md_itoa(int n);
int		get_length(int n);//static
char	*ft_strcat(char *dest, char *src);
void	md_free(int **num);

char	**md_split(char const *s, char c);
char	**put_in(char **ptr, const char *s, char c, size_t count);
void	ftt_free(char **p, size_t i);
size_t	copystr(char *dest, const char *src, size_t index, char c);
int		count_word(char const *s, char c);

char	*md_strjoin(char *s1, char *s2);
char	*md_strdup(char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp1(const char *s1, const char *s2, size_t n);

void	free_group(t_node *group);
void	md_free_char(char **str);
void	ft_free2(t_env **my_envp);
void	ft_free1(t_node **arg);
void	ft_free(t_list **lst);

// MOHAMMED --> PROTOTYPES (MAT9ARABCH HNA) -----------------------------------------------

int		ft_strcmp(char *s1, char *s2);
long	md_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
char	*md_strtrim(char *s1, char const *set);
void	md_putstr(char *str);

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
int		ft_uns_putnbr(unsigned int n);
int		ft_puthex(unsigned long num, char *base);
int		ft_putpoint(void *ptr);
int		ft_hexanbr(unsigned long ptr, char a);
int		mix_printer(char caracter, va_list args);

char	*get_next_line(int fd);

char	**each_group_cmd(t_node *nodes);
t_node	**split_nodes_by_pipe(t_node *nodes, int *num_groups);
int		loop_through_node_builtin(t_node *nodes, t_env *env, t_ha *err);
// char	**loop_through_node(t_node *nodes, char **cmd);
int		loop_through_node(t_node *nodes, char **cmd, t_env *env, t_ha *err);
char	**helper_loop(char **cmd, t_node *nodes);
char	**loop_through_node_cmd(t_node *nodes);
char	*is_accessable(char **path, char *cmd);
char	**load_env(t_env *my_env);

int		piping_forking(t_node **nodes, t_env **my_env, t_ha *err);
int		child_work(t_md *md, t_env **my_env, t_ha *err, t_node *nodes);
void	parent_work(t_md *md);

int		set_md(t_md **md, t_node *nodes, t_env *my_env, t_ha *err);
void	helper_built(t_md *md, t_ha *err);
int		spliting_nodes_hd(t_md *md, t_node *nodes, t_env *my_env, t_ha *err);

char	**fetch_path(t_env *my_env);

void	catch_signals(t_ha *err, pid_t pid);

void	expanding_function_heredoc(t_node *lst, t_env *my_env, t_ha *err);
int		helper_her(t_node *nodes);
int		implement_her_doc(t_node *nodes, t_env *env, t_ha *err);
int		implement_appending(t_node *nodes, t_ha *err);
int		implement_infile(t_node *nodes, t_ha *err);
int		implement_outfile(t_node *nodes, t_ha *err);

int		is_builtin(char *cmd);
int		exec_builtin(char **cmd, t_env **my_env, t_node **nodes, t_ha *err);
void	implement_env(t_env *env);
int		implement_pwd(t_env *env);

int		implement_cd(t_env **env, t_node *nodes, t_ha *err);
char	*set_oldpwd(t_env *env, char *oldpwd);
int		set_env(t_env **env, char *pwd_searched, char *pwd_updated);
char	*fetch_home(t_env **env);

int		implement_echo(t_env *env, t_node *nodes);
int		implement_exit(t_env *my_env, t_node *nodes, t_ha *err);

#endif