/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:03:22 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/23 18:03:22 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_background(t_map_data *data)
{
    int x;
    int y;

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

void    key_hook(void *param)
{
    t_map_data  *data;

    data = (t_map_data *)param;
    if (mlx_is_key_down (data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}



void   perform_dda(t_ray *ray, t_map_data *data)
{
    ray->hit = 0;
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (data->grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}


void    calc_line_height(t_ray *ray)
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
        ray->draw_end = SCREEN_HEIGHT -1;
}

void    draw_wall_column(t_ray *ray, t_map_data *data, int x)
{
    int      y;
    uint32_t colour;

    if (ray->side == 1)
        colour = 0xAA0000FF;
    else
        colour = 0xFF0000FF;
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        mlx_put_pixel(data->img, x, y, colour);
        y++;
    }
}


void    init_dda(t_ray *ray, t_player *player)
{
    ray->map_x = (int)player->x;
    ray->map_y = (int)player->y;
    if (ray->dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->dir_x);
    if (ray->dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->dir_y);
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
    }
}

void    render_frame(void *param)
{
    t_map_data  *data;
    int         x;
    t_ray       ray;

    data = (t_map_data *)param;
    move_player(data);
    strafe_player(data);
    rotate_player(data);
    draw_background(data);
    x = 0;
    while (x < SCREEN_WIDTH)
    {
        ray.camera_x = 2 * x / (double)SCREEN_WIDTH -1;
        ray.dir_x = data->player.dir_x + data->player.plane_x * ray.camera_x;
        ray.dir_y = data->player.dir_y + data->player.plane_y * ray.camera_x;
        init_dda(&ray, &data->player);
        perform_dda(&ray, data);
        calc_line_height(&ray);
        draw_wall_column(&ray, data, x);
        x++;
    }
}

int init_graphics(t_map_data *data)
{
    data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "THE GAME!", false);
    if (!data->mlx)
        return (0);
    data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!data->img)
    {
        mlx_terminate(data->mlx);
        return (0);
    }
    draw_background(data);
    if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
    {
        mlx_terminate(data->mlx);
        return (0);
    }
    mlx_loop_hook(data->mlx, key_hook, data);
    mlx_loop_hook(data->mlx, render_frame, data);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return (1);
}

