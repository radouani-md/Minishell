/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:19:10 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/12 01:19:59 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s2 || !s1)
		return(1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static	int	if_str(char const c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	md_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*md_strtrim(char *s1, char const *set)
{
	char		*trim_s;	
	size_t		len_s;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (if_str(((char )*s1), set) == 1)
			s1++;
		else
			break ;
	}
	len_s = md_strlen(s1);
	while (len_s != 0)
	{
		if (if_str(s1[len_s - 1], set) == 1)
			len_s--;
		else
			break ;
	}
	trim_s = (char *)gc_malloc((len_s + 1) * sizeof(char), 1);
	if (!trim_s)
		return (NULL);
	md_strlcpy(trim_s, (char *)s1, len_s + 1);
	return (trim_s);
}
