#include "../minishell.h"

int	ft_Check_key(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else if (c == 95)
		return (1);
	return (0);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new_node)
{
	t_env	*temp;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*ft_lstnew_env()
{
    t_env	*new_node;

	new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->next = NULL;
    return (new_node);
}

void printf_export(t_env *my_env, t_node *nodes)
{
	while(my_env)
	{
		if(my_env->key)
		{
			printf("declare -x %s",my_env->key);
		}
		if (my_env->value)
		{
			printf("=\"%s\"\n",my_env->value);
		}
		my_env = my_env->next;
	}
}

char	*ft_cpy_key(int i, t_node *nodes)
{
	char	*str;
	int		a;

	a = 0;
	str = malloc(30);
	while (ft_Check_key(nodes->data[i]))
	{
		str[a++] = nodes->data[(i)++];
	}
	str[a++] = '\0';
	return (str);
}

char *ft_cpy_value(int *i, t_node *nodes, t_env *my_env)
{
	char	*str;
	int		a;

	a = 0;
	str = malloc(30);
	while(ft_Check_key(nodes->data[*i]))
		(*i)++;
	if(nodes->data[*i] == '+' && nodes->data[(*i) + 1] == '+')
	{
		printf("mhd: export: `%s': not a valid identifier\n", nodes->data);
		return (NULL);
	}
	if(nodes->data[*i] == '+' && nodes->data[(*i) + 1] == '=')
	{
		*i = *i + 2;
		while(my_env->value[a]) // strjoin
		{
			str[a] = my_env->value[a];
			a++;
		}
		while (nodes->data[*i])
			str[a++] = nodes->data[(*i)++];
	}
	else
	{
		(*i)++;
		while (nodes->data[*i])
			str[a++] = nodes->data[(*i)++];
	}
	str[a] = '\0';
	return (str);
}
void add_value_export(t_env *my_env, t_node *nodes)
{
	t_env *cpy_env;
	int i;
	i = 0;
	nodes = nodes->next;
	while(nodes)
	{
		cpy_env = my_env;
		while(cpy_env)
		{
			if(!ft_strcmp(cpy_env->key, ft_cpy_key(i,nodes)))
			{
				cpy_env->value = ft_cpy_value(&i,nodes,cpy_env); //subster
				break ;
			}
			cpy_env = cpy_env->next;
		}
		if(cpy_env == NULL)
		{
			ft_lstadd_back_env(&my_env, ft_lstnew_env());
			while (my_env)
			{
				if (!my_env->next)
				{
					my_env->key = ft_cpy_key(i,nodes);
					my_env->value = ft_cpy_value(&i,nodes,cpy_env);
				}
				my_env = my_env->next;
			}
		}
		// if(cpy_env == NULL)
		// {
		// 	ft_lstadd_back_env(&cpy_env, ft_lstnew_env());
		// 	cpy_env->key = ft_cpy_key(i,nodes);
		// 	cpy_env->value = ft_cpy_value(&i,nodes,cpy_env);
			
		// 	printf("key= {%s} , value= {%s}\n",cpy_env->key,cpy_env->value);
		// 	// cpy_env = my_env;
		// 	// while(head)
		// 	// {
		// 	// 	head = head->next;
		// 	// }
		// }
		nodes = nodes->next;
	}
}

int implement_export(t_env *my_env, t_node *nodes)
{
	if (nodes->next == NULL && !ft_strcmp(nodes->data, "export"))
	{
		printf_export(my_env, nodes);
	}
	else
	{
		add_value_export(my_env, nodes);
	}
	return (1);
}
