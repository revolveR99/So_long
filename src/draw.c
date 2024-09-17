/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:35:15 by zabdulza          #+#    #+#             */
/*   Updated: 2023/12/20 16:35:15 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// Displaying Game Information:
// The count_movement function is used to 
// display information about movement counts, coin counts,
// and exit instructions on the game window.

void	count_movement(t_main *main)
{
	char	*s1;
	char	*s2;
	char	*dz;
	int		z;

	z = 0xFFFF00;
	mlx_string_put(main->mlx, main->win, PIXEL * 2, PIXEL / 2, z, "MOVEMENT :");
	if (main->movecount == 0)
		mlx_string_put(main->mlx, main->win, PIXEL * 3, PIXEL / 2, z, "0");
	s1 = ft_itoa(main->movecount);
	mlx_string_put(main->mlx, main->win, PIXEL * 3, PIXEL / 2, z, s1);
	mlx_string_put(main->mlx, main->win, (PIXEL * 4), PIXEL / 2, z, "APPLE:");
	s2 = ft_itoa(main->coincount);
	mlx_string_put(main->mlx, main->win, PIXEL * 5, PIXEL / 2, z, s2);
	dz = "CLICK X (in the upper right corner) OR ESC BUTTONS FOR EXITING";
	mlx_string_put(main->mlx, main->win, PIXEL * 8, PIXEL / 2, z, dz);
	free(s1);
	free(s2);
}

// void	count_movement(t_main *main)
// {
// 	char	*s1; --movecount
// 	char	*s2; --coincount
// 	char	*dz; --Pointer to a constant string
// 	int		z; Color value
// 	z = 0xFFFF00; Setting color value to a yellowish shade
// 	Displaying "MOVEMENT :" at a specific position on the window
// 	mlx_string_put(main->mlx, main->win, PIXEL * 2, PIXEL / 2, z, "MOVEMENT :");
// 	If the move count is zero, display "0" at a specified position
// 	if (main->movecount == 0)
// 		mlx_string_put(main->mlx, main->win, PIXEL * 3, PIXEL / 2, z, "0");
// 	Convert main->movecount to a string and display it at a specific position
// 	s1 = ft_itoa(main->movecount);
// 	mlx_string_put(main->mlx, main->win, PIXEL * 3, PIXEL / 2, z, s1);
// 	Displaying "APPLE:" at a specific position on the window
// 	mlx_string_put(main->mlx, main->win, (PIXEL * 4), PIXEL / 2, z, "APPLE:");
// 	Convert main->coincount to a string and display it at a specific position
// 	s2 = ft_itoa(main->coincount);
// 	mlx_string_put(main->mlx, main->win, PIXEL * 5, PIXEL / 2, z, s2);
// 	A constant string to be displayed at a specific position on the window
// 	dz = "CLICK X (in the upper right corner) OR ESC BUTTONS FOR EXITING";
// 	mlx_string_put(main->mlx, main->win, PIXEL * 8, PIXEL / 2, z, dz);
// 	Freeing the allocated memory for the string representations
// 	free(s1);
// 	free(s2);
// }

// Rendering Game Elements:
// The draw_map2 function is responsible for 
// rendering different images onto the game window 
// based on characters present in the map. 
// It uses specific images (main->img->wall, main->img->way, etc.) 
// to represent different elements 
// of the game (e.g., walls, paths, player, coins, enemies) 
// based on the characters in the map data.

static int	draw_map2(t_main *main, int y, int x)
{
	if (main->map->map[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win,
			main->img->wall, x, y);
	else if (main->map->map[y][x] == '0')
		mlx_put_image_to_window(main->mlx, main->win,
			main->img->way, x, y);
	else if (main->map->map[y][x] == 'P')
	{
		mlx_put_image_to_window(main->mlx, main->win, main->img->pl, x, y);
		main->p_y = y;
		main->p_x = x;
	}
	else if (main->map->map[y][x] == 'E')
		mlx_put_image_to_window(main->mlx, main->win, main->img->exitd, x, y);
	else if (main->map->map[y][x] == 'C')
		mlx_put_image_to_window(main->mlx, main->win, main->img->coin, x, y);
	else if (main->map->map[y][x] == 'X')
		mlx_put_image_to_window(main->mlx, main->win, main->img->enemy, x, y);
	else if (main->map->map[y][x] != '\n')
		ft_error("Error\nIncorrect character inside the Map file", main);
	x++;
	return (x);
}

// static int draw_map2(t_main *main, int y, int x) 
// {
//  Drawing different images based on characters in the map
//     if (main->map->map[y][x] == '1')
//     Drawing a wall image at position (x, y)
//         mlx_put_image_to_window(main->mlx, main->win, main->img->wall, x, y);
//     else if (main->map->map[y][x] == '0')
//     Drawing a way image at position (x, y)
//         mlx_put_image_to_window(main->mlx, main->win, main->img->way, x, y);
//     else if (main->map->map[y][x] == 'P') {
// Drawing a player image at position (x, y) and updating player's position
//         mlx_put_image_to_window(main->mlx, main->win, main->img->pl, x, y);
//         main->p_y = y; Updating player's y-coordinate
//         main->p_x = x; Updating player's x-coordinate
//     }
//... (similar conditional blocks for other map characters)
//     else if (main->map->map[y][x] != '\n')
//ft_error("Error\nWrong character in Map file", main); 
// Error handling for unexpected characters    
//     x++;  Move to the next column in the map
//     return (x);  Return the updated x-coordinate
// }

// The draw_map function seems to handle rendering the game map 
// by placing different images corresponding to 
// different elements in the map file.

void	drawing_themap(t_main *main)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < (main->map->y))
	{
		while (x < (main->map->x))
			x = draw_map2(main, y, x);
		y++;
		x = 0;
	}
}

//Function: draw_map
//Purpose: Draw the game map by placing images based on map elements.
// void draw_map(t_main *main) {
//     int y = 0; Initialize y-coordinate
//     int x = 0; Initialize x-coordinate
//     while (y < (main->map->y)) {  Loop through map rows
//         while (x < (main->map->x)) Loop through map columns
//             x = draw_map2(main, y, x); Draw images based on map characters
//         y++; Move to the next row
//         x = 0;  Reset x-coordinate for the next row
//     }
// }
