/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:19:01 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/24 13:19:01 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_isspace(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int	is_valid_char(char c)
{
	if (ft_strchr("01NSWE ", c))
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}
