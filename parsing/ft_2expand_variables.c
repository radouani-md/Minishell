/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:23:22 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/21 17:56:58 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_dollare(t_ha	*ha, char *lst)
{
	int	t;

	t = 0;
	while (lst[ha->read_index] == '$')
	{
		(ha->read_index)++;
		t++;
	}
	if (t % 2 == 1)
	{
		(ha->read_index)--;
	}
}

int	follow_count_env(t_ha *hale, char *dap, int read_index)
{
	if (hale->dbl_qte % 2 == 0 && hale->snl_qte % 2 == 0
		&& (dap[read_index] == ' ' || dap[read_index] == '\t'
			|| dap[read_index] == '\0'))
		return (1);
	return (0);
}

int	ft_count_env(char *dap, int read_index)
{
	t_ha	*hale;
	int		conut;

	conut = 0;
	hale = helper_varia(0);
	while (dap[read_index])
	{
		conut_dabel_singel_qoutition(dap[read_index], hale);
		if (read_index == 0 && (dap[read_index] == ' '
				|| dap[read_index] == '\t'))
		{
			read_index++;
		}
		if ((hale->dbl_qte % 2 == 1 || hale->snl_qte % 2 == 1)
			|| ((dap[read_index] != ' ' || dap[read_index] != '\t')
				&& dap[read_index]))
		{
			read_index++;
			conut++;
		}
		if (follow_count_env(hale, dap, read_index))
			break ;
	}
	return (conut);
}

void	add_node(char *dap, t_node **lst, t_ha	*hal, char **tmp)
{
	t_node	*lst1;

	(*lst)->data = md_strdup(*tmp);
	*tmp = NULL;
	if (dap[hal->read_index] == ' ' || dap[hal->read_index] == '\t')
		hal->read_index++;
	if (dap[hal->read_index])
	{
		if ((*lst)->type == 1 || (*lst)->type == 2 || (*lst)->type == 4)
			(*lst)->type = 1337;
		lst1 = (*lst)->next;
		(*lst)->next = ft_lstnew5();
		(*lst)->next->next = lst1;
		*lst = (*lst)->next;
		(*lst)->type = 0;
		*tmp = gc_malloc(ft_count_env(dap, hal->read_index) + 1, 1);
		hal->dest_index = 0;
	}
}

void	fill_up_node(char *dap, t_node *lst)
{
	t_ha	*hal;
	char	*tmp;

	hal = helper_varia(0);
	tmp = gc_malloc(ft_count_env(dap, hal->read_index) + 1, 1);
	if (dap[hal->read_index] == '\0')
		lst->data = dap;
	while (dap[hal->read_index])
	{
		conut_dabel_singel_qoutition(dap[hal->read_index], hal);
		if (hal->read_index == 0 && (dap[hal->read_index] == ' '
				|| dap[hal->read_index] == '\t'))
			hal->read_index++;
		if ((hal->dbl_qte % 2 == 1 || hal->snl_qte % 2 == 1)
			|| ((dap[hal->read_index] != ' ' || dap[hal->read_index] != '\t')
				&& dap[hal->read_index]))
			tmp[hal->dest_index++] = dap[hal->read_index++];
		if (hal->dbl_qte % 2 == 0 && hal->snl_qte % 2 == 0
			&& ((dap[hal->read_index] == ' ' || dap[hal->read_index] == '\t')
				|| dap[hal->read_index] == '\0'))
		{
			tmp[hal->dest_index] = '\0';
			add_node(dap, &lst, hal, &tmp);
		}
	}
}
