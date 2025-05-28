/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:57:09 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/28 16:01:57 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_env(char *dap, int read_index)
{
	t_ha	*hale;

	hale = helper_varia();
	while (dap[read_index])
	{
		conut_dabel_singel_qoutition(dap[read_index], hale);
		if (read_index == 0 && dap[read_index] == ' ')
			read_index++;
		if ((hale->dablla_qoute % 2 == 1 || hale->singl_qoute % 2 == 1)
			|| (dap[read_index] != ' ' && dap[read_index]))
			read_index++;
		if (hale->dablla_qoute % 2 == 0 && hale->singl_qoute % 2 == 0
			&& (dap[read_index] == ' ' || dap[read_index] == '\0'))
		{
			break ;
		}
	}
	return (read_index);
}
int ft_tchek_q(char *tmp)
{
	int i;

	i = 0;
	while(tmp[i])
	{
		if(tmp[i] == '\"' || tmp[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
void	fill_up_node(char *dap, t_node *lst)
{
	t_node	*lst1;
	t_ha	*hal;
	char	*tmp;

	hal = helper_varia();
	tmp = malloc(100 + 1);//ft_count_env(dap, hal->read_index)
	if(!tmp)
		return ;
	if (dap[hal->read_index] == '\0')
		lst->data = dap;
	while (dap[hal->read_index])
	{
		conut_dabel_singel_qoutition(dap[hal->read_index], hal);
		if (hal->read_index == 0 && dap[hal->read_index] == ' ')
			hal->read_index++;
		if ((hal->dablla_qoute % 2 == 1 || hal->singl_qoute % 2 == 1) || (dap[hal->read_index] != ' ' && dap[hal->read_index]))
			tmp[hal->dest_index++] = dap[hal->read_index++];
		if (hal->dablla_qoute % 2 == 0 && hal->singl_qoute % 2 == 0 && (dap[hal->read_index] == ' ' || dap[hal->read_index] == '\0'))
		{
			tmp[hal->dest_index] = '\0';
			lst->data = md_strdup(tmp);
			tmp = NULL;
			lst->type = 0;
			if (dap[hal->read_index] == ' ')
				hal->read_index++;
			if (dap[hal->read_index])
			{
				lst1 = lst->next;
				lst->next = ft_lstnew5();
				lst->next->next = lst1;
				lst = lst->next;
				tmp = malloc(ft_count_env(dap, hal->read_index));
				if(!tmp)
					return ;
				hal->dest_index = 0;
			}
		}
	}
}
