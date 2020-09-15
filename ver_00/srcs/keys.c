/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:58:16 by xtang             #+#    #+#             */
/*   Updated: 2020/09/15 11:58:21 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/wolf3d.h"

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

int key_press(int key, t_combi *combi)
{
    if(key == KEY_ESC)
        exit (0);
    else if (key == ARROW_UP)
        combi->move->forwd = 1;
    else if (key == ARROW_DOWN)
        combi->move->backwd = 1;
    else if (key == ARROW_LEFT)
        combi->move->left = 1;
    else if (key == ARROW_RIGHT)
        combi->move->right = 1;
    return (0);
}

int key_release(int key, t_combi *combi)
{
    if (key == ARROW_UP)
        combi->move->forwd = 0;
    else if (key == ARROW_DOWN)
        combi->move->backwd = 0;
    else if (key == ARROW_LEFT)
        combi->move->left = 0;
    else if (key == ARROW_RIGHT)
        combi->move->right = 0;
    return (0);
}

void	right_left_ward(t_combi *combi)
{
    double speed;
    t_coord dirold;
    t_coord planeold;

    speed = 0.04;


	if (combi->move->left == 1)
	{
		dirold.x = combi->player->dir.x;
        combi->player->dir.x = combi->player->dir.x * cos(speed) - combi->player->dir.y * sin(speed);
        combi->player->dir.y = combi->player->dir.x * sin(speed) + combi->player->dir.y * cos(speed);
        planeold.x = combi->player->plane.x;
        combi->player->plane.x = combi->player->plane.x * cos(speed) - combi->player->plane.y * sin(speed);
        combi->player->plane.y = combi->player->plane.x * sin(speed) + combi->player->plane.y * cos(speed);
	}
	if (combi->move->right == 1)
	{
		dirold.x = combi->player->dir.x;
		combi->player->dir.x = combi->player->dir.x * cos(speed) - combi->player->dir.y * sin(speed);
		combi->player->dir.y = dirold.x * sin(speed) + combi->player->dir.y * cos(speed);
		planeold.x = combi->player->plane.x;
		combi->player->plane.x = combi->player->plane.x * cos(speed) - combi->player->plane.y * sin(speed);
		combi->player->plane.y = planeold.x * sin(speed) + combi->player->plane.y * cos(speed);
	}
}

void for_back_ward(t_combi *combi)
{
    double speed;

    speed = 0.06;
    if (combi->move->forwd == 1)
    {
        if (worldMap[(int)(combi->player->pos.x + combi->player->dir.x * speed)][(int)(combi->player->pos.y)] == 0)
            combi->player->pos.x += combi->player->dir.x * speed;
        if (worldMap[(int)(combi->player->pos.x)][(int)(combi->player->pos.y + combi->player->dir.y * speed )] == 0)
            combi->player->pos.y += combi->player->dir.y * speed;
    }
    if (combi->move->backwd == 1)
    {
        if (worldMap[(int)(combi->player->pos.x - combi->player->dir.x * speed)][(int)(combi->player->pos.y)] == 0)
            combi->player->pos.x -= combi->player->dir.x * speed;
        if (worldMap[(int)(combi->player->pos.x)][(int)(combi->player->pos.y - combi->player->dir.y * speed )] == 0)
            combi->player->pos.y -= combi->player->dir.y * speed;
    }
}


int		movement(t_combi *combi)
{
	for_back_ward(combi);
	right_left_ward(combi);
//	mlx_destroy_image(combi->mlx->mlx_ptr, combi->mlx->img_ptr);
//	combi->mlx->img_ptr = mlx_new_image(combi->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
//	draw_map(combi->mlx, combi->player);
//	mlx_put_image_to_window(combi->mlx->mlx_ptr, combi->mlx->win_ptr, combi->mlx->img_ptr, 0, 0);
	return (0);
}