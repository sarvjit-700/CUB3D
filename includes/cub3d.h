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

// export LIBGL_ALWAYS_SOFTWARE=1

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h> //for uint32
#include "../libft/libft.h"
#include "MLX42/MLX42.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

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

typedef struct s_player
{
    double      x;
    double      y;
    char        direction;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
} t_player;

typedef struct s_map_data
{
    mlx_t       *mlx;
    mlx_image_t *img;
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
    t_player    player;
    char        *no_path;
    char        *so_path;
    char        *we_path;
    char        *ea_path;
    mlx_texture_t *tex_n;
    mlx_texture_t *tex_s;
    mlx_texture_t *tex_e;
    mlx_texture_t *tex_w;
}   t_map_data;

typedef struct s_ray
{
    double  camera_x;
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;    
    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;
}   t_ray;

// functions - map_help //
char    *ft_strjoin_free(char *s1, char *s2);
int     check_empty_lines(char *raw_map);
void	free_grid(char **grid);
void    map_dimensions(t_map_data *data);
char	**dup_grid(char **grid, int height);


// -- validate grid -- //
int	is_valid_char(char c);
int	loop_grid(t_map_data *data, int y, int x, int *player);
int	valid_grid_player(t_map_data *data);
int check_walls(t_map_data *data);


// -- colours -- //
uint32_t get_rgba(int r, int g, int b, int a);
int parse_colour(char *line, t_colour *colour);

// -- draw -- //
int init_graphics(t_map_data *data);

// -- player --//
void    init_player_vectors(t_map_data *data);
void    move_player(t_map_data *data);
void    rotate_player(t_map_data *data);
void    strafe_player(t_map_data *data);

#endif