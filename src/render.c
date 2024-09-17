/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:36:02 by zabdulza          #+#    #+#             */
/*   Updated: 2023/12/20 16:36:02 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// Render2
// Purpose: Renders individual elements of the game 
// map based on the content of the map grid.
// Parameters:
// main: Pointer to the main structure containing 
// game-related information.
// y: Integer representing the current row index in the map.
// Process:
// Iterates through each cell in the specified row (y) of the map grid.
// Renders different game 
// elements (walls, paths, exits, coins, enemies, or default way) 
// based on the content of the map at the given position.

static void	render2(t_main *main, int y)
{
	int	x;

	x = -1;
	while (++x < main->map->x)
	{
		if (main->map->map[y][x] == '1')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->wall, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == '0' || main->map->map[y][x] == 'P')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->way, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == 'E')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->exitd, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == 'C')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->coin, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == 'X' && (main->p_x + main->p_y) % 3)
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->enemy, x * PIXEL, y * PIXEL);
		else
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->way, x * PIXEL, y * PIXEL);
	}
}
// static void	render2(t_main *main, int y)
// {
// 	int	x;

// 	x = -1;
// 	while (++x < main->map->x)
// 	{
// --Checking the map content at position [y][x]
// 		if (main->map->map[y][x] == '1')
// --If the content is '1', place wall image at 
// --position (x, y) in the window
// 			mlx_put_image_to_window(main->mlx, main->win,
// 				main->img->wall, x * PIXEL, y * PIXEL);
// 		else if (main->map->map[y][x] == '0' || main->map->map[y][x] == 'P')
// --If the content is '0' or 'P', place way image at 
// position (x, y) in the window			
// 			mlx_put_image_to_window(main->mlx, main->win,
// 				main->img->way, x * PIXEL, y * PIXEL);
// 		else if (main->map->map[y][x] == 'E')
// --If the content is 'E', place exit image at 
// position (x, y) in the window
// 			mlx_put_image_to_window(main->mlx, main->win,
// 				main->img->exitd, x * PIXEL, y * PIXEL);
// 		else if (main->map->map[y][x] == 'C')
// --If the content is 'C', place coin image at position 
// (x, y) in the window
// 			mlx_put_image_to_window(main->mlx, main->win,
// 				main->img->coin, x * PIXEL, y * PIXEL);
// 		else if (main->map->map[y][x] == 'X' && (main->p_x + main->p_y) % 3)
// --If the content is 'X' and a condition 
// based on player position is met, 
// place enemy image at (x, y) in the window
// 			mlx_put_image_to_window(main->mlx, main->win,
// 				main->img->enemy, x * PIXEL, y * PIXEL);
// 		else
// --If none of the above conditions are met, 
// place way image at (x, y) in the window
// 			mlx_put_image_to_window(main->mlx, main->win,
// 				main->img->way, x * PIXEL, y * PIXEL);
// 	}
// }

// Render
// Purpose: Manages the rendering of the entire game scene.
// Parameters:
// main: Pointer to the main structure containing 
// game-related information.
// Process:
// Iterates through each row of the map and calls 
// render2 to render the elements in that row.
// Places the player's image at its current position on 
// the game window.
// Checks win or lose conditions:
// If all coins are collected and the player is at the exit, 
// it calls ft_destroy to end the game.
// If conditions are not met, it calls count_movement to 
// continue the game and count movements.

int	render(t_main *main)
{
	int	y;

	y = 0;
	while (y < main->map->y)
	{
		render2(main, y);
		y++;
	}
	mlx_put_image_to_window(main->mlx, main->win, main->img->pl,
		(main->p_x) * PIXEL, (main->p_y) * PIXEL);
	if (main->coincount == 0
		&& main->map->map[main->p_y][main->p_x] == 'E')
		ft_destroy(main);
	else
		count_movement(main);
	return (0);
}

// int	render(t_main *main)
// {
// 	int	y;

// 	y = 0;
// 	while (y < main->map->y)
// 	{
// --// Render each row using render2 function, 
// passing the main structure and the current row index (y)
// 		render2(main, y);
// 		y++;
// 	}
// --Place player image at player's current position in the window
// 	mlx_put_image_to_window(main->mlx, main->win, main->img->pl,
// 		(main->p_x) * PIXEL, (main->p_y) * PIXEL);
// --Check conditions for winning or losing the game
// 	if (main->coincount == 0
// 		&& main->map->map[main->p_y][main->p_x] == 'E')
// 		ft_destroy(main);
// --If all coins are collected and the player is at the exit,
//  destroy the game
// 	else
// 		count_movement(main);
// --If conditions are not met, continue the game and count movements
// 	return (0);
// }
