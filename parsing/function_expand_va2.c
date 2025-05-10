#include "../minishell.h"

int ft_strlen(int a,char *dap)
{
	int	t;
	int	len;

	len = 0;
	t = 0;
	while (t < a)
	{
		if (dap[t] == '\"')
			len++;
		t++;
	}
	return (len);
}
void	copy_to_dap(char *dap, char *str, int *a)
{
	int	i;
	int	m;

	i = 0;
	m = ft_strlen(*a, dap);
	while (str[i])
	{
		if (m % 2 == 0)
		{
			while (str[i] == ' ')
				i++;
			if (str[i] != ' ')
			{
				if (str[i - 1] == ' ')
					dap[(*a)++] = str[i - 1];
				dap[(*a)++] = str[i++];
			}
			if (str[i] == '\"')
				m++;
		}
		else
			dap[(*a)++] = str[i++];
	}
}

void	len_env_value_without_space(char *str, int *a)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ' && str[i])
	{
		i++;
		(*a)++;
	}
}

void	len_env_value(char *str, int *a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		(*a)++;
	}
}
char	*env_key(int *i, char *str)
{
	int		a;
	int		j;
	int		len_key;
	char	*src;

	len_key = 0;
	a = *i;
	j = 0;
	while (ft_Check_after_dollar(str[a]))
	{
		len_key++;
		if (str[a - 1] == '$' && ((str[a] >= 48 && str[a] <= 57)
				|| str[a] == '?'))
			break ;
		a++;
	}
	src = malloc(sizeof(char) * (len_key + 1));
	if (!src)
		return (NULL);
	while (ft_Check_after_dollar(str[*i]))
	{
		src[j++] = str[(*i)++];
		if(((str[*i - 1] >= 48 && str[*i - 1] <= 57)
			|| str[*i - 1] == '?') && str[*i - 2] == '$')
			break ;
	}
	src[j] = '\0';
	return (src);
}

void	numstr_expand_without_quote(t_node *lst, t_env *my_env, int *i, int *a)
{
	int		b;
	char	*src;

	(*i)++;
	if (ft_Check_after_dollar(lst->data[*i]))
		src = env_key(i, lst->data);
	while (my_env)
	{
		b = 0;
		while (my_env->key[b])
		{
			if (my_env->key[b] != src[b])
				break ;
			b++;
		}
		if (my_env->key[b] || src[b])
			my_env = my_env->next;
		else
		{
			len_env_value_without_space(my_env->value, a);
			break ;
		}
	}
	if (src[0] == '?')
		*a = *a + ft_strlen_num_err();
	free(src);
}

void	numstr_expand_with_quote(t_node *lst, t_env *my_env, int *i, int *a)
{
	int		b;
	char	*src;

	(*i)++;
	if (ft_Check_after_dollar(lst->data[*i]))
		src = env_key(i, lst->data);
	while (my_env)
	{
		b = 0;
		while (my_env->key[b])
		{
			if (my_env->key[b] != src[b])
				break ;
			b++;
		}
		if (my_env->key[b] || src[b])
			my_env = my_env->next;
		else
		{
			len_env_value(my_env->value, a);
			break ;
		}
	}
	if (src[0] == '?')
		*a = *a + ft_strlen_num_err();
	free(src);
}
