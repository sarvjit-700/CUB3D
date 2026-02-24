/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:10:22 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/23 23:10:22 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int load_textures(t_map_data *data)
{
    data->no.texture = mlx_load_png(data->no.path);
    data->so.texture = mlx_load_png(data->so.path);
    data->ea.texture = mlx_load_png(data->ea.path);
    data->we.texture = mlx_load_png(data->we.path);
    if (!data->no.texture || !data->so.texture || !data->ea.texture || !data->we.texture)
    {
        printf("Error failed to load textures\n");
        return (0);
    }
    return (1);
}

uint32_t    get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
    int index;

    if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
        return (0);
    index = (y * tex->width + x) * 4;
    return (tex->pixels[index] << 24 | 
            tex->pixels[index + 1] << 16 | 
            tex->pixels[index + 2] << 8 | 
            tex->pixels[index + 3]);
}

void    calc_texture_x(t_ray *ray, t_map_data *data)
{
    if (ray->side == 0 && ray->dir_x < 0)
        ray->texture = data->we.texture;
    else if (ray->side == 0 && ray->dir_x >= 0)
        ray->texture = data->ea.texture;
    else if (ray->side == 1 && ray->dir_y < 0)
        ray->texture = data->no.texture;
    else
        ray->texture = data->so.texture;
    if (ray->side == 0)
        ray->wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
    else
        ray->wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);
    ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
    if (ray->side == 0 && ray->dir_x > 0)
        ray->tex_x = ray->texture->width - ray->tex_x -1;
    if (ray->side == 1 && ray->dir_y < 0)
        ray->tex_x = ray->texture->width -ray->tex_x -1;
}

void    draw_wall_column(t_map_data *data, t_ray *ray, int x)
{
    double      step;
    double      tex_pos;
    int         tex_y;
    int         y;
    uint32_t    colour;

    step = 1.0 * ray->texture->height / ray->line_height;
    tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        tex_y = (int)tex_pos & (ray->texture->height -1);
        tex_pos += step;
        colour = get_texture_pixel(ray->texture, ray->tex_x, tex_y);
        if (ray->side == 1)
            colour = (colour >> 1) & 0x7F7F7F7F;
        mlx_put_pixel(data->img, x, y, colour);
        y++;
    }
}