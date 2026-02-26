/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:29:59 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/25 20:29:59 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_path(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
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

int assign_texture(char **path, char *line, t_map_data *data, int fd)
{
    if (*path != NULL)
    {
        free(line);
        error_exit("Error - Duplicate texture found!", data, fd);
    }
    *path = extract_path(line + 3);
    if (!validate_path(*path))
	{
		free(line);
		error_exit("Error - Texture file does not exist or cannot be read", data, fd);
	}
    
    data->elems_found++;
    return (1);
}


int parse_texture(char *line, t_map_data *data, int fd)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return (assign_texture(&data->no.path, line, data, fd));
    if (ft_strncmp(line, "SO ", 3) == 0)
        return (assign_texture(&data->so.path, line, data, fd));
    if (ft_strncmp(line, "EA ", 3) == 0)
        return (assign_texture(&data->ea.path, line, data, fd));
    if (ft_strncmp(line, "WE ", 3) == 0)
        return (assign_texture(&data->we.path, line, data, fd));
    return (0);
}

int parse_colour_id(char *line, t_map_data *data, int fd)
{
    t_colour    *c;

    if (ft_strncmp(line, "F ", 2) == 0)
        c = &data->floor;
    else if (ft_strncmp(line, "C ", 2) == 0)
        c = &data->ceiling;
    else
        return (0);
    if (c->r != -1)
        {
            free(line);
            error_exit("Error - Too many Floor/Ceiling colours!", data, fd);
        }
		if (parse_colour(line, c) == 0)
		{
            free(line);
			error_exit("Error - Invalid colour format!", data, fd);
        }
        data->elems_found++;
        return (1);
}
