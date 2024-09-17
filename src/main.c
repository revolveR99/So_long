/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:35:44 by zabdulza          #+#    #+#             */
/*   Updated: 2023/12/20 16:35:44 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* 
 * Displays an error message (errorcode) to stderr, destroys the main struct if it exists, 
 * and exits the program with a failure status (errno 2).
 */
void	ft_error(char *errorcode, t_main *main)
{
	errno = 2;
	while (*errorcode)
		write(2, errorcode++, 1);
	write(2, "\n", 1);
	if (main)
		ft_destroy(main);
	exit(1);
}

/* 
 * Loads images from XPM files and assigns them to the corresponding fields in the main structure. 
 * If any image fails to load, the program calls ft_error to exit.
 */
void	xpm_to_img(t_main *main)
{
	main->img->pr = mlx_xpm_file_to_image(
			main->mlx, "./img/right.xpm", &main->tmp, &main->tmp);
	main->img->pl = main->img->pr;
	main->img->ple = mlx_xpm_file_to_image(
			main->mlx, "./img/left.xpm", &main->tmp, &main->tmp);
	main->img->pu = mlx_xpm_file_to_image(
			main->mlx, "./img/up.xpm", &main->tmp, &main->tmp);
	main->img->pd = mlx_xpm_file_to_image(
			main->mlx, "./img/down.xpm", &main->tmp, &main->tmp);
	main->img->way = mlx_xpm_file_to_image(
			main->mlx, "./img/way.xpm", &main->tmp, &main->tmp);
	main->img->wall = mlx_xpm_file_to_image(
			main->mlx, "./img/wall.xpm", &main->tmp, &main->tmp);
	main->img->exitd = mlx_xpm_file_to_image(
			main->mlx, "./img/exit.xpm", &main->tmp, &main->tmp);
	main->img->enemy = mlx_xpm_file_to_image(
			main->mlx, "./img/enemy.xpm", &main->tmp, &main->tmp);
	main->img->coin = mlx_xpm_file_to_image(
			main->mlx, "./img/coin.xpm", &main->tmp, &main->tmp);
	if (main->img->pr == NULL || main->img->ple == NULL
		|| main->img->wall == NULL || main->img->pd == NULL
		|| main->img->way == NULL || main->img->pu == NULL
		|| main->img->exitd == NULL || main->img->coin == NULL
		|| main->img->pl == NULL)
		ft_error("Error\nImage initialization failed", main);
}

/* 
 * Initializes the main structure, allocates memory for map and image structures, 
 * initializes the mlx environment, and creates a new window. 
 * Calls functions to load images and initialize the map.
 */
t_main	*main_init(char *path)
{
	t_main	*main;

	main = ft_calloc(1, sizeof(t_main));
	main->map = ft_calloc(1, sizeof(t_map));
	main->img = ft_calloc(1, sizeof(t_img));
	main->coincount = 0;
	main->movecount = 0;
	main->map->map = map_init(path, main);
	main->mlx = mlx_init();
	if (main->mlx == NULL)
		ft_error("Error\nMlx initialization failed", main);
	xpm_to_img(main);
	main->win = mlx_new_window(main->mlx,
			main->map->x * PIXEL, main->map->y * PIXEL, "so_long");
	return (main);
}

/* 
 * Checks if all necessary image files exist and are readable. 
 * If any file is missing or unreadable, the program exits with an error message.
 */
void	check_files(void)
{
	if (access("img/wall.xpm", F_OK | R_OK) == -1
		|| access("img/way.xpm", F_OK | R_OK) == -1
		|| access("img/coin.xpm", F_OK | R_OK) == -1
		|| access("img/left.xpm", F_OK | R_OK) == -1
		|| access("img/right.xpm", F_OK | R_OK) == -1
		|| access("img/up.xpm", F_OK | R_OK) == -1
		|| access("img/down.xpm", F_OK | R_OK) == -1
		|| access("img/enemy.xpm", F_OK | R_OK) == -1
		|| access("img/exit.xpm", F_OK | R_OK) == -1)
	{
		errno = 2;
		perror("Error\nFailed reading image file");
		exit(1);
	}
}

/* 
 * Main entry point of the program. 
 * Validates the command-line arguments and checks the map file and image files.
 * Initializes the main structure, checks the map, draws the map, and sets up hooks for key events and rendering.
 */
int	main(int argc, char **argv)
{
	t_main		*main;

	if (argc != 2 || access(argv[1], F_OK | R_OK) == -1
		|| !ft_strncmp(argv[1] + ft_strlen(argv[1]) - 5, ".ber", 4))
	{
		errno = 2;
		perror("Error\nUsage: ./so_long maps/map.ber\n wrong map (.ber) file");
		exit(1);
	}
	check_files();
	main = main_init(argv[1]);
	ft_map_check(main);
	drawing_themap(main);
	mlx_hook(main->win, 2, 1, key_event, main);
	mlx_hook(main->win, 17, 0, ft_destroy, main);
	mlx_loop_hook(main->mlx, render, main);
	mlx_loop(main->mlx);
	return (0);
}

