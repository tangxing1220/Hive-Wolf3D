/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:23:34 by xtang             #+#    #+#             */
/*   Updated: 2020/09/18 18:20:21 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void	draw_strip(int x, int draw_start, int draw_end, int color, t_mlx *mlx)
{
	int i;
	int y;

	y = draw_start;
	while (y <= draw_end)
	{
		i = (x * mlx->bits_per_piexl / 8) + (y * mlx->size_line);
		mlx->data_addr[i] = color;
		mlx->data_addr[++i] = color >> 8;
		mlx->data_addr[++i] = color >> 16;
		y++;
	}
}

/*
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
*/

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

	y = WIN_HEIGHT / 2 + 1;
	while (y < WIN_HEIGHT)
	{
		raydir_left.x = c->player->posdir.x - c->player->plane.x;
		raydir_left.y = c->player->posdir.y - c->player->plane.y;
		raydir_right.x = c->player->posdir.x + c->player->plane.x;
		raydir_right.y = c->player->posdir.y + c->player->plane.y;
		p = y - WIN_HEIGHT / 2;
		pos_z = 0.5 * WIN_HEIGHT;
		row_distance = pos_z / p;
		floor_step.x = row_distance * (raydir_right.x - raydir_left.x) / WIN_HEIGHT;
		floor_step.y = row_distance * (raydir_right.y - raydir_left.y) / WIN_HEIGHT;
		floor.x = c->player->pos.x + row_distance * raydir_left.x;
		floor.y = c->player->pos.y + row_distance * raydir_left.y;
		x = 0;
		while (x < WIN_WIDTH)
		{
			cell_x = (int)(floor.x);
			cell_y = (int)(floor.y);
			tex_flr_x = (int)(c->teximg[4]->width * (floor.x - cell_x)) & (c->teximg[4]->width - 1);
			tex_flr_y = (int)(c->teximg[4]->height * (floor.y - cell_y)) & (c->teximg[4]->height - 1);
			tex_cel_x = (int)(c->teximg[5]->width * (floor.x - cell_x)) & (c->teximg[5]->width - 1);
			tex_cel_y = (int)(c->teximg[5]->height * (floor.y - cell_y)) & (c->teximg[5]->height - 1);
			floor.x += floor_step.x;
			floor.y += floor_step.y;
/*
**	floor
*/
			tex_flr_i = (tex_flr_x * c->teximg[4]->bits_per_piexl / 8) + (tex_flr_y * c->teximg[4]->size_line);
			pixel_flr_i = (x * c->mlx->bits_per_piexl / 8) + (y * c->mlx->size_line);
			c->mlx->data_addr[pixel_flr_i] = c->teximg[4]->data_addr[tex_flr_i];
			c->mlx->data_addr[++pixel_flr_i] = c->teximg[4]->data_addr[++tex_flr_i];
			c->mlx->data_addr[++pixel_flr_i] = c->teximg[4]->data_addr[++tex_flr_i];
/*
**	celling
*/
			tex_cel_i = (tex_cel_x * c->teximg[5]->bits_per_piexl / 8) + (tex_cel_y * c->teximg[5]->size_line);
			pixel_cel_i = (x * c->mlx->bits_per_piexl / 8) + ((WIN_HEIGHT - y - 1) * c->mlx->size_line);
			c->mlx->data_addr[pixel_cel_i] = c->teximg[5]->data_addr[tex_cel_i];
			c->mlx->data_addr[++pixel_cel_i] = c->teximg[5]->data_addr[++tex_cel_i];
			c->mlx->data_addr[++pixel_cel_i] = c->teximg[5]->data_addr[++tex_cel_i];
			x++;
		}
		y++;
	}
}
