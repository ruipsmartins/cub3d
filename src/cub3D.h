/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/25 12:21:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define WIDTH 1280
# define HEIGHT 720
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

typedef struct s_player
{
	void		*img_player;
	float		x;
	float		y;
	float		angle;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	float		speed;
	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	char		**map;
	int			map_size_x;
	int			map_size_y;
	void		*img_wall;
	void		*img_ground;
	void		*img_collectable;
	void		*img_exit;
	int			img_width;
	int			img_height;
}				t_data;




void move_player(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);




void			image_checker(t_data *data);
int				handle_input(int keycode, t_data *data);
char			**open_map(char *path);
void			map_checker(t_data *data);
void			free_map(t_data *data);
void			init_game(t_data *data);
void			map_draw(t_data *data);
int				close_game(t_data *data);
void			update_exit(t_data *data);
void			move_player_w(t_data *data);
void			move_player_a(t_data *data);
void			move_player_s(t_data *data);
void			move_player_d(t_data *data);
int				flood_test(t_data *data);
void			window_size(t_data *data);

#endif