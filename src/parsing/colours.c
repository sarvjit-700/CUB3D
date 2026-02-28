/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:57:53 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/27 09:28:44 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_rgba(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	check_commas(char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (0);
	return (1);
}

int	is_valid_colour_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	while (!str[i] || str[i] == '\n' || str[i] == '\r')
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	assign_rgb(t_colour *colour, char **rgb)
{
	int	i;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_colour_num(rgb[i]))
			return (0);
		i++;
	}
	colour->r = ft_atoi(rgb[0]);
	colour->g = ft_atoi(rgb[1]);
	colour->b = ft_atoi(rgb[2]);
	if (colour->r > 255 || colour->g > 255 || colour->b > 255)
		return (0);
	colour->hex_code = get_rgba(colour->r, colour->g, colour->b);
	return (1);
}

int	parse_colour(char *line, t_colour *colour)
{
	char	**rgb;
	int		i;

	if (!check_commas(line))
		return (0);
	i = 0;
	while (line[i] == 'F' || line[i] == 'C' || line[i] == ' ')
		i++;
	rgb = ft_split(&line[i], ',');
	if (!assign_rgb(colour, rgb))
	{
		free_grid(rgb);
		return (0);
	}
	free_grid(rgb);
	return (1);
}
