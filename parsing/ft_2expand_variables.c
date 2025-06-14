/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:57:09 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/14 22:59:53 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_functin_env(char *dap, t_ha *ha)
{
	char	*str;
	int		i;

	i = 0;
	str = md_itoa(ha->err_status);
	while (str[i])
	{
		dap[(ha->dest_index)++] = str[i++];
	}
}

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

int	ft_count_env(char *dap, int read_index)
{
	t_ha	*hale;
	int		conut;

	conut = 0;
	hale = helper_varia(0);
	while (dap[read_index])
	{
		conut_dabel_singel_qoutition(dap[read_index], hale);
		if (read_index == 0 && dap[read_index] == ' ')
		{
			read_index++;
			conut++;
		}
		if ((hale->dbl_qte % 2 == 1 || hale->snl_qte % 2 == 1)
			|| (dap[read_index] != ' ' && dap[read_index]))
		{
			read_index++;
			conut++;
		}
		if (hale->dbl_qte % 2 == 0 && hale->snl_qte % 2 == 0
			&& (dap[read_index] == ' ' || dap[read_index] == '\0'))
			break ;
	}
	return (conut);
}

void	add_node(char *dap, t_node **lst, t_ha	*hal, char *tmp)
{
	t_node	*lst1;

	(*lst)->data = md_strdup(tmp);
	tmp = NULL;
	if (dap[hal->read_index] == ' ')
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
		tmp = gc_malloc(ft_count_env(dap, hal->read_index) + 2, 1);
		hal->dest_index = 0;
	}
}

void	fill_up_node(char *dap, t_node *lst)
{
	t_ha	*hal;
	char	*tmp;

	hal = helper_varia(0);
	tmp = gc_malloc(ft_count_env(dap, hal->read_index) + 2, 1);
	if (dap[hal->read_index] == '\0')
		lst->data = dap;
	while (dap[hal->read_index])
	{
		conut_dabel_singel_qoutition(dap[hal->read_index], hal);
		if (hal->read_index == 0 && dap[hal->read_index] == ' ')
			hal->read_index++;
		if ((hal->dbl_qte % 2 == 1 || hal->snl_qte % 2 == 1)
			|| (dap[hal->read_index] != ' ' && dap[hal->read_index]))
			tmp[hal->dest_index++] = dap[hal->read_index++];
		if (hal->dbl_qte % 2 == 0 && hal->snl_qte % 2 == 0
			&& (dap[hal->read_index] == ' ' || dap[hal->read_index] == '\0'))
		{
			tmp[hal->dest_index] = '\0';
			add_node(dap, &lst, hal, tmp);
		}
	}
}
