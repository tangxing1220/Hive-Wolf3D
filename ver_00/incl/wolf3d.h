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

# define WIN_WIDTH      1280
# define WIN_HEIGHT     960
# define MAP_WIDTH      24
# define MAP_HEIGHT     24

typedef struct s_coord
{
    double x;
    double y;
    int    blk_x;
    int    blk_y;
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

typedef struct s_player
{
    t_coord     pos;
    t_coord     dir;
    t_coord     plane;
}              t_player;

typedef struct  s_map
{
    int width;
    int height;
    int world_map[][];
}               t_map;

#endif