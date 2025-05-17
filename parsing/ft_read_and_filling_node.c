/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_and_filling_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:17:33 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/17 16:45:27 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handel_pipe_direction(char *input, int *i, t_list **lst)
{
	char	*temp;
	int		n;
	int		a;

	a = 0;
	n = *i;
	if ((input[n] == '>' && input[n + 1] == '>')
		|| (input[n] == '<' && input[n + 1] == '<'))
		temp = malloc(sizeof(char) * (3));
	else
		temp = malloc(sizeof(char) * (2));
	if (!temp)
		return (free(input), ft_free(lst), 0);
	a = 0;
	temp[a++] = input[*i];
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
		temp[a++] = input[++(*i)];
	temp[a] = '\0';
	ft_lstadd_back(lst, ft_lstnew(temp));
	(*i)++;
	return (1);
}

int	ft_handle_double_single(char *input, int *i, t_list **lst)
{
	t_handel	*handel;

	handel = helper_variables(*i);
	handel->temp = malloc(sizeof(char) * (count_string(input, *i, handel) + 1));
	if (!handel->temp)
		return (free(input), ft_free(lst), free(handel), 0);
	handel->a = *i;
	while (input[*i])
	{
		if (!handel_qoutation(input, i, handel))
			return (free(input), ft_free(lst), free(handel->temp), free(handel), 0);
		handle_multiple_quotes(input, i, handel);
		if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
		{
			break ;
		}
	}
	handel->temp[handel->t] = '\0';
	ft_lstadd_back(lst, ft_lstnew(handel->temp));
	free(handel);
	return (1);
}

int	ft_ft(char *input, int *i, t_handel *handel)
{
	handel->a = *i;
	while (input[*i])
	{
		if (!handel_qoutation(input, i, handel))
			return (free(input), free(handel->temp), free(handel), 0);
		handle_multiple_quotes(input, i, handel);
		if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
			break ;
	}
	return (1);
}

int	ft_handle_string(char	*input, int	*i, t_list	**lst)
{
	t_handel	*handel;

	handel = helper_variables(*i);
	handel->temp = malloc(sizeof(char) * (100 + 1));
	if (!handel->temp)
		return (free(input), ft_free(lst), free(handel), 0);
	while (input[*i] && (input[*i] != ' ' && input[*i] != '\t')
		&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
	{
		if (input[*i] == '\"' || input[*i] == '\'')
		{
			if (ft_ft(input, i, handel) == 0)
				return (ft_free(lst), 0);
		}
		else
			handel->temp[(handel->t)++] = input[(*i)++];
		if (input[*i - 1] == '\0' || input[*i - 1] == ' '
			|| input[*i - 1] == '\t')
			break ;
	}
	handel->temp[handel->t] = '\0';
	ft_lstadd_back(lst, ft_lstnew(handel->temp));
	free(handel);
	return (1);
}

int	read_and_filling_node(char *input, t_list **lst)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			{
				if (!ft_handel_pipe_direction(input, &i, lst))
					return (0);
			}
			else if (input[i] == '\"' || input[i] == '\'')
			{
				if (!ft_handle_double_single(input, &i, lst))
					return (0);
			}
			else
			{
				if (!ft_handle_string(input, &i, lst))
					return (0);
			}
		}
		if (input[i] == ' ' || input[i] == '\t')
			i++;
	}
	return (1);
}
