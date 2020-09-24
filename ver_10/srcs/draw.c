/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:23:34 by xtang             #+#    #+#             */
/*   Updated: 2020/09/22 14:59:07 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

/*
**	The function to draw a squrre elements of small maps.
*/

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
			index = (i * mlx->bpp / 8) + (j * mlx->sl);
			mlx->data_addr[index] = color;
			mlx->data_addr[++index] = color >> 8;
			mlx->data_addr[++index] = color >> 16;
			i++;
		}
		j++;
	}
}

/*
**	To draw a small map at the top left conner. It show the whole map and
**	current player position.
*/

void	draw_minimap(t_combi *c)
{
	t_vector	map_v;
	t_vector	pos_v;
	int			size;

	size = W_WIDTH / 10 / MAP_W;
	map_v.y = 0;
	while (map_v.y < MAP_W)
	{
		map_v.x = 0;
		while (map_v.x < MAP_H)
		{
			if (c->worldmap[map_v.y][map_v.x] != 0)
				draw_square(c->mlx, map_v, COL_MIN_MAP, size);
			map_v.x++;
		}
		map_v.y++;
	}
	pos_v.y = c->ply->pos.x;
	pos_v.x = c->ply->pos.y;
	draw_square(c->mlx, pos_v, COL_MIN_POS, size);
}

/*
**	To draw/calculate floor and ceilling at first, then to draw walls,
**	to draw mini map at the end.
*/

void	draw_map(t_combi *c)
{
	floor_ceiling_casting(c);
	render_wall(c);
	draw_minimap(c);
}
