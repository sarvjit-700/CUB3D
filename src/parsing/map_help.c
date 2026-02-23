/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:00:34 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/23 17:05:14 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1, s2);
	free(s1);
	return (new_str);
}

int	check_empty_lines(char *raw_map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (raw_map[i] == '\n')
		i++;
	while (raw_map[i])
	{
		if (raw_map[i] == '\n')
		{
			j = i + 1;
			while (raw_map[j] == 32 || raw_map[j] == '\t' || raw_map[j] == '\r')
				j++;
			if (raw_map[j] == '\n' || raw_map[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	free_grid(char **grid)
{
	int i;

	i = 0;
	if (!grid)
		return;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

char	**dup_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char*) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			free_grid(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void map_dimensions(t_map_data *data)
{
	int y;
	int len;
	int i;

	data->height = 0;
	data->width = 0;
	y = 0;
	while (data->grid[y] != NULL)
	{
		len = ft_strlen(data->grid[y]);
		if (len > 0 && data->grid[y][len-1] == '\r')
		{
			data->grid[y][len-1] = '\0';
			len--;
		}
		if (len == 0)
		{
			free(data->grid[y]);
			i = y;
			while (data->grid[i] != NULL)
			{
				data->grid[i] = data->grid[i+1];
				i++;
			}
			continue;
		}
		if (len > data->width)
			data->width = len;
		y++;
	}
	data->height = y;
}