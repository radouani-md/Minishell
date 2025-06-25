/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_handle_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:23:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/25 17:08:22 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	folwone_delete_node(t_node **arg, t_node **tmp1, t_node	**tmp)
{
	if (!(*arg)->next)
	{
		*arg = NULL;
		return (1);
	}
	if (!*tmp1)
	{
		*arg = (*tmp)->next;
		*tmp = (*tmp)->next;
	}
	else
	{
		(*tmp1)->next = (*tmp)->next;
		*tmp = (*tmp)->next;
	}
	return (0);
}

void	ft_node(t_node **arg)
{
	t_node	*tmp;
	t_node	*tmp1;

	tmp = *arg;
	tmp1 = NULL;
	while (tmp)
	{
		if (tmp->data[0] == '\0' && tmp->type != 2
			&& tmp->type != 4 && tmp->type != 1337)
		{
			if (folwone_delete_node(arg, &tmp1, &tmp))
			{
				break ;
			}
		}
		else
		{
			tmp1 = tmp;
			tmp = tmp->next;
		}
	}
}

int	count_handle_str(char *input, int i)
{
	t_ha	*handel;
	int		col;

	col = 0;
	handel = helper_varia(0);
	while (input[i] && (((input[i] != ' ' && input[i] != '\t')
				&& input[i] != '|' && input[i] != '>' && input[i] != '<')
			|| handel->dbl_qte % 2 == 1 || handel->snl_qte % 2 == 1))
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			conut_dabel_singel_qoutition(input[i], handel);
			col++;
			i++;
		}
		else
		{
			col++;
			i++;
		}
		if (input[i] == '\0'
			&& (handel->dbl_qte % 2 == 1 || handel->snl_qte % 2 == 1))
			return (col);
	}
	return (col);
}

void	handel_dolllar1(t_node *lst, char	*tmp, char	*tmp1, t_ha	*ha)
{
	static int	a;

	if (ha->dbl_qte % 2 != 1 && ha->snl_qte % 2 != 1
		&& lst->data[ha->read_index] == '$')
		tmp1[a++] = lst->data[ha->read_index];
	if (lst->data[ha->read_index] == '$'
		&& (lst->data[ha->read_index + 1] == '\"'
			|| lst->data[ha->read_index + 1] == '\''))
	{
		tmp1[a] = '\0';
		if (md_strlen(tmp1) % 2 == 0)
			tmp[ha->dest_index++] = lst->data[ha->read_index++];
		else
			handle_dollar_quote_case11(lst, ha, tmp);
	}
	else
		tmp[ha->dest_index++] = lst->data[ha->read_index++];
	if (lst->data[ha->read_index] != '$')
		a = 0;
}

void	handel_dolllar(t_node *lst)
{
	char	*tmp;
	char	*tmp1;
	t_ha	*ha;

	tmp = gc_malloc(md_strlen(lst->data) + 1, 1);
	tmp1 = gc_malloc(md_strlen(lst->data) + 1, 1);
	ha = helper_varia(0);
	while (lst->data[ha->read_index])
	{
		conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
		handel_dolllar1(lst, tmp, tmp1, ha);
	}
	tmp[ha->dest_index] = '\0';
	lst->data = md_strdup(tmp);
}
