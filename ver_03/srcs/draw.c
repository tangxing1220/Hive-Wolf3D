/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:23:34 by xtang             #+#    #+#             */
/*   Updated: 2020/09/15 10:23:38 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void	draw_strip(int x, int drawStart, int drawEnd, int color, t_mlx *mlx)
{
	int i;
    int y;

    y = drawStart;
	while (y <= drawEnd)
	{
        i = (x * mlx->bits_per_piexl / 8) + (y * mlx->size_line);
        mlx->data_addr[i] = color;
        mlx->data_addr[++i] = color >> 8;
        mlx->data_addr[++i] = color >> 16;
        y++;
	}
}

void draw_square(t_mlx *mlx, int x, int y,  int size)
{

}

void draw_minimap(t_combi *c)
{
    int         x;
    int         y;
    int         size;

    size = WIN_WIDTH / 10 / c->map.width;
    y = 0;
    while (y < c->map.width)
    {
        x = 0;
        while(x < c->map.height)
        {
            if (c->worldMap[y][x] != 0)
                draw_square(c->mlx, x, y, size);
            x++;
        }
        y++;
    }
}
