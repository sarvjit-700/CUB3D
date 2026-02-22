/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:02:20 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/22 16:02:20 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int skip_spaces(char *line, int i)
{
    while (line[i] == 32 || line[i] == '\t')
        i++;
    return (i);
}

void    parse_id(char *line, t_map_data *data)
{
    int i;

    i = 0;
    i = skip_spaces(line, i);

    if (line[i] == '\0' || line[i] == '\n')
        return ;
    if (ft_strncmp(&line[i], "NO ", 3) == 0)
        data->elems_found++;
    else if (ft_strncmp(&line[i], "SO ", 3) == 0)
        data->elems_found++;
    else if (ft_strncmp(&line[i], "EA ", 3) == 0)
        data->elems_found++;
    else if (ft_strncmp(&line[i], "WE ", 3) == 0)
        data->elems_found++;
    else if (ft_strncmp(&line[i], "F ", 2) == 0)
        data->elems_found++;
    else if (ft_strncmp(&line[i], "C ", 2) == 0)
        data->elems_found++;
    else if (data->elems_found < 6)
        printf("Error missing element %d\n", data->elems_found);
    printf("found elem %d\n", i);
}

void    init_map(t_map_data *data)
{
    ft_memset(data, 0, sizeof(t_map_data));
    ft_memset(&data->ceiling, -1, sizeof(t_colour));
    ft_memset(&data->floor, -1, sizeof(t_colour));
    data->elems_found = 0;
}

int    parse_data(int fd, t_map_data *data)
{
    char *line;

    line = get_next_line(fd);
    init_map(data);
    //data->elems_found = 0;
    while (line)
    {
        if (data->elems_found < 6)
            parse_id(line, data);
        else
        {
            printf("need to parse map now\n");
        }
        free(line);
    }
    close(fd);
    return (1);
}


int check_extension(const char *filename)
{
    int len;
    if (!filename)
        return (0);
    len = ft_strlen(filename);
    if (!len || len < 4)
        return (0);
    if (ft_strncmp(filename + len -4, ".cub", 4) == 0)
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    int fd;
    t_map_data  data;

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
    parse_data(fd, &data);
}


