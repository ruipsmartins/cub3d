/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:04:00 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/21 11:38:31 by addicted         ###   ########.fr       */
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

void	move_player(t_player *player, t_game *game)
{
	int speed = 3;
	float angle_speed = 0.06;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);
	int new_x;
	int new_y;
	int margin = 5; // Margem para evitar encostar na parede

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
		new_x = (int)(player->x + cos_angle * (speed + margin)) / 64;
		new_y = (int)(player->y + sin_angle * (speed + margin)) / 64;
		if (game->map_copy[new_y][new_x] != '1')
		{
			player->x += cos_angle * speed;
			player->y += sin_angle * speed;
		}
	}
	if (player->key_down)
	{
		new_x = (int)(player->x - cos_angle * (speed + margin)) / 64;
		new_y = (int)(player->y - sin_angle * (speed + margin)) / 64;
		if (game->map_copy[new_y][new_x] != '1')
		{
			player->x -= cos_angle * speed;
			player->y -= sin_angle * speed;
		}
	}
	if (player->key_left)
	{
		new_x = (int)(player->x + sin_angle * (speed + margin)) / 64;
		new_y = (int)(player->y - cos_angle * (speed + margin)) / 64;
		if (game->map_copy[new_y][new_x] != '1')
		{
			player->x += sin_angle * speed;
			player->y -= cos_angle * speed;
		}
	}
	if (player->key_right)
	{
		new_x = (int)(player->x - sin_angle * (speed + margin)) / 64;
		new_y = (int)(player->y + cos_angle * (speed + margin)) / 64;
		if (game->map_copy[new_y][new_x] != '1')
		{
			player->x -= sin_angle * speed;
			player->y += cos_angle * speed;
		}
	}
}