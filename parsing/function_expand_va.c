#include "../minishell.h"

void count_dollare(int *i,char *lst)
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

void copy_env_value(t_node *lst, t_env *my_env,char *dap,int *i, int *a)
{
	int b;
	char *src;

	(*i)++;
	src = env_key(i,lst->data);
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
			copy_to_dap(dap, my_env->value, a);
			break ;
		}
	}
	if(ft_strncmp1(src, "?", 1))
		ft_functin_env(dap, a);
	// free(src);
}

int count_cmd(t_node *lst, t_env *my_env)
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
		{
			if(m % 2 == 1)
				numstr_expand_with_quote(lst, my_env, &i, &a);
			else
				numstr_expand_without_quote(lst, my_env, &i, &a);
		}
		else
		{
			i++;
			a++;
		}
	}
	return(a);
}
void fill_up_node(char *dap,t_node *lst)
{
	int i = 0;
	int n = 0;
	int m = 0;
	int a = 0;
	char *tmp;
	t_node *lst1;
	tmp = malloc(100);
	while(dap[i])
	{
		if(dap[i] == '\"' && n % 2 == 0)
			m++;
		if(dap[i] == '\'' && m % 2 == 0)
			n++;
		if((m % 2 == 1 || n % 2 == 1) || (dap[i] != ' ' && dap[i]))
			tmp[a++] = dap[i++];
		if (m % 2 == 0 && n % 2 == 0 && (dap[i] == ' ' || dap[i] == '\0'))
		{
			tmp[a] = '\0';
			lst->data = strdup(tmp);
			lst->type = 0;
			if(dap[i] == ' ')
				i++;
			if (dap[i])
			{
				lst1 = lst->next;
				lst->next = ft_lstnew5();
				lst->next->next = lst1;
				lst = lst->next;
				free(tmp);
				tmp = malloc(100);
				a = 0;
			}
		}
	}
}


void expanding_function(t_node *lst, t_env *my_env)
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
	dap = malloc(sizeof(char) * (count_cmd(lst,my_env) + 1));
	while(lst->data[i])
	{
		if(lst->data[i] == '\'' && m % 2 == 0)
			j++;
		else if(lst->data[i] == '\"' && j % 2 == 0)
			m++;
		if(ft_Check_dollar(lst, i, j))
				copy_env_value(lst, my_env,dap, &i, &a);
		else
		{
			if(lst->data[i] == '$' && lst->data[i+1] == '$')
				count_dollare(&i,lst->data);
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
	fill_up_node(dap, lst);
	free(dap);
}

t_node *ft_lstnew5()
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return(NULL);
    new_node->next = NULL;
    return new_node;
}

