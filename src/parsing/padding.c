/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:06:53 by ssukhija          #+#    #+#             */
/*   Updated: 2026/03/02 09:06:53 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pad_single_line(t_map_data *data, int y)
{
	char	*padded_line;
	int		x;

	padded_line = malloc(sizeof(char) * (data->width + 1));
	if (!padded_line)
		error_exit("Malloc failed when padding", data, -1);
	x = 0;
	while (data->grid[y][x])
	{
		padded_line[x] = data->grid[y][x];
		x++;
	}
	while (x < data->width)
	{
		padded_line[x] = ' ';
		x++;
	}
	padded_line[x] = '\0';
	free(data->grid[y]);
	data->grid[y] = padded_line;
}

void	pad_map_grid(t_map_data *data)
{
	int		y;
	int		len;

	y = 0;
	while (y < data->height)
	{
		len = ft_strlen(data->grid[y]);
		if (len < data->width)
			pad_single_line(data, y);
		y++;
	}
}
