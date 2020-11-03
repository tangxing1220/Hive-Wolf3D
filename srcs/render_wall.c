/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:12:11 by xtang             #+#    #+#             */
/*   Updated: 2020/09/24 13:12:14 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void	render_texture(t_combi *c, t_tex *tex)
{
	double	wallx;

	if (tex->side == 0)
		wallx = c->ply->pos.y + tex->perwalldist * c->ply->raydir.y;
	else
		wallx = c->ply->pos.x + tex->perwalldist * c->ply->raydir.x;
	wallx -= floor(wallx);
	tex->texx = (int)(wallx * (double)TEX_WIDTH);
	if (tex->side == 0 && c->ply->raydir.x > 0)
		tex->texx = TEX_WIDTH - tex->texx - 1;
	if (tex->side == 1 && c->ply->raydir.y < 0)
		tex->texx = TEX_WIDTH - tex->texx - 1;
	tex->dstep = 1.0 * TEX_HEIGHT / tex->lineheight;
	tex->texpos = (tex->drawstart - W_HEIGHT / 2 + tex->lineheight / 2)\
																* tex->dstep;
}

void	draw_color(t_combi *c, int texnum, t_map img, t_tex *tex)
{
	int piex_i;
	int tex_i;

	tex_i = (tex->texx * c->teximg[texnum]->bpp / 8)\
										+ (tex->texy * c->teximg[texnum]->sl);
	piex_i = (img.x * c->mlx->bpp / 8) + (img.y * c->mlx->sl);
	c->mlx->data_addr[piex_i] = c->teximg[texnum]->data_addr[tex_i];
	c->mlx->data_addr[++piex_i] = c->teximg[texnum]->data_addr[++tex_i];
	c->mlx->data_addr[++piex_i] = c->teximg[texnum]->data_addr[++tex_i];
}

void	render_wall(t_combi *c)
{
	t_map	img;
	t_tex	*tex;
	int		texnum;

	img.x = 0;
	while (img.x < W_WIDTH - 1)
	{
		tex = (t_tex *)malloc(sizeof(t_tex));
		calc_dist_delta(c, img, tex);
		calc_dist_side(c, tex);
		calc_lineheight(c, tex);
		calc_line_pos(tex);
		render_texture(c, tex);
		texnum = c->worldmap[c->map.x][c->map.y];
		img.y = tex->drawstart;
		while (img.y < tex->drawend)
		{
			tex->texy = (int)tex->texpos & (TEX_HEIGHT - 1);
			tex->texpos += tex->dstep;
			draw_color(c, texnum, img, tex);
			img.y++;
		}
		img.x++;
	}
}
