/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_types_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd_md_haker <rd_md_haker@student.42.fr>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 23:40:09 by rd_md_haker       #+#    #+#             */
/*   Updated: 2025-04-26 23:40:09 by rd_md_haker      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int implement_outfile(t_node *nodes)
{
    int fd;

    fd = open(nodes->data, O_RDONLY);
    if (fd == -1)
        return (-1);
    return (0);
}
