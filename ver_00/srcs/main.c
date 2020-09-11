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
    player->dir.x = -1; // player initial face direction
    player->dir.y = 0;
    player->plane.x = 0;    // versjion of camera plane
    player->plane.y = 0.66;
    return (player);
}

t_mlx   *mlx_init()
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

void calc_ray(t_mlx *mlx, t_player *player, int x)
{
    double cameraX;

    cameraX = 2 * x / WIN_WIDTH - 1;
     
}

int main(int argc, char **argv)
{
    t_mlx       *mlx;
    t_player    *player;
    int         x;    

/*
    if (argc == 2)
    {
        if(ft_strcmp(argv[1], "maps/map_1") != 0 ||\
                ft_strcmp(argv[1], "maps/map_2") != 0 ||\
                ft_strcmp(argv[1], "maps/map_3") != 0)
        {
            print_usage();
            return (0);
        }
        read_map(argv[1]); 

    
    }
    else
        print_usage();
 */
    x = 0;
    player = player_init();
    mlx = mlx_init();
    while(x < WIN_WIDTH - 1)
    {
        calc_ray(mlx, player, x);


        x++;
    }

    return (0);
}