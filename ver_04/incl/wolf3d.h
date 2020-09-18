/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:23:32 by xtang             #+#    #+#             */
/*   Updated: 2020/09/09 20:23:38 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

# define WIN_WIDTH          1280
# define WIN_HEIGHT         1280
# define TEX_WIDTH          1024
# define TEX_HEIGHT         1024
# define MAP_WIDTH          24
# define MAP_HEIGHT         24

# define NUM_TEXTURE        6

# define COL_RED            0x87CEEB
# define COL_GREEN          0xFF7F50
# define COL_BLUE           0x7CFC00
# define COL_YELLOW         0xFFFF00
# define COL_WHITE          0xFF4500
# define COL_SKY_BLUE		0x87CEEB
# define COL_CORAL			0xFF7F50
# define COL_LAWN_GREEN		0x7CFC00
# define COL_YELLOW			0xFFFF00
# define COL_ORANGE_RED		0xFF4500

# define KEY_ESC            53
# define ARROW_LEFT         123
# define ARROW_RIGHT        124
# define ARROW_DOWN         125
# define ARROW_UP           126

typedef struct  s_coord
{
    double x;
    double y;
}               t_coord;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *data_addr;
    int     bits_per_piexl;
    int     size_line;
    int     endian;
}               t_mlx;

typedef struct  s_teximage
{
    void    *img_ptr;
    char    *data_addr;
    int     bits_per_piexl;
    int     size_line;
    int     endian;
    int     width;
    int     height;
}               t_teximg;

typedef struct s_player
{
    t_coord     pos;
    t_coord     posdir;
    t_coord     plane;
    t_coord     raydir;
}              t_player;

typedef struct  s_map
{
    int width;
    int height;
    int x;
    int y;
}               t_map;

typedef struct s_move
{
    int     forwd;
    int     backwd;
    int     left;
    int     right;
}               t_move;


typedef struct  s_combi
{
    t_mlx       *mlx;
    t_player    *player;
    t_map       map;
    t_move      move;
    t_teximg   *teximg[NUM_TEXTURE];
    int         **worldMap;     
}               t_combi;

void	draw_strip(int x, int drawStart, int drawEnd, int color, t_mlx *mlx);
int     key_press(int key, t_combi *combi);
int     key_release(int key, t_combi *combi);
int     movement(t_combi *combi);
void    draw_map(t_combi *combi);
void    load_texture(t_mlx *mlx, t_combi *combi);
int     **load_map(char *filename);
void    floor_casting(t_combi *c);
// void    draw_minimap(t_combi *c);

#endif