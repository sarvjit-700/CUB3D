/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:00:34 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/28 10:28:36 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pad_map_grid(t_map_data *data)
{
	int		y;
	int		x;
	int		len;
	char	*padded_line;
	
	y = 0;
	while (y < data->height)
	{
		len = ft_strlen(data->grid[y]);
		if (len < data->width)
		{
			padded_line = malloc(sizeof(char) * (data->width + 1));
			if (!padded_line)
				error_exit("Error - Malloc failed during map padding", data, -1);
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
		y++;
	}
}

int	check_empty_lines(char *raw_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(raw_map[i]))
		i++;
	while (raw_map[i])
	{
		if (raw_map[i] == '\n')
		{
			j = i + 1;
			while (raw_map[j] == 32 || raw_map[j] == '\t' || raw_map[j] == '\r')
				j++;
			if (raw_map[j] == '\n' || raw_map[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

char	**dup_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			free_grid(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	remove_empty_row(char **grid, int index)
{
	int	i;

	free(grid[index]);
	i = index;
	while (grid[i] != NULL)
	{
		grid[i] = grid[i + 1];
		i++;
	}
}

void	map_dimensions(t_map_data *data, int y)
{
	int	len;

	while (data->grid[y] != NULL)
	{
		len = ft_strlen(data->grid[y]);
		if (len > 0 && data->grid[y][len - 1] == '\r')
		{
			data->grid[y][len - 1] = '\0';
			len--;
		}
		if (len == 0)
		{
			remove_empty_row(data->grid, y);
			continue ;
		}
		if (len > data->width)
			data->width = len;
		y++;
	}
	data->height = y;
}
