/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:35:55 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/21 16:16:19 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

/* bool touch(float px, float py, t_game *game)
{
	float x;
	float y;
	float epsilon = 0.01;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map_copy[(int)(y + epsilon)][(int)(x + epsilon)] == '1' ||
	game->map_copy[(int)(y - epsilon)][(int)(x + epsilon)] == '1' ||
	game->map_copy[(int)(y + epsilon)][(int)(x - epsilon)] == '1' ||
	game->map_copy[(int)(y - epsilon)][(int)(x - epsilon)] == '1' ||
	game->map_copy[(int)y][(int)(x + epsilon)] == '1' ||
	game->map_copy[(int)y][(int)(x - epsilon)] == '1' ||
	game->map_copy[(int)(y + epsilon)][(int)x] == '1' ||
	game->map_copy[(int)(y - epsilon)][(int)x] == '1')
		return (true);
	return (false);
} */
bool touch(float px, float py, t_game *game)
{
	float x;
	float y;

 	x = px / BLOCK;
 	y = py / BLOCK;
 	if (game->map_copy[(int)y][(int)x] == '1') // tenho de meter parede a volta do mapa, se sair fora da seg
 		return (true);
 	return (false);
}

// distance calculation functions
float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x;
	float delta_y;
	float angle;
	float fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

// raycasting functions with DDA algorithm
void draw_line(t_player *player, t_game *game, float ray_angle, int i)
{
	float cos_angle;
	float sin_angle;
	float ray_x;
	float ray_y;
	float dist;
	float height;
	int start_y;
	int end;

	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	ray_x = player->x;
	ray_y = player->y;

	// DDA algorithm
	float delta_dist_x;
	float delta_dist_y;
	float side_dist_x;
	float side_dist_y;
	int step_x;
	int step_y;
	int hit;
	int side;

	delta_dist_x = fabs(1 / cos_angle);
	delta_dist_y = fabs(1 / sin_angle);
	step_x = (cos_angle < 0) ? -1 : 1;
	step_y = (sin_angle < 0) ? -1 : 1;
	side_dist_x = (cos_angle < 0) ? (ray_x - (int)ray_x) * delta_dist_x : ((int)ray_x + 1 - ray_x) * delta_dist_x;
	side_dist_y = (sin_angle < 0) ? (ray_y - (int)ray_y) * delta_dist_y : ((int)ray_y + 1  - ray_y) * delta_dist_y;

	hit = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			ray_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			ray_y += step_y;
			side = 1;
		}
		if (touch(ray_x, ray_y, game))
			hit = 1;
	}

	// Calculate the perpendicular distance to avoid fish-eye effect
	if (side == 0)
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	else
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);

	// Correct for fish-eye effect by multiplying by the cosine of the relative angle
	//float relative_angle = ray_angle - player->angle;
	//dist *= cos(relative_angle);

	// Calculate wall height
	height = (BLOCK / dist) * (WINDOW_WIDTH / 2);
	start_y = (WINDOW_HEIGHT - height) / 2;
	end = start_y + height;

	// Ensure the wall height stays within the screen bounds
	if (start_y < 0)
		start_y = 0;
	if (end >= WINDOW_HEIGHT)
		end = WINDOW_HEIGHT - 1;

	// Draw the wall slice
	while (start_y < end)
	{
		ft_put_pixel(i, start_y, 0x1E3A5F, game);
		start_y++;
	}
}