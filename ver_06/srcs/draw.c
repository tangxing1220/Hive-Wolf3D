/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:23:34 by xtang             #+#    #+#             */
/*   Updated: 2020/09/21 15:50:04 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void	draw_square(t_mlx *mlx, t_vector vec, int color, int size)
{
	int i;
	int j;
	int index;

	j = size * 2 + size * vec.y;
	while (j < size * 2 + size * (vec.y + 1))
	{
		i = size * 2 + size * vec.x;
		while (i < size * 2 + size * (vec.x + 1))
		{
			index = (i * mlx->bits_per_piexl / 8) + (j * mlx->size_line);
			mlx->data_addr[index] = color;
			mlx->data_addr[++index] = color >> 8;
			mlx->data_addr[++index] = color >> 16;
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_combi *c)
{
	t_vector	map_v;
	t_vector	pos_v;
	int			size;


	size = W_WIDTH/ 10 / MAP_W;
	map_v.y = 0;
	while (map_v.y < MAP_W)
	{
		 map_v.x= 0;
		while (map_v.x < MAP_H)
		{
			if (c->worldmap[map_v.y][map_v.x] != 0)
				draw_square(c->mlx, map_v, COL_MIN_MAP, size);
			map_v.x++;
		}
		map_v.y++;
	}
	pos_v.y = c->player->pos.x;
	pos_v.x = c->player->pos.y;
	draw_square(c->mlx, pos_v, COL_MIN_POS, size);
}

void	floor_casting(t_combi *c)
{
	int		x;
	int		y;
	int		p;
	float	pos_z;
	float	row_distance;
	int		tex_flr_x;
	int		tex_flr_y;
	int		tex_cel_x;
	int		tex_cel_y;
	int		cell_x;
	int		cell_y;
	t_coord	floor_step;
	t_coord	floor;
	t_coord	raydir_left;
	t_coord	raydir_right;
	int		tex_flr_i;
	int		pixel_flr_i;
	int		tex_cel_i;
	int		pixel_cel_i;
	int		minimap_size;

	minimap_size = W_WIDTH;
	y = W_HEIGHT / 2 + 1;
	while (y < W_HEIGHT)
	{
		raydir_left.x = c->player->posdir.x - c->player->plane.x;
		raydir_left.y = c->player->posdir.y - c->player->plane.y;
		raydir_right.x = c->player->posdir.x + c->player->plane.x;
		raydir_right.y = c->player->posdir.y + c->player->plane.y;
		p = y - W_HEIGHT / 2;
		pos_z = 0.5 * W_HEIGHT;
		row_distance = pos_z / p;
		floor_step.x = row_distance * (raydir_right.x - raydir_left.x) / W_HEIGHT;
		floor_step.y = row_distance * (raydir_right.y - raydir_left.y) / W_HEIGHT;
		floor.x = c->player->pos.x + row_distance * raydir_left.x;
		floor.y = c->player->pos.y + row_distance * raydir_left.y;
		x = 0;
		while (x < W_WIDTH)
		{
			cell_x = (int)(floor.x);
			cell_y = (int)(floor.y);
			tex_flr_x = (int)(c->teximg[TEX_6_FLOOR]->width * (floor.x - cell_x)) & (c->teximg[TEX_6_FLOOR]->width - 1);
			tex_flr_y = (int)(c->teximg[TEX_6_FLOOR]->height * (floor.y - cell_y)) & (c->teximg[TEX_6_FLOOR]->height - 1);
			tex_cel_x = (int)(c->teximg[TEX_5_CEILING]->width * (floor.x - cell_x)) & (c->teximg[TEX_5_CEILING]->width - 1);
			tex_cel_y = (int)(c->teximg[TEX_5_CEILING]->height * (floor.y - cell_y)) & (c->teximg[TEX_5_CEILING]->height - 1);
			floor.x += floor_step.x;
			floor.y += floor_step.y;
/*
 ** floor
*/
			tex_flr_i = (tex_flr_x * c->teximg[TEX_6_FLOOR]->bits_per_piexl / 8) + (tex_flr_y * c->teximg[TEX_6_FLOOR]->size_line);
			pixel_flr_i = (x * c->mlx->bits_per_piexl / 8) + (y * c->mlx->size_line);
			if ((x < minimap_size * MAP_W && y < minimap_size * MAP_H) != 0)
			{
				c->mlx->data_addr[pixel_flr_i] = c->teximg[TEX_6_FLOOR]->data_addr[tex_flr_i];
				c->mlx->data_addr[++pixel_flr_i] = c->teximg[TEX_6_FLOOR]->data_addr[++tex_flr_i];
				c->mlx->data_addr[++pixel_flr_i] = c->teximg[TEX_6_FLOOR]->data_addr[++tex_flr_i];
			}
/*
 **	celling
*/
			tex_cel_i = (tex_cel_x * c->teximg[TEX_5_CEILING]->bits_per_piexl / 8) + (tex_cel_y * c->teximg[TEX_5_CEILING]->size_line);
			pixel_cel_i = (x * c->mlx->bits_per_piexl / 8) + ((W_HEIGHT - y - 1) * c->mlx->size_line);
			if ((x < minimap_size * MAP_W && (W_HEIGHT - y - 1) < minimap_size * MAP_H) != 0)
			{
				c->mlx->data_addr[pixel_cel_i] = c->teximg[TEX_5_CEILING]->data_addr[tex_cel_i];
				c->mlx->data_addr[++pixel_cel_i] = c->teximg[TEX_5_CEILING]->data_addr[++tex_cel_i];
				c->mlx->data_addr[++pixel_cel_i] = c->teximg[TEX_5_CEILING]->data_addr[++tex_cel_i];
			}
			x++;
		}
		y++;
	}
}

void		draw_map(t_combi *combi)
{
	int x;

	floor_casting(combi);
	x = 0;
	while (x < W_WIDTH - 1)
	{
		calc_ray(combi, x);
		x++;
	}
}