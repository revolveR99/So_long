/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:35:49 by zabdulza          #+#    #+#             */
/*   Updated: 2024/09/17 13:14:54 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* 
 * Recursively checks the map for valid paths using flood fill algorithm. 
 * Marks the visited paths and checks if all coins and exits are reachable. 
 * If a coin is found, decrements the count. If an exit is found, sets the exitflag to true.
 */
static void	ft_floodfill(t_main *main, int x, int y, int *count_c)
{
	if (x <= 0 || x >= main->map->x || y <= 0 || y >= main->map->y
		|| main->map->map[y][x] == '1' || main->map->map[y][x] == 'c'
		|| main->map->map[y][x] == 'o' || main->map->map[y][x] == 'e'
		|| main->map->map[y][x] == 'E' || main->map->map[y][x] == 'X')
	{
		if (main->map->map[y][x] == 'E')
			main->exitflag = 1;
		return ;
	}
	if (main->map->map[y][x] == 'C')
	{
		(*count_c)--;
		main->map->map[y][x] = 'c';
	}
	else if (main->map->map[y][x] == '0')
		main->map->map[y][x] = 'o';
	ft_floodfill(main, x, (y + 1), count_c);
	ft_floodfill(main, x, (y - 1), count_c);
	ft_floodfill(main, (x + 1), y, count_c);
	ft_floodfill(main, (x - 1), y, count_c);
}

/* 
 * Restores the map to its original state after the flood fill algorithm. 
 * Converts all temporary marks ('c', 'e', 'o') back to their original values.
 */
static void	ft_restore(t_main *main)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < main->map->y)
	{
		x = 0;
		while (x < main->map->x)
		{
			if (main->map->map[y][x] == 'c')
				main->map->map[y][x] = 'C';
			else if (main->map->map[y][x] == 'e')
				main->map->map[y][x] = 'E';
			else if (main->map->map[y][x] == 'o')
				main->map->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

/* 
 * Checks the map to ensure that all coins are accessible and that there is a valid path to the exit. 
 * Uses the flood fill algorithm to verify pathfinding, and if any check fails, exits the program with an error.
 */
static void	ft_check_valid_map_path(t_main *main)
{
	int	count_c;

	count_c = main->coincount;
	ft_floodfill(main, main->p_x, main->p_y, &count_c);
	if (count_c != 0)
		ft_error("Error\nNo valid Path, access to Coin is blocked", main);
	ft_restore(main);
	if (main->exitflag == 0)
		ft_error("Error\nNo valid Path, access to Exit is blocked", main);
	return ;
}

/* 
 * Checks the integrity of the map, ensuring there is exactly one player, at least one exit and coin, 
 * and that all borders of the map are surrounded by walls ('1'). 
 * Calls a function to validate that all important elements are reachable.
 */
void	ft_map_check(t_main *main)
{
	int	i;

	if (main->exitcount < 1)
		ft_error("Error\nExit not found", main);
	else if (main->coincount < 1)
		ft_error("Error\nCoin not found", main);
	else if (main->playercount < 1 || main->playercount > 1)
		ft_error("Error\nPlayer not found or more than one", main);
	i = -1;
	while (++i < main->map->y - 1)
	{
		if (main->map->map[i][0] != '1')
			ft_error("Error\nMAP: (LEFT) border of wall", main);
		else if (main->map->map[i][main->map->x - 1] != '1')
			ft_error("Error\nMAP: (RIGHT) border of wall", main);
	}
	i = -1;
	while (++i < main->map->x)
	{
		if (main->map->map[0][i] != '1')
			ft_error("Error\nMAP: (UP) border of wall", main);
		if (main->map->map[main->map->y - 1][i] != '1')
			ft_error("Error\nMAP: (DOWN) border of wall", main);
	}
	ft_check_valid_map_path(main);
}

