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

void	calc_wall_ray(t_combi *c)
{
	t_map	img;
	t_map	step;
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
	double	dstep;
	double	texpos;
	int		tex_i;
	int		piex_i;

	img.x = 0;
	while (img.x < W_WIDTH - 1)
	{
		hit = 0;
		camerax = 2 * img.x / (double)(W_WIDTH) - 1;
		c->ply->raydir.x = c->ply->pdir.x + c->ply->flt.x * camerax;
		c->ply->raydir.y = c->ply->pdir.y + c->ply->flt.y * camerax;
		c->map.x = (int)c->ply->pos.x;
		c->map.y = (int)c->ply->pos.y;

		if (c->ply->raydir.y == 0)
			deltadist.x = 0;
		else if (c->ply->raydir.x == 0)
			deltadist.x = 1;
		else
			deltadist.x = fabs(1 / c->ply->raydir.x);
		
		if (c->ply->raydir.x == 0)
			deltadist.y = 0;
		else if (c->ply->raydir.y == 0)
			deltadist.y = 1;
		else
			deltadist.y = fabs(1 / c->ply->raydir.y);


		if (c->ply->raydir.x < 0)
		{
			step.x = -1;
			sidedist.x = (c->ply->pos.x - c->map.x) * deltadist.x;
		}
		else
		{
			step.x = 1;
			sidedist.x = (c->map.x + 1.0 - c->ply->pos.x) * deltadist.x;
		}

		if (c->ply->raydir.y < 0)
		{
			step.y = -1;
			sidedist.y = (c->ply->pos.y - c->map.y) * deltadist.y;
		}
		else
		{
			step.y = 1;
			sidedist.y = (c->map.y + 1.0 - c->ply->pos.y) * deltadist.y;
		}

		while (hit == 0)
		{
			if (sidedist.x < sidedist.y)
			{
				sidedist.x = sidedist.x + deltadist.x;
				c->map.x = c->map.x + step.x;
				side = 0;
			}
			else
			{
				sidedist.y = sidedist.y + deltadist.y;
				c->map.y = c->map.y + step.y;
				side = 1;
			}
			if (c->worldmap[c->map.x][c->map.y] > 0)
				hit = 1;
		}

		if (side == 0)
			perwalldist = (c->map.x - c->ply->pos.x + (1 - step.x) / 2) / c->ply->raydir.x;
		else
			perwalldist = (c->map.y - c->ply->pos.y + (1 - step.y) / 2) / c->ply->raydir.y;
		lineheight = (int)(W_HEIGHT / perwalldist);

/*
**
*/	


		drawstart = -(lineheight / 2) + (W_HEIGHT / 2);
		if (drawstart < 0)
			drawstart = 0;
		drawend = (lineheight / 2) + (W_HEIGHT / 2);
		if (drawend > W_HEIGHT)
			drawend = W_HEIGHT - 1;
		texnum = c->worldmap[c->map.x][c->map.y] - 1;

		if (side == 0)
			wallx = c->ply->pos.y + perwalldist * c->ply->raydir.y;
		else
			wallx = c->ply->pos.x + perwalldist * c->ply->raydir.x;

		wallx -= floor((wallx));
		texx = (int)(wallx * (double)TEX_WIDTH);
		if (side == 0 && c->ply->raydir.x > 0)
			texx = TEX_WIDTH - texx - 1;
		if (side == 1 && c->ply->raydir.y < 0)
			texx = TEX_WIDTH - texx - 1;
		dstep = 1.0 * TEX_HEIGHT / lineheight;
		texpos = (drawstart - W_HEIGHT / 2 + lineheight / 2) * dstep;

		img.y = drawstart;
		while (img.y < drawend)
		{
			texy = (int)texpos & (TEX_HEIGHT - 1);
			texpos += dstep;
			tex_i = (texx * c->teximg[texnum]->bpp / 8) + (texy * c->teximg[texnum]->sl);
			piex_i = (img.x * c->mlx->bpp / 8) + (img.y * c->mlx->sl);
			c->mlx->data_addr[piex_i] = c->teximg[texnum]->data_addr[tex_i];
			c->mlx->data_addr[++piex_i] = c->teximg[texnum]->data_addr[++tex_i];
			c->mlx->data_addr[++piex_i] = c->teximg[texnum]->data_addr[++tex_i];
			img.y++;
		}
		img.x++;
	}
}
