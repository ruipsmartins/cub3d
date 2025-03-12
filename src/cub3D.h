/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/12 14:22:05 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define BLOCK 64
# define DEBUG 1

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;

	void		*img;
	int			img_width;
	int			img_height;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;

	char		**map;
	char		**map_copy;

	void		*img_wall;
	void		*img_background;
	int			img_width;
	int			img_height;
	
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char 		*color_floor;
	char		*color_ceiling;
	
	
}				t_game;

void			init_game(t_game *game);
void			init_player(t_player *player);
void			clean_game(t_game *game);

void			img_draw(t_game *game, void *image, int x, int y);

void			draw_map(t_game *game);

int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			move_player(t_player *player, t_game *game);

char			**open_map(char *path);
void			free_map(t_game *game);

void			get_textures(t_game *game);
void	get_rgb(t_game *game);
void	copy_map(t_game *game);

#endif