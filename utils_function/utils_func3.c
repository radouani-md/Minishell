/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:09:05 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/03 11:22:09 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	get_length(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*md_itoa(int n)
{
	char	*result;
	int		len;
	long	num;

	num = n;
	len = get_length(n);
	result = (char *)gc_malloc(len + 1, 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (len-- > 0)
	{
		if (result[len] == '-')
			break ;
		result[len] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}

char	*random_num(void)
{
	char		*tmp;
	static int	i = 1;
	char		*num_str;
	char		*new_str;

	tmp = md_strdup("/tmp/tmp_");
	if (!tmp)
		return (NULL);
	num_str = md_itoa(i);
	new_str = md_strjoin(tmp, num_str);
	i++;
	return (new_str);
}

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
