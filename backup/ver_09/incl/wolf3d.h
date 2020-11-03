/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:23:32 by xtang             #+#    #+#             */
/*   Updated: 2020/09/21 18:10:37 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define W_WIDTH            1280
# define W_HEIGHT           1280
# define TEX_WIDTH          1024
# define TEX_HEIGHT         1024
# define MAP_W              24
# define MAP_H              24

# define NUM_TEXTURE        7

# define COL_MIN_MAP        0xFFFFFF
# define COL_MIN_POS        0xFF4500

# define T_0_BRICK        0
# define T_1_WOOD         1
# define T_2_METAL        2
# define T_3_STONE        3
# define T_4_GLASS        4
# define T_5_CEILING      5
# define T_6_FLOOR        6

# define KEY_ESC            53
# define ARROW_LEFT         123
# define ARROW_RIGHT        124
# define ARROW_DOWN         125
# define ARROW_UP           126

typedef	struct	s_coord
{
	double x;
	double y;
}				t_coord;

typedef	struct	s_vector
{
	int x;
	int y;
}				t_vector;

typedef struct	s_dist		
{
	t_coord		delta;
	t_coord		side;
}				t_dist;

typedef	struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		sl;
	int		endian;
}				t_mlx;

typedef	struct	s_teximage
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		sl;
	int		endian;
	int		w;
	int		h;
}				t_teximg;

typedef	struct	s_player
{
	t_coord		pos;
	t_coord		pdir;
	t_coord		flt;
	t_coord		raydir;
}				t_player;

typedef	struct	s_map
{
	int x;
	int y;
}				t_map;

typedef struct s_draw
{
	int start;
	int end;
}				t_draw;


typedef	struct	s_move
{
	int	forwd;
	int	backwd;
	int	left;
	int	right;
}				t_move;

typedef struct	s_tex
{
	t_dist	dist;
	t_map	step;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		side;
	double	perwalldist;
	double	wallx;
}				t_tex;

typedef	struct	s_combi
{
	t_mlx		*mlx;
	t_player	*ply;
	t_map		map;
	t_move		move;
	t_teximg	*teximg[NUM_TEXTURE];
	int			**worldmap;
}				t_combi;

int				key_press(int key, t_combi *combi);
int				key_release(int key, t_combi *combi);
int				movement(t_combi *combi);
void			draw_map(t_combi *combi);
void			load_texture(t_mlx *mlx, t_combi *combi);
int				**load_map(char *filename);
void			floor_casting(t_combi *c);
void			draw_minimap(t_combi *c);
void			calc_wall_ray(t_combi *c);
void			floor_ceiling_casting(t_combi *c);
void			ray_pos_dir(t_combi *c, t_map img);
t_map			dda_dist_size(t_combi *c, t_coord *sidedist, t_coord deltadist);

#endif
