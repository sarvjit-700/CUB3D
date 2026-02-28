/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:03:22 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/27 09:51:42 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_map_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				mlx_put_pixel(data->img, x, y, data->ceiling.hex_code);
			else
				mlx_put_pixel(data->img, x, y, data->floor.hex_code);
			x++;
		}
		y++;
	}
}

void	key_hook(void *param)
{
	t_map_data	*data;

	data = (t_map_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	calc_line_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist <= 0.000001)
		ray->perp_wall_dist = 0.000001;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	render_frame(void *param)
{
	t_map_data	*data;
	int			x;
	t_ray		ray;

	data = (t_map_data *)param;
	move_player(data);
	strafe_player(data);
	rotate_player(data);
	draw_background(data);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray.dir_x = data->player.dir_x + data->player.plane_x * ray.camera_x;
		ray.dir_y = data->player.dir_y + data->player.plane_y * ray.camera_x;
		init_dda(&ray, &data->player);
		perform_dda(&ray, data);
		calc_line_height(&ray);
		calc_texture_x(&ray, data);
		draw_wall_column(data, &ray, x);
		x++;
	}
}

int	init_graphics(t_map_data *data)
{
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "THE GAME!", false);
	if (!data->mlx)
		error_exit("Error - MLX initialization failed", data, -1);
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img)
		error_exit("Error - MLX image creation failed", data, -1);
	draw_background(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
		error_exit("Error - MLX image to window failed", data, -1);
	load_textures(data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
	return (1);
}
