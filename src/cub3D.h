/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/12 16:16:37 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define BLOCK 64
# define DEBUG 1
# define PI 3.14159265359

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PLAYER_RADIUS 5

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_minimap
{
	int			tile_size;
	int			center_x;
	int			center_y;
	int			minimap_radius;
	int			draw_x;
	int			draw_y;
}				t_minimap;

typedef struct s_img
{
	void		*img;
	char		*pixel_buffer;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_textures
{
	t_img		wall_n;
	t_img		wall_s;
	t_img		wall_e;
	t_img		wall_w;
	t_img		minimap_frame;
	t_img		floor;
	t_img		ceiling;
}				t_textures;

typedef struct s_ray
{
	float		cos_angle;
	float		sin_angle;
	float		ray_x;
	float		ray_y;
	float		dist;
	float		height;
	int			start_y;
	int			end;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			color;
	int			texture_x;
	int			texture_y;
	t_img		wall;
	float		texture_step;
	float		texture_pos;
}				t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_img		screen_img;
	t_textures	textures;
	t_ray		ray;
	int			return_value;
	char		**map;
	char		**map_copy;
	int			map_len;
	int			map_height;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	int			color_floor;
	int			color_ceiling;
}				t_game;

void			init_game(t_game *game);
void			init_player(t_game *game);
int				clean_game(t_game *game);
int				draw_loop(t_game *game);

void			draw_square(int x, int y, int size, t_game *game);
void			ft_put_img(t_game *game, void *image, int x, int y);
void			ft_put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
int				rgb_str_to_hex(char *rgb_str);
void			get_floor_color(t_game *game, char *line);

// raycasting
bool			touch(float px, float py, t_game *game);
float			distance(float x, float y);
float			fixed_dist(t_game *game, t_player *player, t_ray *ray);
void			draw_ray_cast(t_player *player, t_game *game, float start_x,
					int i);
void			ft_put_img(t_game *game, void *image, int x, int y);
void			render_wall_slice(t_ray *ray, int column, t_game *game);
void			perform_dda(t_ray *ray, t_game *game);
void			init_ray(t_ray *ray, t_player *player, float ray_angle);
int				get_texture_pixel(t_img *texture, int x, int y);

// player movement
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			move_player(t_player *player, t_game *game);
int				is_colliding(t_game *game, float x, float y);
void			rotate_player(t_player *player);
void			move_in_direction(t_player *player, t_game *game, float dx,
					float dy);
void			move_player(t_player *player, t_game *game);
void			check_multiple_players(t_game *game, int x, int y);

// map
char			**open_map(char *path);
void			free_all_maps(t_game *game);
void			check_wrong_options(t_game *game);
void			map_len(t_game *game);
int				skip_def(t_game *game);
int				flood_fill(t_game *game, int y, int x, char **map);
void			ff_map(t_game *game);
void			print_map(char **map);
void			draw_minimap(t_game *game);
void			map_height(t_game *game);
void			map_len(t_game *game);
void			ff_map(t_game *game);
void			check_map(t_game *game);

// texture utils
void			check_for_xpm(char *str, t_game *game);
void			get_north_texture(t_game *game, char *line);
void			get_south_texture(t_game *game, char *line);
void			get_west_texture(t_game *game, char *line);
void			get_east_texture(t_game *game, char *line);
void			validate_textures(t_game *game);

// texture core
void			check_duplicate_textures(t_game *game, int index);
void			process_texture_line(t_game *game, int index);
void			get_textures(t_game *game);

void			get_rgb(t_game *game);
void			copy_map(t_game *game);

// minimap
void			draw_minimap(t_game *game);
void			draw_minimap_tiles(t_game *game, t_minimap *minimap);
void			draw_minimap_background(t_game *game, int center_x,
					int center_y, int minimap_radius);
void			init_minimap(t_minimap *minimap);
void			draw_player(t_game *game, int center_x, int center_y);
void			draw_direction_line(t_player *player, t_game *game);

void			draw_frame(t_img *src, t_game *game);

int				should_update_frame(void);
void			free_images(t_game *game);
void			free_path(t_game *game);
void			free_all_maps(t_game *game);
void			free_single_map(char **map);

#endif
