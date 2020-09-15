/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:11:36 by xtang             #+#    #+#             */
/*   Updated: 2020/09/09 20:11:39 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void print_usage(void)
{
    ft_putstr_fd("usage: ", STDERR_FILENO);
    ft_putstr_fd("./wolf3D [mpa]\n", STDERR_FILENO);
    ft_putstr_fd("maps/map_1 maps/map_2 maps/map_3\n", STDERR_FILENO);
}

void open_read_file(char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY);

}

int worldMap[MAP_HEIGHT][MAP_WIDTH] = 
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_player *player_init()
{
    t_player *player;


    player = (t_player *)malloc(sizeof(t_player));
    player->pos.x = 22; // player start postion 
    player->pos.y = 12;
    player->posdir.x = -1; // player initial face direction
    player->posdir.y = 0;
    player->plane.x = 0;    // versjion of camera plane
    player->plane.y = 0.66;
    player->raydir.x = 0;  // ray direction
    player->raydir.y = 0;
    return (player);
}

t_mlx   *wolf3d_mlx_init()
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

t_combi *combi_init(t_player *player, t_mlx *mlx)
{
    t_combi     *combi;

    combi = (t_combi *)malloc(sizeof(t_combi));
    combi->player = player;
    combi->mlx = mlx;
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

void calc_ray(t_combi *c, int x)
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
    int color;

    hit = 0;
    cameraX = 2 * x / WIN_WIDTH - 1;
    c->player->raydir.x = c->player->posdir.x + c->player->plane.x * cameraX;
    c->player->raydir.y = c->player->posdir.y + c->player->plane.y * cameraX;
    c->map.x = (int)c->player->pos.x;
    c->map.y = (int)c->player->pos.y;


    deltaDist.x = (c->player->raydir.y == 0) ? 0 : ((c->player->raydir.x == 0) ? 1 : abs((int)(1 / c->player->raydir.x)));
    deltaDist.y = (c->player->raydir.x == 0) ? 0 : ((c->player->raydir.y == 0) ? 1 : abs((int)(1 / c->player->raydir.y)));

    if (rayDir.x < 0)
    {
        stepX = -1;
        sideDist.x = (player->pos.x - mapX) * deltaDist.x;
    }
    else
    {
        stepX = 1;
        sideDist.x = (mapX + 1.0 - player->pos.x) * deltaDist.x;
    }

    if (rayDir.y < 0)
    {
        stepY = -1;
        sideDist.y = (player->pos.y - mapY) * deltaDist.y;
    }
    else
    {
        stepY = 1;
        sideDist.y = (mapY + 1.0 - player->pos.y) * deltaDist.y;
    }

    while (hit == 0)
    {
        if (sideDist.x < sideDist.y)
        {
            sideDist.x = sideDist.x + deltaDist.x;
            mapX = mapX + stepX;
            side = 0;            
        }
        else
        {
            sideDist.y = sideDist.y + deltaDist.y;
            mapY = mapY + stepY;
            side = 1;
        }
        if (worldMap[mapX][mapY] > 0) hit = 1;        
    }

    if (side == 0)
        perWallDist = (mapX - player->pos.x + (1 - stepX) / 2) / rayDir.x;
    else
        perWallDist = (mapY - player->pos.y + (1 - stepY) / 2) / rayDir.y;
    
    lineHeight = (int)(WIN_HEIGHT / perWallDist); 

    drawStart = (WIN_HEIGHT / 2) - (lineHeight / 2);
    if (drawStart < 0) 
        drawStart = 0;
    drawEnd = (WIN_HEIGHT / 2) + (lineHeight / 2);
    if (drawEnd > WIN_HEIGHT)
        drawEnd = WIN_HEIGHT - 1;

    if (worldMap[mapX][mapY] == 1)
        color = COL_RED;
    else if (worldMap[mapX][mapY] == 2)
        color = COL_GREEN;
    else if (worldMap[mapX][mapY] == 3)
        color = COL_BLUE;
    else if (worldMap[mapX][mapY] == 4)
        color = COL_YELLOW;
    else
        color = COL_WHITE;

    draw_strip(x, drawStart, drawEnd, color, mlx);
}

void draw_map(t_combi *combi)
{
    int x;

    x = 0;
    while(x < WIN_WIDTH - 1)
    {
        calc_ray(combi->mlx, combi->player, x);
        x++;
    }
}



int main(int argc, char **argv)
{
    t_mlx       *mlx;
    t_player    *player;
    t_combi     *combi;
    char        *name;
    int         argc_count;
 

    argc_count = argc;
    name = argv[1];

    player = player_init();
    mlx = wolf3d_mlx_init();
    combi = combi_init(player, mlx);

//   mlx_hook(mlx->win_ptr, 2, 0, key_press, combi);
//	mlx_hook(mlx->win_ptr, 3, 0, key_release, combi);

    draw_map(combi);

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
//	mlx_loop_hook(mlx->mlx_ptr, movement, combi);
    mlx_loop(mlx->mlx_ptr);
    return (0);
}