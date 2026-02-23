/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:00:38 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/23 20:00:38 by ssukhija         ###   ########.fr       */
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
