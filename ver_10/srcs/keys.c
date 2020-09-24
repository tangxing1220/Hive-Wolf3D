/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:58:16 by xtang             #+#    #+#             */
/*   Updated: 2020/09/18 18:38:58 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

/*
**	To response the status of arrow keys pressed. The player moves continuously
**	when the key is pressed.
*/

int		key_press(int key, t_combi *c)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == ARROW_UP)
		c->move.forwd = 1;
	else if (key == ARROW_DOWN)
		c->move.backwd = 1;
	else if (key == ARROW_LEFT)
		c->move.left = 1;
	else if (key == ARROW_RIGHT)
		c->move.right = 1;
	return (0);
}

/*
**	To response the status of arrow keys release.
*/

int		key_release(int key, t_combi *c)
{
	if (key == ARROW_UP)
		c->move.forwd = 0;
	else if (key == ARROW_DOWN)
		c->move.backwd = 0;
	else if (key == ARROW_LEFT)
		c->move.left = 0;
	else if (key == ARROW_RIGHT)
		c->move.right = 0;
	return (0);
}

/*
**	The player is turning left or turning right that are rotation here.
**	It is not easy to understand. The camera plane and player must be
**	rotate at the same time. the rotate a vector, multiply it with the
**	rotation matrix. [ cos(a)  -sin(a) ]
**					 [ sin(a)   cos(a) ]
*/

void	right_left_ward(t_combi *c)
{
	double	rosp;
	t_coord	odir;
	t_coord	oflt;

	rosp = 0.20;
	if (c->move.left == 1)
	{
		odir.x = c->ply->pdir.x;
		c->ply->pdir.x = c->ply->pdir.x * cos(-rosp)\
									- c->ply->pdir.y * sin(-rosp);
		c->ply->pdir.y = odir.x * sin(-rosp) + c->ply->pdir.y * cos(-rosp);
		oflt.x = c->ply->flt.x;
		c->ply->flt.x = c->ply->flt.x * cos(-rosp) - c->ply->flt.y * sin(-rosp);
		c->ply->flt.y = oflt.x * sin(-rosp) + c->ply->flt.y * cos(-rosp);
	}
	if (c->move.right == 1)
	{
		odir.x = c->ply->pdir.x;
		c->ply->pdir.x = c->ply->pdir.x * cos(rosp)\
									- c->ply->pdir.y * sin(rosp);
		c->ply->pdir.y = odir.x * sin(rosp) + c->ply->pdir.y * cos(rosp);
		oflt.x = c->ply->flt.x;
		c->ply->flt.x = c->ply->flt.x * cos(rosp) - c->ply->flt.y * sin(rosp);
		c->ply->flt.y = oflt.x * sin(rosp) + c->ply->flt.y * cos(rosp);
	}
}

/*
**	It is easy to understand that direct movement.
**	The value is a vector(x, y) including direct infomation.
**	The player can move until hitting the wall.
*/

void	for_back_ward(t_combi *c)
{
	double mvsp;

	mvsp = 0.06;
	if (c->move.forwd == 1)
	{
		if (c->worldmap[(int)(c->ply->pos.x + c->ply->pdir.x * mvsp)]\
						[(int)(c->ply->pos.y)] == 0)
			c->ply->pos.x += c->ply->pdir.x * mvsp;
		if (c->worldmap[(int)(c->ply->pos.x)][(int)\
						(c->ply->pos.y + c->ply->pdir.y * mvsp)] == 0)
			c->ply->pos.y += c->ply->pdir.y * mvsp;
	}
	if (c->move.backwd == 1)
	{
		if (c->worldmap[(int)(c->ply->pos.x - c->ply->pdir.x * mvsp)]\
						[(int)(c->ply->pos.y)] == 0)
			c->ply->pos.x -= c->ply->pdir.x * mvsp;
		if (c->worldmap[(int)(c->ply->pos.x)][(int)
						(c->ply->pos.y - c->ply->pdir.y * mvsp)] == 0)
			c->ply->pos.y -= c->ply->pdir.y * mvsp;
	}
}

/*
**	To handle the player movement and redraw the images.
**	The function is passed through mlx_loop_hook().
*/

int		movement(t_combi *c)
{
	for_back_ward(c);
	right_left_ward(c);
	mlx_destroy_image(c->mlx->mlx_ptr, c->mlx->img_ptr);
	c->mlx->img_ptr = mlx_new_image(c->mlx->mlx_ptr, W_WIDTH, W_HEIGHT);
	draw_map(c);
	mlx_put_image_to_window(c->mlx->mlx_ptr, c->mlx->win_ptr,\
									c->mlx->img_ptr, 0, 0);
	return (0);
}
