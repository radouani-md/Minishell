/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:06:26 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/22 17:49:41 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(char const *s, char c)
{
	size_t	i;
	int	count;

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

void	ftt_free(char **p, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(p[j]);
		j++;
	}
	free(p);
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
		ptr[i] = (char *)malloc(j + 1);
		if (!ptr[i])
		{
			ftt_free(ptr, i);
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
	int	count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	ptr = malloc((count + 1) * sizeof(char *));
	if (!ptr)
	return (NULL);
	ptr = put_in(ptr, s, c, count);
	return (ptr);
}
