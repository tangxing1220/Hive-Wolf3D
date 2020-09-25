/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:33:43 by xtang             #+#    #+#             */
/*   Updated: 2020/09/21 15:32:35 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

/*
**	To load texture image into image array by mlx_xmp_file_to_image() function.
**	In order to obey norminette, I use static value here.
*/

void	load_texture(t_mlx *mlx, t_combi *c)
{
	int				i;
	int				tex_w;
	int				tex_h;
	t_teximg		*teximg[NUM_TEXTURE];
	static char		*texname[NUM_TEXTURE] = {"textures/floor.xpm",\
		"textures/brick.xpm", "textures/wood.xpm", "textures/stone.xpm",\
		"textures/grass.xpm", "textures/metal.xpm", "textures/w3d.xpm",\
		"textures/ceiling.xpm", "textures/lightning.xpm"};

	i = 0;
	while (i < NUM_TEXTURE)
	{
		teximg[i] = (t_teximg *)malloc(sizeof(t_teximg));
		teximg[i]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, texname[i],\
						&tex_w, &tex_h);
		teximg[i]->data_addr = mlx_get_data_addr(teximg[i]->img_ptr,\
			&teximg[i]->bpp, &teximg[i]->sl, &teximg[i]->endian);
		teximg[i]->h = tex_h;
		teximg[i]->w = tex_w;
		c->teximg[i] = teximg[i];
		i++;
	}
}
