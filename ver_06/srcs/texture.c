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

void	load_texture(t_mlx *mlx, t_combi *c)
{
	int			i;
	int			tex_w;
	int			tex_h;
	t_teximg	*teximg[NUM_TEXTURE];
	char		*texname[NUM_TEXTURE] = {"textures/brick.xpm", "textures/wood.xpm",\
									"textures/metal.xpm", "textures/stone.xpm",\
									"textures/grass.xpm", "textures/ceiling.xpm",\
									"textures/floor.xpm"};

	i = 0;
	while (i < NUM_TEXTURE)
	{
		teximg[i] = (t_teximg *)malloc(sizeof(t_teximg));
		teximg[i]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, texname[i], &tex_w, &tex_h);
		teximg[i]->data_addr = mlx_get_data_addr(teximg[i]->img_ptr, &teximg[i]->bits_per_piexl, &teximg[i]->size_line,
				&teximg[i]->endian);
		teximg[i]->height = tex_h;
		teximg[i]->width = tex_w;
		c->teximg[i] = teximg[i];
		i++;
	}
}
