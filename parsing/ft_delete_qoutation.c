/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_qoutation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:22:40 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/18 11:22:43 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_ec(char *arg)
{
	t_ha	*hax;
	int		m;

	m = 0;
	hax = helper_varia(0);
	while (arg[hax->read_index])
	{
		if (arg[hax->read_index] == '\'' && hax->dbl_qte % 2 == 0)
			hax->snl_qte++;
		else if (arg[hax->read_index] == '\"' && hax->snl_qte % 2 == 0)
			hax->dbl_qte++;
		else if ((arg[hax->read_index] != '\"' && hax->snl_qte % 2 == 0)
			|| (arg[hax->read_index] != '\'' && hax->dbl_qte % 2 == 0)
			|| (arg[hax->read_index] == '\'' && hax->dbl_qte % 2 == 1)
			|| (arg[hax->read_index] == '\"' && hax->snl_qte % 2 == 1))
		{
			m++;
		}
		hax->read_index++;
	}
	return (m);
}

void	delete_qoutation(t_node *arg)
{
	t_ha	*ha;
	char	*str;

	while (arg)
	{
		ha = helper_varia(0);
		str = gc_malloc(ft_count_ec(arg->data) + 1, 1);
		while (arg->data[ha->read_index])
		{
			if (arg->data[ha->read_index] == '\'' && ha->dbl_qte % 2 == 0)
				ha->snl_qte++;
			else if (arg->data[ha->read_index] == '\"' && ha->snl_qte % 2 == 0)
				ha->dbl_qte++;
			else if ((arg->data[ha->read_index] != '\"' && ha->snl_qte % 2 == 0)
				|| (arg->data[ha->read_index] != '\'' && ha->dbl_qte % 2 == 0)
				|| (arg->data[ha->read_index] == '\'' && ha->dbl_qte % 2 == 1)
				|| (arg->data[ha->read_index] == '\"' && ha->snl_qte % 2 == 1))
				str[ha->dest_index++] = arg->data[ha->read_index];
			ha->read_index++;
		}
		str[ha->dest_index] = '\0';
		arg->data = str;
		arg = arg->next;
	}
}
