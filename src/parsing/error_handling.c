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

void	free_map_data(t_map_data *data)
{
	if (data->no.path)
		free(data->no.path);
	if (data->so.path)
		free(data->so.path);
	if (data->we.path)
		free(data->we.path);
	if (data->ea.path)
		free(data->ea.path);
	if (data->raw_map)
		free(data->raw_map);
//	if (data->grid)
//		free_split(data->grid);
}


int	error_exit(char *msg, t_map_data *data, int fd)
{
	printf("Error\n%s\n", msg);
	if (fd >= 0)
		close(fd);
	free_map_data(data);
	return (0);
}

