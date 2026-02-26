/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:02:51 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/24 11:02:51 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_grid(char **grid)
{
	int i;

	i = 0;
	if (!grid)
		return;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	cleanup_mlx(t_map_data *data)
{
	if (data->no.texture)
		mlx_delete_texture(data->no.texture);
	if (data->so.texture)
		mlx_delete_texture(data->so.texture);
	if (data->we.texture)
		mlx_delete_texture(data->we.texture);
	if (data->ea.texture)
		mlx_delete_texture(data->ea.texture);
	if (data->mlx)
		mlx_terminate(data->mlx);
}

void	free_map_data(t_map_data *data)
{
	if (!data)
		return ;
	if (data->no.path)
		free(data->no.path);
	if (data->so.path)
		free(data->so.path);
	if (data->we.path)
		free(data->we.path);
	if (data->ea.path)
		free(data->ea.path);
	cleanup_mlx(data);
	if (data->raw_map)
	{
		free(data->raw_map);
		data->raw_map = NULL;
	}
	if (data->grid)
		free_grid(data->grid);
}

void	error_exit(char *msg, t_map_data *data, int fd)
{
	char *trash;

	if (fd >= 0)
	{
		trash = get_next_line(fd);
		while (trash)
		{
			free(trash);
			trash = get_next_line(fd);
		}
		close(fd);
	}
	printf("%s\n", msg);
	free_map_data(data);
	exit(1);
}
