/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:53:51 by xtang             #+#    #+#             */
/*   Updated: 2020/09/21 17:53:55 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void		calc_ray(t_combi *c, int x)
{
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	camerax;
	double	perwalldist;
	t_coord	deltadist;
	t_coord	sidedist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texnum;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	int		y;
	int		tex_i;
	int		piex_i;
	int		minimap_size;

	minimap_size = W_WIDTH/ 10;
	hit = 0;
	camerax = 2 * x / (double)(W_WIDTH) - 1;
	c->player->raydir.x = c->player->posdir.x + c->player->plane.x * camerax;
	c->player->raydir.y = c->player->posdir.y + c->player->plane.y * camerax;
	c->map.x = (int)c->player->pos.x;
	c->map.y = (int)c->player->pos.y;
	deltadist.x = (c->player->raydir.y == 0) ? 0 : (c->player->raydir.x == 0 ? 1 : fabs(1 / c->player->raydir.x));
	deltadist.y = (c->player->raydir.x == 0) ? 0 : (c->player->raydir.y == 0 ? 1 : fabs(1 / c->player->raydir.y));
	if (c->player->raydir.x < 0)
	{
		step_x = -1;
		sidedist.x = (c->player->pos.x - c->map.x) * deltadist.x;
	}
	else
	{
		step_x = 1;
		sidedist.x = (c->map.x + 1.0 - c->player->pos.x) * deltadist.x;
	}
	if (c->player->raydir.y < 0)
	{
		step_y = -1;
		sidedist.y = (c->player->pos.y - c->map.y) * deltadist.y;
	}
	else
	{
		step_y = 1;
		sidedist.y = (c->map.y + 1.0 - c->player->pos.y) * deltadist.y;
	}
	while (hit == 0)
	{
		if (sidedist.x < sidedist.y)
		{
			sidedist.x = sidedist.x + deltadist.x;
			c->map.x = c->map.x + step_x;
			side = 0;
		}
		else
		{
			sidedist.y = sidedist.y + deltadist.y;
			c->map.y = c->map.y + step_y;
			side = 1;
		}
		if (c->worldmap[c->map.x][c->map.y] > 0)
			hit = 1;
	}
	if (side == 0)
		perwalldist = (c->map.x - c->player->pos.x + (1 - step_x) / 2) / c->player->raydir.x;
	else
		perwalldist = (c->map.y - c->player->pos.y + (1 - step_y) / 2) / c->player->raydir.y;
	lineheight = (int)(W_HEIGHT / perwalldist);
	drawstart = -(lineheight / 2) + (W_HEIGHT / 2);
	if (drawstart < 0)
		drawstart = 0;
	drawend = (lineheight / 2) + (W_HEIGHT / 2);
	if (drawend > W_HEIGHT)
		drawend = W_HEIGHT - 1;
	texnum = c->worldmap[c->map.x][c->map.y] - 1;
	if (side == 0)
		wallx = c->player->pos.y + perwalldist * c->player->raydir.y;
	else
		wallx = c->player->pos.x + perwalldist * c->player->raydir.x;
	wallx -= floor((wallx));
	texx = (int)(wallx * (double)TEX_WIDTH);
	if (side == 0 && c->player->raydir.x > 0)
		texx = TEX_WIDTH - texx - 1;
	if (side == 1 && c->player->raydir.y < 0)
		texx = TEX_WIDTH - texx - 1;
	step = 1.0 * TEX_HEIGHT / lineheight;
	texpos = (drawstart - W_HEIGHT / 2 + lineheight / 2) * step;
	y = drawstart;
	while (y < drawend)
	{
		texy = (int)texpos & (TEX_HEIGHT - 1);
		texpos += step;
		tex_i = (texx * c->teximg[texnum]->bits_per_piexl / 8) + (texy * c->teximg[texnum]->size_line);
		piex_i = (x * c->mlx->bits_per_piexl / 8) + (y * c->mlx->size_line);
		if ((x < minimap_size * MAP_W && y < minimap_size * MAP_H) != 0)
		{
			c->mlx->data_addr[piex_i] = c->teximg[texnum]->data_addr[tex_i];
			c->mlx->data_addr[++piex_i] = c->teximg[texnum]->data_addr[++tex_i];
			c->mlx->data_addr[++piex_i] = c->teximg[texnum]->data_addr[++tex_i];
		}
		y++;
	}
}
