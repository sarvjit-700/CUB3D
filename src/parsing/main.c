/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:02:20 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/26 09:36:58 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

void	parse_id(char *line, t_map_data *data, int fd)
{
	int	i;

	i = skip_spaces(line, 0);
	if (line[i] == '\0' || line[i] == '\n' || line[i] == '\r')
		return ;
	if (parse_texture(&line[i], data, fd))
		return ;
	if (parse_colour_id(&line[i], data, fd))
		return ;
	free(line);	
	error_exit("Error - Unknown identifier found in map file", data, fd);
}

void	init_map(t_map_data *data)
{
	ft_memset(data, 0, sizeof(t_map_data));
	ft_memset(&data->ceiling, -1, sizeof(t_colour));
	ft_memset(&data->floor, -1, sizeof(t_colour));
	data->elems_found = 0;
	data->raw_map = ft_strdup("");
}

void	fill_grid(t_map_data *data)
{
	int	len;

	len = ft_strlen(data->raw_map);
	if (data->raw_map)
	{
		len = ft_strlen(data->raw_map);
		while (len > 0 && ft_isspace(data->raw_map[len - 1]))
		{
			data->raw_map[len - 1] = '\0';
			len--;
		}
	}
	if (check_empty_lines(data->raw_map))
		error_exit("Error - Empty line inside the map", data, -1);
	data->grid = ft_split(data->raw_map, '\n');
}

void	parse_data(int fd, t_map_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (data->elems_found < 6)
			parse_id(line, data, fd);
		else
			data->raw_map = ft_strjoin_free(data->raw_map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fill_grid(data);
	free(data->raw_map);
	data->raw_map = NULL;
	map_dimensions(data);
	valid_grid_player(data);
    check_walls(data);
}

int	check_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (!len || len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map_data	data;

	fd = -1;
	if (argc != 2 || !check_extension(argv[1]))
	{
		printf("Incorrect format. Use ./cub3d map.cub\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error could not open the map file\n");
		return (0);
	}
	init_map(&data);
	parse_data(fd, &data);
	printf("Parsing great!! BOOTING MLX\n");
	init_player_vectors(&data);
	init_graphics(&data);
	free_map_data(&data);
	return (0);
}
