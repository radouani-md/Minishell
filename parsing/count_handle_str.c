/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_handle_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:23:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/18 11:23:54 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (!(*arg)->next)
			{
				*arg = NULL;
			}
			else if (!tmp1)
			{
				*arg = tmp->next;
			}
			else
				tmp1->next = tmp->next;
		}
		tmp1 = tmp;
		tmp = tmp->next;
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
