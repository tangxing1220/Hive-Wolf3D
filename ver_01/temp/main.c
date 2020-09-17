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

void    load_map(int map[MAP_HEIGHT][MAP_WIDTH])
{
    int fd;
    int x;
    int y;
    char *line;
    char **line_arr;
    char *filename;

    filename = "maps/map1.txt";

    fd = open(filename, O_RDONLY);
    y = 0;
    while (y < MAP_HEIGHT)
    {
        get_next_line(fd, &line);
        line_arr = ft_strsplit(line, ' ');
        x = 0;
        while(x < MAP_WIDTH)
        {
            map[y][x] = ft_atoi(line_arr[x]);
            x++;
        }
        free(line);
        free_split_arr(line_arr);
        y++;
    }
    close(fd);
}

int main(void)
{
    int map[MAP_HEIGHT][MAP_WIDTH];

    load_map(map);
    printf( "ok!\n");
    return (0);
}