/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:21:06 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/28 10:40:22 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_grid(t_map_data *data, int y, int x, int *player)
{
	char	c;

	if (!is_valid_char(data->grid[y][x]))
	{
		printf("Error - character [%c] ", data->grid[y][x]);
		error_exit("Not Allowed In Map!", data, -1);
	}
	c = data->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player)++;
		data->player.x = (double)x + 0.5;
		data->player.y = (double)y + 0.5;
		data->player.direction = data->grid[y][x];
		data->grid[y][x] = '0';
	}
}

void	valid_grid_player(t_map_data *data)
{
	int	y;
	int	x;
	int	player;

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
		printf("Error - %d ", player);
		error_exit("PLayers. Need Just 1 Player!", data, -1);
	}
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
	if (!floodfill(map, x + 1, y, max_height)
		|| !floodfill(map, x - 1, y, max_height)
		|| !floodfill(map, x, y + 1, max_height)
		|| !floodfill(map, x, y - 1, max_height))
		return (0);
	return (1);
}

void print_map(char **map, int height)//takeout
{
    int i = 0;
    while (i < height)
    {
        printf("%s\n", map[i]);
        i++;
    }
    printf("\n");
}


int	sweep_leftovers(char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (ft_strchr("0NSWE", map_copy[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	check_walls(t_map_data *data)
{
	char	**map_copy;
	int		is_valid;
	int		pos_px;
	int		pos_py;

	pos_px = (int)data->player.x;
	pos_py = (int)data->player.y;
	map_copy = dup_grid(data->grid, data->height);
	if (!map_copy)
		error_exit("Error - Malloc failed for map copy", data, -1);
	is_valid = floodfill(map_copy, pos_px, pos_py, data->height);
	print_map(map_copy, data->height);//take out
	//if (is_valid)
	//	is_valid = sweep_leftovers(map_copy);
	free_grid(map_copy);
	if (!is_valid)
		error_exit("Error - Leaky Walls or Rogue 0's!", data, -1);
}
