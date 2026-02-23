/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:21:06 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/23 22:03:49 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char c)
{
	if (ft_strchr("01NSWE ", c))
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	loop_grid(t_map_data *data, int y, int x, int *player)
{
	char	c;

	if (!is_valid_char(data->grid[y][x]))
	{
		printf("%c is NOT valid\n", data->grid[y][x]);
		return (0);
	}
	c = data->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player)++;
		data->player.x = (double)x + 0.5;
		data->player.y = (double)y + 0.5;
		data->player.direction = data->grid[y][x];
		data->grid[y][x] = '0'; // THIS MAKES PLAYER 0 FOR RAYCASTER? 
		printf("players :  %d\n", (*player));
	}
	return (1);
}

int	valid_grid_player(t_map_data *data)
{
	int y;
	int x;
	int player;

	y = 0;
	player = 0;
	while (data->grid[y])
	{
		x = 0;
		while (data->grid[y][x])
		{
			loop_grid(data, y, x, &player);
			x++;
		}
		y++;
	}
	if (player != 1)
	{
		printf("Error - need only 1 player!\n");
		return (0);
	}
	return (1);
}

int	floodfill(char **map, int x, int y, int max_height)
{
	if (y < 0 || y >= max_height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!floodfill(map, x + 1, y, max_height) ||
		!floodfill(map, x - 1, y, max_height) ||
		!floodfill(map, x, y + 1, max_height) ||
		!floodfill(map, x, y - 1, max_height))
		return (0);
	return (1);
}

int	check_walls(t_map_data *data)
{
	char	**map_copy;
	int		is_valid;
	int		pos_px;
	int		pos_py;

	pos_px = (int)data->player.x;
	pos_py = (int)data->player.y;
	map_copy = dup_grid(data->grid, data->height);
	if (!map_copy)
		return (0);
	is_valid = floodfill(map_copy, pos_px, pos_py, data->height);
	free_grid(map_copy);
	if (!is_valid)
	{
		printf("Error - Leaky walls\n");
		return (0);
	}
	return (1);	
}