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

void calc_lineheight(t_combi *c, t_tex *tex)
{
	while (c->worldmap[c->map.x][c->map.y] == 0)
	{
		if (tex->dist.side.x < tex->dist.side.y)
		{
			tex->dist.side.x = tex->dist.side.x + tex->dist.delta.x;
			c->map.x = c->map.x + tex->step.x;
			tex->side = 0;
		}
		else
		{
			tex->dist.side.y = tex->dist.side.y + tex->dist.delta.y;
			c->map.y = c->map.y + tex->step.y;
			tex->side = 1;
		}
	}
	if (tex->side == 0)
		tex->perwalldist = (c->map.x - c->ply->pos.x + (1 - tex->step.x) / 2) / c->ply->raydir.x;
	else
		tex->perwalldist = (c->map.y - c->ply->pos.y + (1 - tex->step.y) / 2) / c->ply->raydir.y;
	tex->lineheight = (int)(W_HEIGHT / tex->perwalldist);
}

void	calc_dist_side(t_combi *c, t_tex *tex)
{
	if (c->ply->raydir.x < 0)
	{
		tex->step.x = -1;
		tex->dist.side.x = (c->ply->pos.x - c->map.x) * (tex->dist.delta.x);
	}
	else
	{
		tex->step.x = 1;
		tex->dist.side.x = (c->map.x + 1.0 - c->ply->pos.x) * (tex->dist.delta.x);
	}
	if (c->ply->raydir.y < 0)
	{
		tex->step.y = -1;
		tex->dist.side.y = (c->ply->pos.y - c->map.y) * (tex->dist.delta.y);
	}
	else
	{
		tex->step.y = 1;
		tex->dist.side.y = (c->map.y + 1.0 - c->ply->pos.y) * (tex->dist.delta.y);
	}
}

void	calc_dist_delta(t_combi *c, t_map img, t_tex *tex)
{
	double	camerax;

	camerax = 2 * img.x / (double)(W_WIDTH) - 1;
	c->ply->raydir.x = c->ply->pdir.x + c->ply->flt.x * camerax;
	c->ply->raydir.y = c->ply->pdir.y + c->ply->flt.y * camerax;
	c->map.x = (int)c->ply->pos.x;
	c->map.y = (int)c->ply->pos.y;
	if (c->ply->raydir.y == 0)
		tex->dist.delta.x = 0;
	else if (c->ply->raydir.x == 0)
		tex->dist.delta.x = 1;
	else
		tex->dist.delta.x = fabs(1 / c->ply->raydir.x);
	if (c->ply->raydir.x == 0)
		tex->dist.delta.y = 0;
	else if (c->ply->raydir.y == 0)
		tex->dist.delta.y = 1;
	else
		tex->dist.delta.y = fabs(1 / c->ply->raydir.y);
}

void	calc_wall_ray(t_combi *c)
{
	t_map	img;
//	t_map	step;
//	int		side;
//	double	perwalldist;
//	t_dist	dist;
//	int		lineheight;
//	int		drawstart;
//	int		drawend;
	int		texnum;
//	double	wallx;
	int		texx;
	int		texy;
	double	dstep;
	double	texpos;
	int		tex_i;
	int		piex_i;
	t_tex	*tex;

	img.x = 0;
	while (img.x < W_WIDTH - 1)
	{
		tex = (t_tex *)malloc(sizeof(t_tex));
		calc_dist_delta(c, img, tex);
		calc_dist_side(c, tex);	
		calc_lineheight(c, tex);

		tex->drawstart = -(tex->lineheight / 2) + (W_HEIGHT / 2);
		if (tex->drawstart < 0)
			tex->drawstart = 0;
		tex->drawend = (tex->lineheight / 2) + (W_HEIGHT / 2);
		if (tex->drawend > W_HEIGHT)
			tex->drawend = W_HEIGHT - 1;

		texnum = c->worldmap[c->map.x][c->map.y] - 1;
		if (tex->side == 0)
			tex->wallx = c->ply->pos.y + tex->perwalldist * c->ply->raydir.y;
		else
			tex->wallx = c->ply->pos.x + tex->perwalldist * c->ply->raydir.x;
		tex->wallx -= floor((tex->wallx));
		texx = (int)(tex->wallx * (double)TEX_WIDTH);
		if (tex->side == 0 && c->ply->raydir.x > 0)
			texx = TEX_WIDTH - texx - 1;
		if (tex->side == 1 && c->ply->raydir.y < 0)
			texx = TEX_WIDTH - texx - 1;
		dstep = 1.0 * TEX_HEIGHT / tex->lineheight;
		texpos = (tex->drawstart - W_HEIGHT / 2 + tex->lineheight / 2) * dstep;

		img.y = tex->drawstart;
		while (img.y < tex->drawend)
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
