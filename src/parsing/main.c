/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:02:20 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/24 16:00:48 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

char	*extract_path(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	len = 0;
	while (line[i] == 32 || line[i] == '\t')
		i++;
	while (line[i + len] && !ft_isspace(line[i + len]))
		len++;
	path = ft_substr(line, i, len);
	return (path);
}

int	parse_id(char *line, t_map_data *data)
{
	int	i;

	i = 0;
	i = skip_spaces(line, i);
	if (line[i] == '\0' || line[i] == '\n' || line[i] == '\r')
		return(1) ;
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
	{
		data->elems_found++;
		data->no.path = extract_path(&line[i + 3]);
	}
	else if (ft_strncmp(&line[i], "SO ", 3) == 0)
	{
		data->elems_found++;
		data->so.path = extract_path(&line[i + 3]);
	}
	else if (ft_strncmp(&line[i], "EA ", 3) == 0)
	{
		data->elems_found++;
		data->ea.path = extract_path(&line[i + 3]);
	}	else if (ft_strncmp(&line[i], "WE ", 3) == 0)
	{
		data->elems_found++;
		data->we.path = extract_path(&line[i + 3]);
	}
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
	{
		if (parse_colour(&line[i], &data->floor))
			data->elems_found++;
		else
			return (0);
	}
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
	{
		if (parse_colour(&line[i], &data->ceiling))
			data->elems_found++;
		else
			printf("Error - Invalid ceiling colour\n");
	}
	else if (data->elems_found < 6)
		return (0);
	return (1);
}

void	init_map(t_map_data *data)
{
	ft_memset(data, 0, sizeof(t_map_data));
	ft_memset(&data->ceiling, -1, sizeof(t_colour));
	ft_memset(&data->floor, -1, sizeof(t_colour));
	data->elems_found = 0;
	data->raw_map = ft_strdup("");
}

int	fill_grid(t_map_data *data)
{
	int	len;

	printf("raw : \n%s\n", data->raw_map);
	len = ft_strlen(data->raw_map);
	if (data->raw_map)
	{
		len = ft_strlen(data->raw_map);
		while (len > 0 && (data->raw_map[len - 1] == '\n' 
			|| data->raw_map[len - 1] == '\r' 
			|| data->raw_map[len - 1] == ' '
			|| data->raw_map[len - 1] == '\t'))
		{
			data->raw_map[len - 1] = '\0';
			len--;
		}
	}
	if (check_empty_lines(data->raw_map))
	{
		printf("Error - Empty line inside the map\n");
		return (0);
	}
	data->grid = ft_split(data->raw_map, '\n');
	return (1);
}




int	parse_data(int fd, t_map_data *data)
{
	char	*line;

	line = get_next_line(fd);
	init_map(data);
	while (line)
	{
		if (data->elems_found < 6)
		{
			if (!parse_id(line, data))
			{
				free(line);
				return (error_exit("Invalid identifier", data, fd));
			}
		}
		else
			data->raw_map = ft_strjoin_free(data->raw_map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!fill_grid(data))
	{
		free(data->raw_map);
		return (0);
	}
	free(data->raw_map);
	data->raw_map = NULL;
	map_dimensions(data);
	valid_grid_player(data);
    if (!check_walls(data))
        return (0);
    return (1);
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
	if (parse_data(fd, &data))
	{
		printf("Parsing great!! BOOTING MLX\n");
		init_player_vectors(&data);
		init_graphics(&data);
	}
	return (0);
}
