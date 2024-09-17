/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:35:55 by zabdulza          #+#    #+#             */
/*   Updated: 2023/12/20 16:35:55 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* 
 * Splits the buffer containing the map data into the 2D map array. 
 * Counts the number of exits, players, and coins as it parses the buffer.
 * Stores the player position and initializes each row of the map with the respective data.
 */
static void	map_split2(t_main *main, int height, int width, char *buffer)
{
	int		y;
	int		x;

	y = 0;
	while (y < height)
	{
		x = 0;
		main->map->map[y] = ft_calloc((width + 1), sizeof(char));
		while (x < width)
		{
			if (buffer[(y * (width + 1) + x)] == 'E')
				main->exitcount++;
			else if (buffer[y * (width + 1) + x] == 'P')
			{
				main->playercount++;
				main->p_x = x;
				main->p_y = y;
			}
			else if (buffer[(y * (width + 1) + x)] == 'C')
				main->coincount++;
			main->map->map[y][x] = buffer[(y * (width + 1) + x)];
			x++;
		}
		main->map->map[y++][x] = '\0';
	}
}

/* 
 * Parses the buffer to determine the map's width and height, 
 * and then calls map_split2 to split the buffer into a 2D map array.
 */
static void	map_split(char *buffer, t_main *main)
{
	int		height;
	int		width;
	int		i;

	main->exitcount = 0;
	main->playercount = 0;
	main->coincount = 0;
	height = 0;
	i = 0;
	while (buffer[i] != 0)
		if (buffer[i++] == '\n')
			height++;
	if (buffer[i - 1] != '\n')
		height++;
	i = 0;
	while (buffer[i] != '\n' && buffer[i] && buffer[i] != EOF)
		i++;
	width = i;
	main->map->map = ft_calloc((height + 1), sizeof(char *));
	map_split2(main, height, width, buffer);
	main->map->x = width;
	main->map->y = height;
}

/* 
 * Reads the contents of the map file into a buffer, then calls map_split to process 
 * the buffer and initialize the map structure. Frees the buffer after processing.
 */
char	**map_init(char *path, t_main *main)
{
	char	*buffer;
	int		i;
	int		bytes;
	int		fd;

	buffer = ft_calloc(10000, sizeof(char));
	fd = open(path, O_RDONLY);
	i = 0;
	bytes = 1;
	buffer[0] = '\0';
	while (bytes)
	{
		bytes = read(fd, &buffer[i++], 1);
		if (bytes == -1)
			ft_destroy(main);
	}
	buffer[i] = '\0';
	map_split(buffer, main);
	free(buffer);
	close(fd);
	return (main->map->map);
}
