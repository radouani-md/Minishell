#include "../minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*last;

	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_lstadd_back12(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL)
	return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void filling_tmp(char *key,char *env, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
}

size_t	ft_strlcpy(char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
            if (src[i] == '=')
                break ;
			i++;
		}
	}
	return (i);
}

size_t	md_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_env	*ft_lstnewt(char *env_key, char *env_value)
{
	t_env	*ptr;

	ptr = (t_env *) malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->value = env_value;
    ptr->key = env_key;
	ptr->next = NULL;
	return (ptr);
}


void	claiming_env(char **env_p, t_env **my_env)
{
	char	*tmp_key;
	char	*tmp_value;
	int		in_equal;
	int		i;

	i = 0;
	while (env_p[i])
	{
		in_equal = ft_strlcpy(env_p[i], md_strlen(env_p[i]));
		tmp_key = malloc(((in_equal + 1) * sizeof(char)));
		filling_tmp(tmp_key, env_p[i], in_equal);
		tmp_value = NULL;
		tmp_value = malloc(((md_strlen(env_p[i]) - in_equal) * sizeof(char)) + 1);
		if (env_p[i][in_equal] == '=')
			tmp_value = md_strdup(env_p[i] + in_equal + 1);
		ft_lstadd_back12(my_env, ft_lstnewt(tmp_key, tmp_value));
		i++;
	}
}
