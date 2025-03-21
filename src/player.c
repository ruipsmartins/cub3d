/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:04:00 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/21 14:15:32 by ruidos-s         ###   ########.fr       */
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
	if (keycode == 65307) // ESC
		clean_game(game);
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

void	move_player(t_player *player, t_game *game)
{
	int speed = 3;
	float angle_speed = 0.06;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);
	float new_x;
	float new_y;

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		new_x = player->x + cos_angle * speed;
		new_y = player->y + sin_angle * speed;

		// Verifica colisão com um pequeno raio ao redor do jogador
		if (!is_colliding(game, new_x + PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x - PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x, new_y + PLAYER_RADIUS)
			&& !is_colliding(game, new_x, new_y - PLAYER_RADIUS))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}

	if (player->key_down)
	{
		new_x = player->x - cos_angle * speed;
		new_y = player->y - sin_angle * speed;

		if (!is_colliding(game, new_x + PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x - PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x, new_y + PLAYER_RADIUS)
			&& !is_colliding(game, new_x, new_y - PLAYER_RADIUS))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}

	if (player->key_left)
	{
		new_x = player->x + sin_angle * speed;
		new_y = player->y - cos_angle * speed;

		if (!is_colliding(game, new_x + PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x - PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x, new_y + PLAYER_RADIUS)
			&& !is_colliding(game, new_x, new_y - PLAYER_RADIUS))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}

	if (player->key_right)
	{
		new_x = player->x - sin_angle * speed;
		new_y = player->y + cos_angle * speed;

		if (!is_colliding(game, new_x + PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x - PLAYER_RADIUS, new_y)
			&& !is_colliding(game, new_x, new_y + PLAYER_RADIUS)
			&& !is_colliding(game, new_x, new_y - PLAYER_RADIUS))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}