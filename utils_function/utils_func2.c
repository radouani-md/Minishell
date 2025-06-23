/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:25:21 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/23 16:48:10 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

size_t	copystr(char *dest, const char *src, size_t index, char c)
{
	size_t	i;

	i = 0;
	while (src[index] && src[index] != c)
	{
		dest[i] = src[index];
		i++;
		index++;
	}
	dest[i] = '\0';
	return (index);
}

char	**put_in(char **ptr, const char *s, char c, size_t count)
{
	size_t	i;
	size_t	index;
	size_t	j;

	i = 0;
	index = 0;
	while (i < count)
	{
		while (s[index] && s[index] == c)
			index++;
		j = 0;
		while (s[index + j] && s[index + j] != c)
			j++;
		ptr[i] = (char *)gc_malloc(j + 1, 1);
		if (!ptr[i])
		{
			return (NULL);
		}
		index = copystr(ptr[i], s, index, c);
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	**md_split(char const *s, char c)
{
	char	**ptr;
	int		count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	ptr = gc_malloc((count + 1) * sizeof(char *), 1);
	if (!ptr)
		return (NULL);
	ptr = put_in(ptr, s, c, count);
	return (ptr);
}

long	md_atoi_helper(char *str, long *exit_status, int sign, int *i)
{
	int				check;
	unsigned long	t;

	check = 0;
	t = 0;
	while (str[*i] && (str[*i] <= '9' && str[*i] >= '0'))
	{
		check = 1;
		if (t > (unsigned long)((9223372036854775807
				- (str[*i] - 48)) / 10))
			return (1);
		t = t * 10 + (str[*i] - 48);
		(*i)++;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (str[*i] != '\0' || !check)
		return (1);
	*exit_status = t * sign;
	return (0);
}

long	md_atoi(char *str, long *exit_status)
{
	int				i;
	int				sign;

	i = -1;
	sign = 1;
	while (str[++i])
	{
		if ((str[i] > '9' || str[i] < '0')
		&& str[i] != '-' && str[i] != '+'
		&& str[i] != ' ' && str[i] != '\t')
			return (1);
	}
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (md_atoi_helper(str, exit_status, sign, &i) == 1)
		return (1);
	return (0);
}
