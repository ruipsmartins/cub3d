/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:04:00 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/16 10:43:39 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == 65307)
	{
		game->return_value = 0;
		clean_game(game);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

int	is_colliding(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x) / 64;
	map_y = (int)(y) / 64;
	return (game->map_copy[map_y][map_x] == '1');
}

void	check_multiple_players(t_game *game, int x, int y)
{
	if (game->player.x)
	{
		free_all_maps(game);
		ft_putstr_fd("Error\nPlayer positions\n", 2);
		exit(1);
	}
	game->player.x = x;
	game->player.y = y;
}
