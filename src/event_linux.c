/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:35:27 by zabdulza          #+#    #+#             */
/*   Updated: 2023/12/20 16:35:27 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// Function: write_move_cnt
// Purpose: Display the current move count to the console.
static void	write_move_cnt(int cnt)
{
	char	*move;

	move = ft_itoa(cnt);
	write(1, "Move count: ", 12);
	write(1, move, ft_strlen(move));
	write(1, "\n", 1);
	free(move);
}
// static void	write_move_cnt(int cnt)
// {
// 	char	*move;
// 	move = ft_itoa(cnt); Convert move count to string
// 	write(1, "Move count: ", 12); Write label to console
// 	write(1, move, ft_strlen(move));  Write move count to console
// 	write(1, "\n", 1); Write newline to console
// 	free(move); Free allocated memory
// }

// Function: check_esc
// Purpose: Check for escape key or collision with enemy/coin,
//take corresponding action.
static int	check_esc(t_main *main, int key)
{
	if (key == ESC)
		ft_destroy(main);
	if (main->map->map[main->p_y][main->p_x] == 'X')
	{
		ft_destroy(main);
	}
	if (main->map->map[main->p_y][main->p_x] == 'C')
	{
		main->map->map[main->p_y][main->p_x] = '0';
		main->coincount--;
	}
	return (0);
}

// static int	check_esc(t_main *main, int key)
// {
// 	if (key == ESC) If escape key is pressed
// 		ft_destroy(main); Destroy the game
// 	if (main->map->map[main->p_y][main->p_x] == 'X') If collided with enemy
// 	{
// 		ft_destroy(main); Destroy the game
// 	}
// 	if (main->map->map[main->p_y][main->p_x] == 'C') If collided with coin
// 	{
// 		main->map->map[main->p_y][main->p_x] = '0'; Remove coin from the map
// 		main->coincount--; Decrement coin count
// 	}
// 	return (0);
// }

// Function: key_event
// Purpose: Handle keyboard events 
//(movement and check for escape or collisions).
int	key_event(int key, t_main *main)
{
	if (key == W_UP && main->map->map[main->p_y - 1][main->p_x] != '1')
	{
		main->p_y--;
		main->img->pl = main->img->pu;
		write_move_cnt(++(main->movecount));
	}
	else if (key == A_LEFT && main->map->map[main->p_y][main->p_x - 1] != '1')
	{
		main->img->pl = main->img->ple;
		main->p_x--;
		write_move_cnt(++(main->movecount));
	}
	else if (key == S_DOWN && main->map->map[main->p_y + 1][main->p_x] != '1')
	{
		main->img->pl = main->img->pd;
		main->p_y++;
		write_move_cnt(++(main->movecount));
	}
	else if (key == D_RIGHT && main->map->map[main->p_y][main->p_x + 1] != '1')
	{
		main->img->pl = main->img->pr;
		main->p_x++;
		write_move_cnt(++(main->movecount));
	}
	return (check_esc(main, key));
}
// int	key_event(int key, t_main *main)
// {
// 	if (key == W_UP && main->map->map[main->p_y - 1][main->p_x] != '1')
// 	{
// 		main->p_y--; Move up
// 		main->img->pl = main->img->pu; Change player image
// 		write_move_cnt(++(main->movecount)); Write move count to console
// 	}
// 	else if (key == A_LEFT && main->map->map[main->p_y][main->p_x - 1] != '1')
// 	{
// 		main->img->pl = main->img->ple;
// 		main->p_x--;
// 		write_move_cnt(++(main->movecount));
// 	}
// 	else if (key == S_DOWN && main->map->map[main->p_y + 1][main->p_x] != '1')
// 	{
// 		main->img->pl = main->img->pd;
// 		main->p_y++;
// 		write_move_cnt(++(main->movecount));
// 	}
// 	else if (key == D_RIGHT && main->map->map[main->p_y][main->p_x + 1] != '1')
// 	{
// 		main->img->pl = main->img->pr;
// 		main->p_x++;
// 		write_move_cnt(++(main->movecount));  
// 	}
// 	return (check_esc(main, key)); Check for escape or collisions
// }

// Function: ft_destroy
// Purpose: Clean up resources and exit the game.
int	ft_destroy(t_main *main)
{
	int	y;

	mlx_destroy_image(main->mlx, main->img->ple);
	mlx_destroy_image(main->mlx, main->img->pr);
	mlx_destroy_image(main->mlx, main->img->pu);
	mlx_destroy_image(main->mlx, main->img->pd);
	mlx_destroy_image(main->mlx, main->img->wall);
	mlx_destroy_image(main->mlx, main->img->way);
	mlx_destroy_image(main->mlx, main->img->exitd);
	mlx_destroy_image(main->mlx, main->img->enemy);
	mlx_destroy_image(main->mlx, main->img->coin);
	mlx_destroy_window(main->mlx, main->win);
	mlx_destroy_display(main->mlx);
	y = 0;
	while (y < main->map->y)
		free(main->map->map[y++]);
	free(main->map->map);
	free(main->img);
	free(main->map);
	free(main->mlx);
	free(main);
	exit(0);
	return (0);
}
// int ft_destroy(t_main *main) {
//     Destroy images and window
//     mlx_destroy_image(main->mlx, main->img->ple);
//     // ... (similar destroy calls for other images)
//     mlx_destroy_window(main->mlx, main->win);
//     mlx_destroy_display(main->mlx);
//    Free memory allocated for map
//     int y = 0;
//     while (y < main->map->y)
//         free(main->map->map[y++]);
//     free(main->map->map);
//     Free allocated memory for structs and exit the program
//     free(main->img);
//     free(main->map);
//     free(main->mlx);
//     free(main);
//     exit(0); // Exit the program
//     return (0);
// }
