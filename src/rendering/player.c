/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:00:38 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/27 10:02:53 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_vectors(t_map_data *data)
{
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	if (data->player.direction == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	if (data->player.direction == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	if (data->player.direction == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
	if (data->player.direction == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
}

void	move_player(t_map_data *data)
{
	double	move_speed;

	move_speed = 0.05;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->grid[(int)data->player.y][(int)(data->player.x
			+ data->player.dir_x * move_speed)] == '0')
			data->player.x += data->player.dir_x * move_speed;
		if (data->grid[(int)(data->player.y + data->player.dir_y
				* move_speed)][(int)data->player.x] == '0')
			data->player.y += data->player.dir_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->grid[(int)data->player.y][(int)(data->player.x
			- data->player.dir_x * move_speed)] == '0')
			data->player.x -= data->player.dir_x * move_speed;
		if (data->grid[(int)(data->player.y - data->player.dir_y
				* move_speed)][(int)data->player.x] == '0')
			data->player.y -= data->player.dir_y * move_speed;
	}
}

void	apply_rotation(t_map_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y
		* sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y
		* cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y
		* cos(angle);
}

void	rotate_player(t_map_data *data)
{
	double	rot_speed;

	rot_speed = 0.05;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		apply_rotation(data, rot_speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		apply_rotation(data, -rot_speed);
}

void	strafe_player(t_map_data *data)
{
	double	move_speed;

	move_speed = 0.05;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->grid[(int)data->player.y][(int)(data->player.x
			- data->player.dir_y * move_speed)] == '0')
			data->player.x -= data->player.dir_y * move_speed;
		if (data->grid[(int)(data->player.y + data->player.dir_x
				* move_speed)][(int)data->player.x] == '0')
			data->player.y += data->player.dir_x * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->grid[(int)data->player.y][(int)(data->player.x
			+ data->player.dir_y * move_speed)] == '0')
			data->player.x += data->player.dir_y * move_speed;
		if (data->grid[(int)(data->player.y - data->player.dir_x
				* move_speed)][(int)data->player.x] == '0')
			data->player.y -= data->player.dir_x * move_speed;
	}
}
