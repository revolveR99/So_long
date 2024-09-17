/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:35:14 by zabdulza          #+#    #+#             */
/*   Updated: 2023/12/21 17:09:01 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h> 	/* open */
# include <stdio.h> 	/* perror */
# include <errno.h> 	/* errno */
# include <stdlib.h> 	/* exit */
# include <unistd.h> 	/* write, access */

# ifdef __APPLE__
#  include "../minilibx-mac/mlx.h"
#  define S_DOWN 1
#  define D_RIGHT 2
#  define W_UP 13
#  define A_LEFT 0
#  define ESC 53
# endif
# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
#  define W_UP 119
#  define A_LEFT 97
#  define S_DOWN 115
#  define D_RIGHT 100
#  define ESC 65307
# endif

# define PIXEL 64

typedef struct s_img
{
	void			*wall;
	void			*way;
	void			*coin;
	void			*exitd;
	void			*enemy;
	void			*pr;
	void			*pl;
	void			*ple;
	void			*pu;
	void			*pd;
}					t_img;

typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
}					t_map;

typedef struct s_main
{
	void			*mlx;
	void			*win;
	int				p_x;
	int				p_y;
	int				coincount;
	int				movecount;
	int				playercount;
	int				exitcount;
	int				tmp;
	int				exitflag;
	t_map			*map;
	t_img			*img;
}					t_main;

t_main				*main_init(char *path);
char				**map_init(char *path, t_main *main);
void				ft_map_check(t_main *main);
void				drawing_themap(t_main *main);
void				xpm_to_img(t_main *main);
int					key_event(int key, t_main *main);
int					render(t_main *main);
void				count_movement(t_main *main);
void				ft_error(char *errorcode, t_main *main);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_itoa(int n);
int					ft_destroy(t_main *main);

#endif
