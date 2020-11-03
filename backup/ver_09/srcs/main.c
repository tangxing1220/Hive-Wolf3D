/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:11:36 by xtang             #+#    #+#             */
/*   Updated: 2020/09/21 19:33:09 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

/*
**	Print out the usege info if the input arguments aren't appropriate.
*/

void		print_usage(void)
{
	ft_putstr_fd("usage: ", STDERR_FILENO);
	ft_putstr_fd("./wolf3D [map]\n", STDERR_FILENO);
	ft_putstr_fd("map: maps/map1.txt\tmaps/map2.txt\n", STDERR_FILENO);
}

/*
**	I call the player as camera or eye also. It includes the coordinate of
**	player star point, the vector of original direction, the camera plane vector
**	and ray direction vector. For plane plan x = 0, y = 0.66, it means the Field
**	of vision (FOV) is 66 degree.
*/

t_player	*player_init(void)
{
	t_player *ply;

	ply = (t_player *)malloc(sizeof(t_player));
	ply->pos.x = 19;
	ply->pos.y = 18;
	ply->pdir.x = 1;
	ply->pdir.y = 0;
	ply->flt.x = 0;
	ply->flt.y = 0.66;
	ply->raydir.x = 0;
	ply->raydir.y = 0;
	return (ply);
}

/*
**	The mlx image is initialized here.
*/

t_mlx		*wolf3d_mlx_init(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W_WIDTH, W_HEIGHT, "WOLF3D");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, W_WIDTH, W_HEIGHT);
	mlx->data_addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,\
			&mlx->sl, &mlx->endian);
	return (mlx);
}

/*
**	There is only one argument to pass through into mlx event function. I create
**	this combi struct to include all necessary data.
*/

t_combi		*combi_init(int **worldmap, t_player *ply, t_mlx *mlx)
{
	t_combi	*combi;

	combi = (t_combi *)malloc(sizeof(t_combi));
	combi->ply = ply;
	combi->mlx = mlx;
	combi->worldmap = worldmap;
	combi->move.forwd = 0;
	combi->move.backwd = 0;
	combi->move.right = 0;
	combi->move.left = 0;
	combi->map.x = 0;
	combi->map.y = 0;
	return (combi);
}

/*
**	I learn ray casting from the following tutorial
**	https://lodev.org/cgtutor/raycasting.html
*/

int			main(int argc, char **argv)
{
	int			**worldmap;
	t_player	*ply;
	t_mlx		*mlx;
	t_combi		*combi;

	if (argc == 2)
	{
		worldmap = load_map(argv[1]);
		ply = player_init();
		mlx = wolf3d_mlx_init();
		combi = combi_init(worldmap, ply, mlx);
		load_texture(mlx, combi);
		mlx_hook(mlx->win_ptr, 2, 0, key_press, combi);
		mlx_hook(mlx->win_ptr, 3, 0, key_release, combi);
		draw_map(combi);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
		mlx_loop_hook(mlx->mlx_ptr, movement, combi);
		mlx_loop(mlx->mlx_ptr);
	}
	else
		print_usage();
	return (0);
}
