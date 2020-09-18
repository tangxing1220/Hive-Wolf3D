/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:11:36 by xtang             #+#    #+#             */
/*   Updated: 2020/09/18 18:46:32 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void		print_usage(void)
{
    ft_putstr_fd("usage: ", STDERR_FILENO);
    ft_putstr_fd("./wolf3D [map]\n", STDERR_FILENO);
    ft_putstr_fd("map: maps/map1.txt\tmaps/map2.txt\n", STDERR_FILENO);
}

t_player	*player_init()
{
    t_player *player;


    player = (t_player *)malloc(sizeof(t_player));
    player->pos.x = 19; // player start postion 
    player->pos.y = 5;
    player->posdir.x = 1; // player initial face direction
    player->posdir.y = 0;
    player->plane.x = 0;    // versjion of camera plane
    player->plane.y = 0.66;
    player->raydir.x = 0;  // ray direction
    player->raydir.y = 0;
    return (player);
}

t_mlx		*wolf3d_mlx_init()
{
    t_mlx   *mlx;
    mlx = (t_mlx *)malloc(sizeof(t_mlx));
    mlx->mlx_ptr = mlx_init();
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,"WOLF3D");
    mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    mlx->data_addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_piexl, &mlx->size_line,
                        &mlx->endian);
    return (mlx);
}

t_combi		*combi_init(int **worldMap, t_player *player, t_mlx *mlx)
{
    t_combi     *combi;

    combi = (t_combi *)malloc(sizeof(t_combi));

    combi->player = player;
    combi->mlx = mlx;
    combi->worldMap = worldMap;

    combi->move.forwd = 0;
    combi->move.backwd = 0;
    combi->move.right = 0;
    combi->move.left = 0;
    combi->map.x = 0;
    combi->map.y = 0;
    combi->map.width = 0;
    combi->map.width = 0;

    return (combi);
}

void		calc_ray(t_combi *c, int x)
{
    int stepX;
    int stepY;
    int hit;
    int side;
    double cameraX;
    double perWallDist;
    t_coord deltaDist;
    t_coord sideDist;
    int lineHeight;
    int drawStart;
    int drawEnd;

    int texNum;
    double wallX;
    int texX;
    int texY;
    double step;
   double texPos;
   int y;
    int tex_i;
    int piex_i;

    hit = 0;
    cameraX = 2 * x / (double)(WIN_WIDTH) - 1;
    c->player->raydir.x = c->player->posdir.x + c->player->plane.x * cameraX;
    c->player->raydir.y = c->player->posdir.y + c->player->plane.y * cameraX;
    c->map.x = (int)c->player->pos.x;
    c->map.y = (int)c->player->pos.y;


    deltaDist.x = (c->player->raydir.y == 0) ? 0 : ((c->player->raydir.x == 0) ? 1 : fabs(1 / c->player->raydir.x));
    deltaDist.y = (c->player->raydir.x == 0) ? 0 : ((c->player->raydir.y == 0) ? 1 : fabs(1 / c->player->raydir.y));

    if (c->player->raydir.x < 0)
    {
        stepX = -1;
        sideDist.x = (c->player->pos.x - c->map.x) * deltaDist.x;
    }
    else
    {
        stepX = 1;
        sideDist.x = (c->map.x + 1.0 - c->player->pos.x) * deltaDist.x;
    }

    if (c->player->raydir.y < 0)
    {
        stepY = -1;
        sideDist.y = (c->player->pos.y - c->map.y) * deltaDist.y;
    }
    else
    {
        stepY = 1;
        sideDist.y = (c->map.y + 1.0 - c->player->pos.y) * deltaDist.y;
    }

    while (hit == 0)
    {
        if (sideDist.x < sideDist.y)
        {
            sideDist.x = sideDist.x + deltaDist.x;
            c->map.x = c->map.x + stepX;
            side = 0;            
        }
        else
        {
            sideDist.y = sideDist.y + deltaDist.y;
            c->map.y = c->map.y + stepY;
            side = 1;
        }
        if (c->worldMap[c->map.x][c->map.y] > 0)
            hit = 1;        
    }

    if (side == 0)
        perWallDist = (c->map.x - c->player->pos.x + (1 - stepX) / 2) / c->player->raydir.x;
    else
        perWallDist = (c->map.y - c->player->pos.y + (1 - stepY) / 2) / c->player->raydir.y;
    
    lineHeight = (int)(WIN_HEIGHT / perWallDist); 

    drawStart = -(lineHeight / 2) + (WIN_HEIGHT / 2);
    if (drawStart < 0) 
        drawStart = 0;

    drawEnd = (lineHeight / 2) + (WIN_HEIGHT / 2);
    if (drawEnd > WIN_HEIGHT)
        drawEnd = WIN_HEIGHT - 1;

    texNum = c->worldMap[c->map.x][c->map.y] - 1;

    if(side == 0)
        wallX = c->player->pos.y + perWallDist * c->player->raydir.y;
    else
        wallX = c->player->pos.x + perWallDist * c->player->raydir.x;
    wallX -= floor((wallX));

    texX = (int)(wallX * (double)TEX_WIDTH);
    if(side == 0 && c->player->raydir.x > 0) 
        texX = TEX_WIDTH - texX - 1;
    if(side == 1 && c->player->raydir.y < 0) 
        texX = TEX_WIDTH - texX - 1;

    step = 1.0 * TEX_HEIGHT / lineHeight;

    texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;

    y = drawStart; 
    while(y < drawEnd)
    {
        texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        tex_i = (texX * c->teximg[texNum]->bits_per_piexl / 8) + (texY * c->teximg[texNum]->size_line); 
        piex_i = (x * c->mlx->bits_per_piexl / 8) + (y * c->mlx->size_line);
        c->mlx->data_addr[piex_i] = c->teximg[texNum]->data_addr[tex_i];
        c->mlx->data_addr[++piex_i] = c->teximg[texNum]->data_addr[++tex_i];
        c->mlx->data_addr[++piex_i] = c->teximg[texNum]->data_addr[++tex_i];
        y++;
    }
}

void	draw_map(t_combi *combi)
{
    int x;
/*
** floor casting 
*/
    floor_casting(combi);

    x = 0;
    while(x < WIN_WIDTH - 1)
    {
        calc_ray(combi, x);
        x++;
    }
}

int		main(int argc, char **argv)
{
    t_mlx       *mlx;
    t_player    *player;
    t_combi     *combi;
    int         **worldMap;

    if (argc == 2)
    {
        worldMap = load_map(argv[1]);
        player = player_init();
        mlx = wolf3d_mlx_init();
        combi = combi_init(worldMap, player, mlx);
        load_texture(mlx, combi);
        mlx_hook(mlx->win_ptr, 2, 0, key_press, combi);
        mlx_hook(mlx->win_ptr, 3, 0, key_release, combi);

        draw_map(combi);
 //       draw_minimap(combi);
	    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	    mlx_loop_hook(mlx->mlx_ptr, movement, combi);
        mlx_loop(mlx->mlx_ptr);
    }
    else
    {
        print_usage();
    }    
    return (0);
}
