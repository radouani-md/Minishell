#include "../minishell.h"

char	*env_key1(t_ha *ha, char *str,int *m)
{
	int		cpy_index;
	int		dest_index;
	int		len_key;
	char	*src;

	len_key = 0;
	cpy_index = ha->read_index;
	dest_index = 0;
	while (ft_Check_after_dollar(str[cpy_index]))
	{
		len_key++;
		if (str[cpy_index - 1] == '$' && ((str[cpy_index] >= 48 && str[cpy_index] <= 57)
				|| str[cpy_index] == '?'))
			break ;
		cpy_index++;
	}
	src = malloc(sizeof(char) * (len_key + 1));
	if (!src)
		return (NULL);
	while (ft_Check_after_dollar(str[ha->read_index]))
	{
		src[dest_index++] = str[(ha->read_index)++];
		(*m)++;
		if(((str[ha->read_index - 1] >= 48 && str[ha->read_index - 1] <= 57)
			|| str[ha->read_index - 1] == '?') && str[ha->read_index - 2] == '$')
			break ;
	}
	src[dest_index] = '\0';
	return (src);
}

void	count_dollare1(t_ha	*ha, char *lst, int *m)
{
	int	t;

	t = 0;
	while (lst[ha->read_index] == '$')
	{
		(ha->read_index)++;
        m++;
		t++;
	}
	if (t % 2 == 1)
	{
        m--;
		(ha->read_index)--;
	}
}

void	copy_env_value1(t_node *lst, t_env *my_env, t_ha *ha, int *m)
{
	int		b;
	char	*src;
    int i;

	(ha->read_index)++;
	src = env_key1(ha, lst->data, m);
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
            i = 0;
            while(my_env->value[i])
            {
                i++;
                (*m)++;
            }
			break ;
		}
	}
	// if (ft_strncmp1(src, "?", 1))
	// 	ft_functin_env(dap, ha);
	free(src);
}


int	count_cmd1(t_node *lst, t_env *my_env)
{
    t_ha	*ha;
    int m;
	
    m = 0;
	ha = helper_varia();
    while (lst->data[ha->read_index])
	{
		conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
		if (ft_Check_dollar(lst, ha))
			copy_env_value1(lst, my_env, ha, &m);
		else
		{
			if (lst->data[ha->read_index] == '$' && lst->data[ha->read_index + 1] == '$')
				count_dollare1(ha, lst->data, &m);
			else if (lst->data[ha->read_index] == '$' && (lst->data[ha->read_index + 1] == '\"' || lst->data[ha->read_index + 1] == '\''))
			{
				if (lst->data[ha->read_index + 1] == '\'' && ha->dablla_qoute % 2 == 0)
					ha->quote_count = ha->singl_qoute + 1;
				else if (lst->data[ha->read_index + 1] == '\"' && ha->singl_qoute % 2 == 0)
					ha->quote_count = ha->dablla_qoute + 1;
				if (ha->quote_count % 2 == 1)
                {
					ha->read_index++;
                    m++;
                }
				else
                {
					ha->read_index++;
                    m++;
                }
			}
			else
			{
                ha->read_index++;
                m++;
            }
		}
	}
    return(m);
}