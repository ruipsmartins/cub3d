/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:35:55 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/26 17:06:49 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

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

// Calculate the perpendicular distance to avoid fish-eye effect
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

int get_texture_pixel(t_img *texture, int x, int y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); // Cor preta se estiver fora dos limites

	char *pixel = texture->pixel_buffer + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
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
	//if (side == 0)
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	/* else
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game); */

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
		int color;
		int texture_x;
		int texture_y;
		int teste = 0;

		(void)teste;

		t_img wall;
		if (side == 1) // Parede Norte ou Sul
		{
			if (step_y == -1)
				wall = game->textures.wall_N;
			else
			{
				wall = game->textures.wall_S;
				teste = 1;
			}
		}
		else // Parede Este ou Oeste
		{
			if (step_x == -1)
				wall = game->textures.wall_W;
			else
			{
				wall = game->textures.wall_E;
				teste = 1;
			}
		}		

		// Mapeamento correto da posição X na textura (horizontal)
		if (side == 0) // Parede vertical (Norte ou Sul)
    		texture_x = (int)(ray_y) % wall.width;
		else // Parede horizontal (Este ou Oeste)
    		texture_x = (int)(ray_x) % wall.width;

		// Calcular o "step" para percorrer a textura uniformemente
		float texture_step = (float)wall.height / height;

		// Definir a posição inicial na textura
		float texture_pos = (start_y - (WINDOW_HEIGHT - height) / 2) * texture_step;

		// Percorrer os píxeis verticais e desenhá-los corretamente
		
		while (start_y < end)
		{
			texture_y = (int)texture_pos % wall.height;
			color = get_texture_pixel(&wall, texture_x, texture_y);
			ft_put_pixel(i, start_y, color, game);
			// Avançar na textura de forma proporcional
			texture_pos += texture_step;
			start_y++;
		}
	}
}

