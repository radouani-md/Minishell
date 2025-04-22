
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
# include <sys/wait.h>

typedef struct s_list
{
    char            *content;
    int             type;
    // int             eroor;
    struct s_list   *next;
}                   t_list;

typedef struct t_node
{
    char            *data;
    int             type;
    struct t_node   *next;
}                   t_node;

typedef struct t_env
{
	char *key;
	char *value;
	struct t_env *next;
}				t_env;

typedef struct t_handel
{
    int t;
	char *temp;
    int q;
    int quote_count;
    int a;
	struct t_handel *next;
}				t_handel;



int ft_fun(char *input,t_list **lst);
t_node *ft_type_comente_in_out_put(t_list *lst);

void ft_lstadd_back1(t_node **lst, t_node *new_node);
t_node *ft_lstnew1(char *content, int type);

void ft_lstadd_back(t_list **lst, t_list *new_node);
t_list *ft_lstnew(char *content);
int ft_pips(char *input, int *i, t_list **lst);
int ft_handle_double_single(char *input, int *i, t_list **lst);
int ft_handle_string(char *input, int *i, t_list **lst);

t_env	*ft_lstnewt(char *env_key, char *env_value);
void	claiming_env(char **env_p, t_env **my_env);
void	ft_lstadd_back12(t_env **lst, t_env *new);

//ft_fun
int ft_pips(char *input, int *i, t_list **lst);
void ft_free(t_list **lst);
int ft_handle_double_single(char *input, int *i, t_list **lst);
int ft_handle_string(char *input, int *i, t_list **lst);
t_handel *ft_lstnew_handl(int i);
int ft_handle2(char *input,int i,t_handel *handel);
int ft_handle1(char *input,int *i,t_handel *handel);
void ft_handle3(char *input,int *i,t_handel *handel);
void ft_lstadd_back(t_list **lst, t_list *new_node);
t_list *ft_lstnew(char *content);

// ft_eroor
int ft_syntax_erorr(t_list *lst);

//ft_type
t_node *ft_type_comente_in_out_put(t_list *lst);
void ft_lstadd_back1(t_node **lst, t_node *new_node);
t_node *ft_lstnew1(char *content, int type);

//function_expand_va
void ft_expand_variables(t_node *lst, t_env *my_env);
void ft_exp(t_node *lst, t_env *my_env);
int ft_strlen_envd(t_node *lst, t_env *my_env);
void ft_exp2(t_node *lst, t_env *my_env,char *dap,int *i, int *a);
void ft_strlen_$(int *i,char *lst);
void ft_exp55(t_node *lst, t_env *my_env,int *i, int *a);
char *ft_strlen_key(int *i,char *str);
void ft_copy55(char *str, int *a);
void ft_copy(char *dap, char *str, int *a);

// MOHAMMED --> PROTOTYPES (MAT9ARABCH HNA) -----------------------------------------------

// typedef struct s_env
// {
// 	char *key;
// 	char *value;
// 	struct s_env *next;
// }				t_env;

// t_env		*ft_lstnew_m(char *env_key, char *env_value);
// void		ft_lstadd_front(t_env **lst, t_env *new_l);
// int			ft_lstsize(t_env *lst);
// void		ft_lstadd_back_m(t_env **lst, t_env *new);
// void		ft_lstclear(t_env **lst);


size_t	ft_strlcpy(char *src, size_t dstsize);
size_t	md_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*md_strdup(char *src);
char	*md_strjoin(char *s1, char *s2);
char	**md_split(char const *s, char c);

void	md_free(int **num);

char 	**each_group_cmd(t_node *nodes);
t_node	**split_nodes_by_pipe(t_node *nodes, int *num_groups);
char	**loop_through_node(t_node *nodes, char **cmd);
char 	*is_accessable(char **path, char *cmd);
void 	filling_tmp(char *key,char *env, int size);

char **fetch_path(t_env *my_env);

int	piping_forking(char *cmd_path, char **cmd, char **group_cmd, t_node *nodes, t_env *my_env);


/////////////////
t_node	*ft_lstneww(char *lst, int typ_e);
t_node	*ft_lstlastt(t_node *lst);
void	ft_lstadd_back_m(t_env **lst, t_env *new);
void	ft_lstadd_backk(t_node **lst, t_node *new);
void	ft_lstadd_front(t_env **lst, t_env *new);
#endif
