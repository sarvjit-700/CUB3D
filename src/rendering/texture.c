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
    data->tex_n = mlx_load_png(data->no_path);
    data->tex_s = mlx_load_png(data->so_path);
    data->tex_e = mlx_load_png(data->ea_path);
    data->tex_w = mlx_load_png(data->we_path);

    
}