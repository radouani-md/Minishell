/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_ft_ha_do_si.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:16:38 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/09 21:18:38 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_handel	*helper_variables(int i)
{
	t_handel	*new_node;

	new_node = malloc(sizeof(t_handel));
	if (!new_node)
		return (NULL);
	new_node->t = 0;
	new_node->a = 0;
	new_node->q = 1;
	new_node->quote_count = 1;
	new_node->next = NULL;
	return (new_node);
}

int	count_string(char *input, int i, t_handel *handel)
{
	int	n;
	int	q;
	int	quote_count;

	n = 0;
	q = 1;
	quote_count = 1;
	while (input[i])
	{
		if (input[handel->a] == '\"' && input[i] == '\"')
			(quote_count)++;
		if (input[handel->a] == '\'' && input[i] == '\'')
			(q)++;
		if ((quote_count % 2 == 1 && input[handel->a] == '\"' && (input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == '\0'))
			|| (q % 2 == 1 && input[handel->a] == '\'' && (input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == '\0')))
		{
			n++;
			break ;
		}
		i++;
		n++;
	}
	return (n);
}

int	handel_qoutation(char *input, int *i, t_handel *handel) // handel_qoutation
{
	if (input[handel->a] == '\"' && input[*i] == '\"')
		(handel->quote_count)++;
	if (input[handel->a] == '\'' && input[*i] == '\'')
		(handel->q)++;
	while ((handel->quote_count % 2 == 0 && input[handel->a] == '\"')
		|| (handel->q % 2 == 0 && input[handel->a] == '\''))
	{
		if(*i != handel->a && ((input[*i] == '\"' && input[handel->a] == '\"') || (input[*i] == '\'' && input[handel->a] == '\'')))
			break ;
		handel->temp[(handel->t)++] = input[*i];
		(*i)++;
		if (!input[*i]) // break; دشي علاش مع توصل \0 دير "ls d""skfjfe حيت هدي تبقى تقرى لا م نهاية فية حالة كان
		{
			printf("eroor\n");
			return (0);
		}
	}
	return (1);
}

void	handle_multiple_quotes(char *input, int *i, t_handel *handel)
{
	if (((input[*i] == '\"') || input[*i] == '\'') && input[*i])
	{
		handel->temp[(handel->t)++] = input[(*i)++];
		if (input[*i]) //  echo "$HOME$"$"youssef"    input[*i] = '\0'  او هدي *i++ حيت هدي نزيد ب
		{
			handel->a = *i;
			if (input[handel->a] == '\"')
				handel->quote_count = 1;
			else if (input[handel->a] == '\'')
				handel->q = 1;
			else if ((input[*i] != ' ' || input[*i] == '\t') && input[*i] != '>'
				&& input[*i] != '<' && input[*i] != '|' && input[*i])
			{
				handel->temp[(handel->t)++] = input[(*i)++];
				handel->quote_count = 1;
				handel->q = 1;
				handel->a = *i;
			}
		}
	}
	else
	{
		handel->temp[(handel->t)++] = input[(*i)++];
		handel->a = *i;
	}
}
