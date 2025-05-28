/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_qoutation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:14:54 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/27 15:34:40 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_ec(char *arg)
{
	t_ha	*hax;
	int		m;

	m = 0;
	hax = helper_varia();
	while (arg[hax->read_index])
	{
		if (arg[hax->read_index] == '\'' && hax->dablla_qoute % 2 == 0)
			hax->singl_qoute++;
		else if (arg[hax->read_index] == '\"' && hax->singl_qoute % 2 == 0)
			hax->dablla_qoute++;
		else if ((arg[hax->read_index] != '\"' && hax->singl_qoute % 2 == 0) || (arg[hax->read_index] != '\'' && hax->dablla_qoute % 2 == 0)
			||(arg[hax->read_index] == '\'' && hax->dablla_qoute % 2 == 1)||(arg[hax->read_index] == '\"' && hax->singl_qoute % 2 == 1))
		{
			m++;
		}
		hax->read_index++;
	}
	return (free(hax), m);
}

void	delete_qoutation(t_node *arg)
{
	t_ha	*ha;
	char	*str;
	t_node	*tmp;

	tmp = arg;
	while (arg)
	{
		ha = helper_varia();
		str = malloc(sizeof(char) * (ft_count_ec(arg->data) + 1));
		if(!str)
			return(free(ha));
		while (arg->data[ha->read_index])
		{
			if (arg->data[ha->read_index] == '\'' && ha->dablla_qoute % 2 == 0)
				ha->singl_qoute++;
			else if (arg->data[ha->read_index] == '\"' && ha->singl_qoute % 2 == 0)
				ha->dablla_qoute++;
			else if ((arg->data[ha->read_index] != '\"' && ha->singl_qoute % 2 == 0) || (arg->data[ha->read_index] != '\'' && ha->dablla_qoute % 2 == 0)
				||(arg->data[ha->read_index] == '\'' && ha->dablla_qoute % 2 == 1)||(arg->data[ha->read_index] == '\"' && ha->singl_qoute % 2 == 1))
			{
				str[ha->dest_index++] = arg->data[ha->read_index];
			}
			ha->read_index++;
		}
		str[ha->dest_index] = '\0';
		free(arg->data);
		free(ha);
		arg->data = str;
		arg = arg->next;
	}
	while (tmp)
	{
		printf("To: [%s]-->{%d}\n", tmp->data,tmp->type);
		tmp = tmp->next;
	}
}
