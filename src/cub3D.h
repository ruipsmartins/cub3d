/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/21 14:51:18 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define BLOCK 64
# define DEBUG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PLAYER_RADIUS 5  // Define um raio para o jogador


# define PI 3.14159265359

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
#include <sys/time.h>

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


typedef struct s_img
{
	void		*img;
	char		*pixel_buffer; // Buffer de píxeis da imagem
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}	t_img;

typedef struct s_textures
{
	t_img		wall_N;
	t_img		wall_S;
	t_img		wall_E;
	t_img		wall_W;
	t_img		floor;
	t_img		ceiling; 
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_img		screen_img;
	t_img		img_wall;

	/* int			img_width;
	int			img_height;
	char		*pixel_buffer;
	int			bpp;
	int			size_line;
	int			endian; */

	char		**map;
	char		**map_copy;

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
// utils
void			draw_square(int x, int y, int size, int color, t_game *game);
void			ft_put_img(t_game *game, void *image, int x, int y);
void			ft_put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);

// raycasting
bool			touch(float px, float py, t_game *game);
float			distance(float x, float y);
float			fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
void			draw_line(t_player *player, t_game *game, float start_x, int i);

void			ft_put_img(t_game *game, void *image, int x, int y);


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