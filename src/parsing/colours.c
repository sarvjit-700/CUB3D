/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:57:53 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/23 18:57:53 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int parse_colour(char *line, t_colour *colour)
{  
    char **rgb;
    int i;

    i = 0;
    while (line[i] == 'F' || line[i] == 'C' || line[i] == ' ')
        i++;
    rgb = ft_split(&line[i], ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        return (0);
    colour->r = ft_atoi(rgb[0]);
    colour->g = ft_atoi(rgb[1]);
    colour->b = ft_atoi(rgb[2]);
    colour->hex_code = get_rgba(colour->r, colour->g, colour->b, 255);
    free_grid(rgb);
    return (1);
}