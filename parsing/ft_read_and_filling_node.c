/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_and_filling_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:22:28 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/18 11:22:30 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ha_pipe_direction(char *input, int *i, t_list **lst)
{
	char	*temp;
	int		a;

	a = 0;
	if (!ft_strncmp(input + *i, "<<", 2) || !ft_strncmp(input + *i, ">>", 2))
		temp = gc_malloc(3, 1);
	else
		temp = gc_malloc(2, 1);
	a = 0;
	temp[a++] = input[*i];
	if (!ft_strncmp(input + *i, "<<", 2) || !ft_strncmp(input + *i, ">>", 2))
		temp[a++] = input[++(*i)];
	temp[a] = '\0';
	ft_lstadd_back(lst, ft_lstnew(temp));
	(*i)++;
}

int	ft_handle_string(char	*input, int	*i, t_list	**lst, t_ha *err)
{
	t_ha	*handel;

	handel = helper_varia(0);
	handel->temp = gc_malloc(count_handle_str(input, *i) + 2, 1);
	while (input[*i] && (((input[*i] != ' ' && input[*i] != '\t')
				&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
			|| handel->dbl_qte % 2 == 1 || handel->snl_qte % 2 == 1))
	{
		if (input[*i] == '\"' || input[*i] == '\'')
		{
			conut_dabel_singel_qoutition(input[*i], handel);
			handel->temp[(handel->dest_index)++] = input[(*i)++];
		}
		else
			handel->temp[(handel->dest_index)++] = input[(*i)++];
		if (input[*i] == '\0'
			&& (handel->dbl_qte % 2 == 1 || handel->snl_qte % 2 == 1))
		{
			write(2, "bash : syntax error\n", 20);
			return (err->err_status = 2, 0);
		}
	}
	handel->temp[handel->dest_index] = '\0';
	ft_lstadd_back(lst, ft_lstnew(handel->temp));
	return (1);
}

int	read_and_filling_node(char *input, t_list **lst, t_ha *err)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			{
				ft_ha_pipe_direction(input, &i, lst);
			}
			else
			{
				if (!ft_handle_string(input, &i, lst, err))
					return (0);
			}
		}
		if (input[i] == ' ' || input[i] == '\t')
			i++;
	}
	return (1);
}
