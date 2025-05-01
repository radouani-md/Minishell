#include "../minishell.h"

void ft_strlen_$(int *i,char *lst)
{
	int t;
	t = 0;
	while(lst[*i] == '$')
	{
		(*i)++;
		t++;
	}
	if(t % 2 == 1)
	{
		(*i)--;
	}
}

void ft_exp2(t_node *lst, t_env *my_env,char *dap,int *i, int *a)
{
	int b;
	char *src;

	(*i)++;
	src = ft_strlen_key(i,lst->data);
	while(my_env)
	{
		b = 0;
		while(my_env->key[b])
		{
			if(my_env->key[b] != src[b])
				break;
			b++;
		}
		if(my_env->key[b] || src[b])
			my_env = my_env->next;
		else
		{
			ft_copy(dap, my_env->value, a);
			break ;
		}
	}
	if(ft_strncmp1(src, "?", 1))
		ft_functin_env(dap, a);
	free(src);
}

int ft_strlen_envd(t_node *lst, t_env *my_env)
{
	int a;
	int i;
	int j;
	int m;

	a = 0;
	i = 0;
	j = 0;
	m = 0;

	while(lst->data[i])
	{
		if(lst->data[i] == '\'' && m % 2 == 0)
			j++;
		else if(lst->data[i] == '\"' && j % 2 == 0)
			m++;
		if(ft_Check_dollar(lst, i, j))
				ft_exp55(lst, my_env, &i, &a);
		else
		{
			i++;
			a++;
		}
	}
	return(a);
}


void ft_exp(t_node *lst, t_env *my_env)
{
	char *dap;
	int a;
	int i;
	int y;
	int j;
	int m;

	a = 0;
	i = 0;
	j = 0;
	m = 0;
	dap = malloc(sizeof(char) * (ft_strlen_envd(lst,my_env) + 1));
	while(lst->data[i])
	{
		if(lst->data[i] == '\'' && m % 2 == 0)
			j++;
		else if(lst->data[i] == '\"' && j % 2 == 0)
			m++;
		if(ft_Check_dollar(lst, i, j))
				ft_exp2(lst, my_env,dap, &i, &a);
		else
		{
			if(lst->data[i] == '$' && lst->data[i+1] == '$')
				ft_strlen_$(&i,lst->data);
			else if(lst->data[i] == '$' && (lst->data[i + 1] == '\"' || lst->data[i + 1] == '\''))
			{
				if(lst->data[i+1] == '\'' && m % 2 == 0)
					y = j + 1;
				else if(lst->data[i+1] == '\"' && j % 2 == 0)
					y = m + 1;
				if(y % 2 == 1)
					i++;
				else
					dap[a++] = lst->data[i++];
			}
			else
				dap[a++] = lst->data[i++];
		}
	}
	dap[a] = '\0';
	free(lst->data);
	lst->data = dap;
}
