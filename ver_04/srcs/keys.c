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

int		key_press(int key, t_combi *combi)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == ARROW_UP)
		combi->move.forwd = 1;
	else if (key == ARROW_DOWN)
		combi->move.backwd = 1;
	else if (key == ARROW_LEFT)
		combi->move.left = 1;
	else if (key == ARROW_RIGHT)
		combi->move.right = 1;
	return (0);
}

int		key_release(int key, t_combi *combi)
{
	if (key == ARROW_UP)
		combi->move.forwd = 0;
	else if (key == ARROW_DOWN)
		combi->move.backwd = 0;
	else if (key == ARROW_LEFT)
		combi->move.left = 0;
	else if (key == ARROW_RIGHT)
		combi->move.right = 0;
	return (0);
}

void	right_left_ward(t_combi *combi)
{
	double	rotspeed;
	t_coord	olddir;
	t_coord	oldplane;

	rotspeed = 0.04;
	if (combi->move.right == 1)
	{
		olddir.x = combi->player->posdir.x;
		combi->player->posdir.x = combi->player->posdir.x * cos(-rotspeed) - combi->player->posdir.y * sin(-rotspeed);
		combi->player->posdir.y = olddir.x * sin(-rotspeed) + combi->player->posdir.y * cos(-rotspeed);
		oldplane.x = combi->player->plane.x;
		combi->player->plane.x = combi->player->plane.x * cos(-rotspeed) - combi->player->plane.y * sin(-rotspeed);
		combi->player->plane.y = oldplane.x * sin(-rotspeed) + combi->player->plane.y * cos(-rotspeed);
	}
	if (combi->move.left == 1)
	{
		olddir.x = combi->player->posdir.x;
		combi->player->posdir.x = combi->player->posdir.x * cos(rotspeed) - combi->player->posdir.y * sin(rotspeed);
		combi->player->posdir.y = olddir.x * sin(rotspeed) + combi->player->posdir.y * cos(rotspeed);
		oldplane.x = combi->player->plane.x;
		combi->player->plane.x = combi->player->plane.x * cos(rotspeed) - combi->player->plane.y * sin(rotspeed);
		combi->player->plane.y = oldplane.x * sin(rotspeed) + combi->player->plane.y * cos(rotspeed);
	}
}

void	for_back_ward(t_combi *c)
{
	double movspeed;

	movspeed = 0.06;
	if (c->move.forwd == 1)
	{
		if (c->worldMap[(int)(c->player->pos.x + c->player->posdir.x * movspeed)][(int)(c->player->pos.y)] == 0)
			c->player->pos.x += c->player->posdir.x * movspeed;
		if (c->worldMap[(int)(c->player->pos.x)][(int)(c->player->pos.y + c->player->posdir.y * movspeed)] == 0)
			c->player->pos.y += c->player->posdir.y * movspeed;
	}
	if (c->move.backwd == 1)
	{
		if (c->worldMap[(int)(c->player->pos.x - c->player->posdir.x * movspeed)][(int)(c->player->pos.y)] == 0)
			c->player->pos.x -= c->player->posdir.x * movspeed;
		if (c->worldMap[(int)(c->player->pos.x)][(int)(c->player->pos.y - c->player->posdir.y * movspeed)] == 0)
			c->player->pos.y -= c->player->posdir.y * movspeed;
	}
}

int		movement(t_combi *combi)
{
	for_back_ward(combi);
	right_left_ward(combi);
	mlx_destroy_image(combi->mlx->mlx_ptr, combi->mlx->img_ptr);
	combi->mlx->img_ptr = mlx_new_image(combi->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	draw_map(combi);
	mlx_put_image_to_window(combi->mlx->mlx_ptr, combi->mlx->win_ptr, combi->mlx->img_ptr, 0, 0);
	return (0);
}
