/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:09:18 by xtang             #+#    #+#             */
/*   Updated: 2020/09/22 16:37:56 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

/*
**	The floor is drawn with horizontal scanlines.
*/

void	floor_draw(t_combi *c, t_coord flr, int x, int y)
{
	t_map	cell;
	t_map	tex_flr;
	int		tex_i;
	int		pixel_i;

	cell.x = (int)(flr.x);
	cell.y = (int)(flr.y);
	tex_flr.x = (int)(c->teximg[T_0_FLOOR]->w * (flr.x - cell.x)) &\
											(c->teximg[T_0_FLOOR]->w - 1);
	tex_flr.y = (int)(c->teximg[T_0_FLOOR]->h * (flr.y - cell.y)) &\
											(c->teximg[T_0_FLOOR]->h - 1);
	tex_i = (tex_flr.x * c->teximg[T_0_FLOOR]->bpp / 8) +\
									(tex_flr.y * c->teximg[T_0_FLOOR]->sl);
	pixel_i = (x * c->mlx->bpp / 8) + (y * c->mlx->sl);
	c->mlx->data_addr[pixel_i] = c->teximg[T_0_FLOOR]->data_addr[tex_i];
	c->mlx->data_addr[++pixel_i] = c->teximg[T_0_FLOOR]->data_addr[++tex_i];
	c->mlx->data_addr[++pixel_i] = c->teximg[T_0_FLOOR]->data_addr[++tex_i];
}

void	sky_draw(t_combi *c, int x, int y)
{
	int		pixel_i;
	int		tex_i;
	int		tex_x;
	int		tex_y;

	double	rate_x;
	double  rate_y;
	rate_x = (double)(W_WIDTH / c->teximg[T_8_SKY]->w);
	rate_y = (double)(W_HEIGHT / c->teximg[T_8_SKY]->h);

	tex_x = (int)(x * rate_x);
	tex_y = (int)((W_HEIGHT - y - 1) * rate_y);
	tex_i = (tex_x * c->teximg[T_8_SKY]->bpp / 8) + tex_y * c->teximg[T_8_SKY]->sl;
	pixel_i = (x * c->mlx->bpp / 8) + ((W_HEIGHT - y - 1) * c->mlx->sl);
	c->mlx->data_addr[pixel_i] = c->teximg[T_8_SKY]->data_addr[tex_i];
	c->mlx->data_addr[++pixel_i] = c->teximg[T_8_SKY]->data_addr[++tex_i];
	c->mlx->data_addr[++pixel_i] = c->teximg[T_8_SKY]->data_addr[++tex_i];

}

/*
**	The ceiling is drawn with horizontal scanlines.
*/

void	ceiling_draw(t_combi *c, t_coord flr, int x, int y)
{
	t_map	cell;
	t_map	tex_cel;
	int		tex_i;
	int		pixel_i;

	cell.x = (int)(flr.x);
	cell.y = (int)(flr.y);
	tex_cel.x = (int)(c->teximg[T_7_CEILING]->w * (flr.x - cell.x)) &\
											(c->teximg[T_7_CEILING]->w - 1);
	tex_cel.y = (int)(c->teximg[T_7_CEILING]->h * (flr.y - cell.y)) &\
											(c->teximg[T_7_CEILING]->h - 1);
	tex_i = (tex_cel.x * c->teximg[T_7_CEILING]->bpp / 8) +\
									(tex_cel.y * c->teximg[T_7_CEILING]->sl);
	pixel_i = (x * c->mlx->bpp / 8) + ((W_HEIGHT - y - 1) * c->mlx->sl);
	c->mlx->data_addr[pixel_i] = c->teximg[T_7_CEILING]->data_addr[tex_i];
	c->mlx->data_addr[++pixel_i] = c->teximg[T_7_CEILING]->data_addr[++tex_i];
	c->mlx->data_addr[++pixel_i] = c->teximg[T_7_CEILING]->data_addr[++tex_i];
}

/*
**	To calculate floor_step vector and floor vector.
*/

void	raydir_direction(t_combi *c, t_map img, t_coord *flr_step, t_coord *flr)
{
	t_coord	raydir_left;
	t_coord	raydir_right;
	float	row_distance;

	raydir_left.x = c->ply->pdir.x - c->ply->flt.x;
	raydir_left.y = c->ply->pdir.y - c->ply->flt.y;
	raydir_right.x = c->ply->pdir.x + c->ply->flt.x;
	raydir_right.y = c->ply->pdir.y + c->ply->flt.y;
	row_distance = (0.5 * (W_HEIGHT - 1)) / (img.y - (W_HEIGHT - 1) / 2);
	flr_step->x = row_distance * (raydir_right.x - raydir_left.x)\
															/ (W_HEIGHT - 1);
	flr_step->y = row_distance * (raydir_right.y - raydir_left.y)\
															/ (W_HEIGHT - 1);
	flr->x = c->ply->pos.x + row_distance * raydir_left.x;
	flr->y = c->ply->pos.y + row_distance * raydir_left.y;
}

/*
**	To draw floor and ceiling
*/

void	floor_ceiling_casting(t_combi *c)
{
	t_map	img;
	t_coord	flr_step;
	t_coord	flr;

	img.y = (W_HEIGHT - 1) / 2 + 1;
	while (img.y < (W_HEIGHT - 1))
	{
		raydir_direction(c, img, &flr_step, &flr);
		img.x = 0;
		while (img.x < (W_WIDTH - 1))
		{
			floor_draw(c, flr, img.x, img.y);
//			ceiling_draw(c, flr, img.x, img.y);
			sky_draw(c, img.x, img.y);
			flr.x += flr_step.x;
			flr.y += flr_step.y;
			img.x++;
		}
		img.y++;
	}
}
