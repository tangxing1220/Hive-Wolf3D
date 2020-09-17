/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:58:07 by xtang             #+#    #+#             */
/*   Updated: 2020/09/17 17:58:10 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/wolf3d.h"

void    free_split_arr(char **arr)
{
    int i;
    
    i = 0;
    while(arr[i] != NULL)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int     ** load_map(char *filename)
{
    int fd;
    int x;
    int y;
    char *line;
    char **line_arr;
    int  **worldMap;

    fd = open(filename, O_RDONLY);
    worldMap = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
    y = 0;
    while (y < MAP_HEIGHT)
    {
        worldMap[y] = (int *)malloc(sizeof(int) * MAP_WIDTH); 
        get_next_line(fd, &line);
        line_arr = ft_strsplit(line, ' ');
        x = 0;
        while(x < MAP_WIDTH)
        {
            worldMap[y][x] = ft_atoi(line_arr[x]);
            x++;
        }
        free(line);
        free_split_arr(line_arr);
        y++;
    }
    close(fd);
    return (worldMap);
}
