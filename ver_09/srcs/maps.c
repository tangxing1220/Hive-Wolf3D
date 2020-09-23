/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:58:07 by xtang             #+#    #+#             */
/*   Updated: 2020/09/21 15:26:03 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

/*
**	get_next_line has malloc(), ft_strsplit() has malloc();
**	release them to avoid memoey leak.
*/

void	free_split_arr(char **arr, char *line)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	free(line);
}

/*
**	I load the map into 2D integer array because we know already the map.
**	There is no map checking since we know already the map. I apply to
**	get_net_line() and ft_strsplit() functions to read map line by line
**	and identify the values. last free the assigned the memory.
*/

int		**load_map(char *filename)
{
	int			fd;
	t_vector	map;
	char		*line;
	char		**line_arr;
	int			**worldmap;

	fd = open(filename, O_RDONLY);
	worldmap = (int **)malloc(sizeof(int *) * MAP_H);
	map.y = 0;
	while (map.y < MAP_H)
	{
		worldmap[map.y] = (int *)malloc(sizeof(int) * MAP_W);
		get_next_line(fd, &line);
		line_arr = ft_strsplit(line, ' ');
		map.x = 0;
		while (map.x < MAP_W)
		{
			worldmap[map.y][map.x] = ft_atoi(line_arr[map.x]);
			map.x++;
		}
		free_split_arr(line_arr, line);
		map.y++;
	}
	close(fd);
	return (worldmap);
}
