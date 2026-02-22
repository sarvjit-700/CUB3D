/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:25:41 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/22 16:25:41 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h> //for uint32
#include "../libft/libft.h"
#include "MLX42/MLX42.h"

typedef struct s_texture
{
    char            *path;
    mlx_texture_t   *texture;
} t_texture;

typedef struct s_colour
{
    int         r;
    int         g;
    int         b;
    uint32_t    hex_code;
} t_colour;


typedef struct s_map_data
{
    t_texture   no;
    t_texture   so;
    t_texture   ea;
    t_texture   we;
    t_colour    floor;
    t_colour    ceiling;
    int         elems_found;
    char        *raw_map;
    char        **grid;
    int         width;
    int         height;
}   t_map_data;


// functions - map_help //
char    *ft_strjoin_free(char *s1, char *s2);
int     check_empty_lines(char *raw_map);


#endif