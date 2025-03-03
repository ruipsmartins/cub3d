/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:28 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/03 16:17:05 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

// our own put_pixel function
void	ft_put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	index = (x * game->bpp / 8) + (y * game->size_line);
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color & 0xFF00) >> 8;
	game->data[index + 2] = (color & 0xFF0000) >> 16;
}

// our own clear_image function
void	clear_image(t_game *game)
{
	for (int y = 0; y < WINDOW_HEIGHT; y++)
		for (int x = 0; x < WINDOW_WIDTH; x++)
			ft_put_pixel(x, y, 0, game);
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ft_put_pixel(x + i, y + j, color, game);
		}
	}
}

void	img_draw(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, image, x * 64, y * 64);
}

// touch function
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

// distance calculation functions
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

// raycasting functions
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			ft_put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		height = (BLOCK / dist) * (WINDOW_WIDTH / 2);
		start_y = (WINDOW_HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
		{
			ft_put_pixel(i, start_y, 200, game);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	// mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	fraction = PI / 3 / WINDOW_WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	if (DEBUG)
	{
		draw_map(game);
		draw_square(player->x, player->y, 40, 0x00FF00, game);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	game.map = open_map(argv[1]);
	init_game(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_wall, 200, 200);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
