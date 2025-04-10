/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:04:00 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/10 16:20:54 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	rotate_player(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.04;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void move_in_direction(t_player *player, t_game *game, float dx, float dy)
{
    float new_x;
    float new_y;

	new_x = player->x + dx;
	new_y = player->y;
    if (!is_colliding(game, new_x + PLAYER_RADIUS, player->y) &&
        !is_colliding(game, new_x - PLAYER_RADIUS, player->y))
    {
        player->x = new_x;
    }
    new_y = player->y + dy;
    if (!is_colliding(game, player->x, new_y + PLAYER_RADIUS) &&
        !is_colliding(game, player->x, new_y - PLAYER_RADIUS))
    {
        player->y = new_y;
    }
}

void	move_player(t_player *player, t_game *game)
{
	int		speed;
	float	cos_angle;
	float	sin_angle;

	speed = 3;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	rotate_player(player);
	if (player->key_up)
		move_in_direction(player, game, cos_angle * speed, sin_angle * speed);
	if (player->key_down)
		move_in_direction(player, game, -cos_angle * speed, -sin_angle * speed);
	if (player->key_left)
		move_in_direction(player, game, sin_angle * speed, -cos_angle * speed);
	if (player->key_right)
		move_in_direction(player, game, -sin_angle * speed, cos_angle * speed);
}
