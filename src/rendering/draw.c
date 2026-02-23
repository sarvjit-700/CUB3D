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
    uint32_t x;
    uint32_t y;

    printf("DEBUG: starting draw bg\n");
    if (!data->img)
    {
        printf("DEBUG:ERROR image buffer is NULL\n");
        return ;
    }
    
    y = 0;
    while (y < 768) // Assuming 768 is your SCREEN_HEIGHT
    {
        x = 0;
        while (x < 1024) // Assuming 1024 is your SCREEN_WIDTH
        {
            if (y < 768 / 2)
                mlx_put_pixel(data->img, x, y, 0x87CEEBFF); // Sky
            else
                mlx_put_pixel(data->img, x, y, 0x8B4513FF); // Ground
            x++;
        }
        y++;
    }
    printf("DEBUG: finished bg\n");
}

// void    draw_background(t_map_data *data)
// {
//     int x;
//     int y;

//     printf("DEBUG: starting draw bg\n");
//     if (!data->img)
//     {
//         printf("DEBUG:ERROR image buffer is NULL\n");
//         return ;
//     }
//     y = 0;
//     while (y < 768)
//     {
//         x = 0;
//         while (x < 1024)
//         {
//             if (y < 768 / 2)
//                 // mlx_put_pixel(data->img, x, y, data->ceiling.hex_code);
//                 mlx_put_pixel(data->img, x, y, 0x87CEEBFF);
//             else
//                 mlx_put_pixel(data->img, x, y, 0x8B4513FF);
//             x++;
//         }
//         y++;
//     }
//     printf("DEBUG: finished bg\n");
// }

void    key_hook(void *param)
{
    t_map_data  *data;

    data = (t_map_data *)param;
    if (mlx_is_key_down (data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}

int init_graphics(t_map_data *data)
{
    data->mlx = mlx_init(1024, 768, "THE GAME!", false);
    if (!data->mlx)
        return (0);
    data->img = mlx_new_image(data->mlx, 1024, 768);
    if (!data->img)
    {
        mlx_terminate(data->mlx);
        return (0);
    }
    draw_background(data);
    if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
    {
        printf("DEBUG: ERROR! failed\n");
        mlx_terminate(data->mlx);
        return (0);
    }
    mlx_loop_hook(data->mlx, key_hook, data);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return (1);
}