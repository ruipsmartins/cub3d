/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:35:55 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/28 14:41:23 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

bool	touch(float px, float py, t_game *game)
{
	float	x;
	float	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map_copy[(int)y][(int)x] == '1')
		// tenho de meter parede a volta do mapa, se sair fora da seg
		return (true);
	return (false);
}

// distance calculation functions
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

// Calculate the perpendicular distance to avoid fish-eye effect
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

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); // Cor preta se estiver fora dos limites
	pixel = texture->pixel_buffer + (y * texture->size_line + x * (texture->bpp
				/ 8));
	return (*(unsigned int *)pixel);
}

// raycasting functions with DDA algorithm
void	draw_ray_cast(t_player *player, t_game *game, float ray_angle, int i)
{
	t_ray	ray;

	ray.cos_angle = cos(ray_angle);
	ray.sin_angle = sin(ray_angle);
	ray.ray_x = player->x;
	ray.ray_y = player->y;
	// DDA algorithm
	ray.delta_dist_x = fabs(1 / ray.cos_angle);
	ray.delta_dist_y = fabs(1 / ray.sin_angle);
	ray.step_x = (ray.cos_angle < 0) ? -1 : 1;
	ray.step_y = (ray.sin_angle < 0) ? -1 : 1;
	ray.side_dist_x = (ray.cos_angle < 0) ? (ray.ray_x - (int)ray.ray_x)
		* ray.delta_dist_x : ((int)ray.ray_x + 1 - ray.ray_x) * ray.delta_dist_x;
		ray.side_dist_y = (ray.sin_angle < 0) ? (ray.ray_y - (int)ray.ray_y)
		* ray.delta_dist_y : ((int)ray.ray_y + 1 - ray.ray_y) * ray.delta_dist_y;
	ray.hit = 0;
	while (!ray.hit)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.ray_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.ray_y += ray.step_y;
			ray.side = 1;
		}
		if (touch(ray.ray_x, ray.ray_y, game))
			ray.hit = 1;
	}
	// Calculate the perpendicular distance to avoid fish-eye effect
	// if (side == 0)
	ray.dist = fixed_dist(player->x, player->y, ray.ray_x, ray.ray_y, game);
	/* else
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game); */
	// Calculate wall height
	ray.height = (BLOCK / ray.dist) * (WINDOW_WIDTH / 2);
	ray.start_y = (WINDOW_HEIGHT - ray.height) / 2;
	ray.end = ray.start_y + ray.height;
	// Ensure the wall height stays within the screen bounds
	if (ray.start_y < 0)
		ray.start_y = 0;
	if (ray.end >= WINDOW_HEIGHT)
		ray.end = WINDOW_HEIGHT - 1;
	// Draw the wall slice
	while (ray.start_y < ray.end)
	{
		if (ray.side == 1) // Parede Norte ou Sul
		{
			if (ray.step_y == -1)
			{
				ray.wall = game->textures.wall_N;
				ray.texture_x = (int)(ray.ray_y) % ray.wall.width;
			}
			else
			{
				ray.wall = game->textures.wall_S;
				ray.texture_x = (int)(ray.ray_y) % ray.wall.width;
			}
		}
		else // Parede Este ou Oeste
		{
			if (ray.step_x == -1)
			{
				ray.wall = game->textures.wall_W;
				ray.texture_x = (int)(ray.ray_x) % ray.wall.width;
			}
			else
			{
				ray.wall = game->textures.wall_E;
				ray.texture_x = (int)(ray.ray_x) % ray.wall.width;
			}
		}
		// Mapeamento correto da posição X na textura (horizontal)
		if (ray.side == 0) // Parede vertical (Norte ou Sul)
			ray.texture_x = (int)(ray.ray_y) % ray.wall.width;
		else // Parede horizontal (Este ou Oeste)
			ray.texture_x = (int)(ray.ray_x) % ray.wall.width;
		if (ray.wall.img == game->textures.wall_S.img)
			ray.texture_x = ray.wall.width - ray.texture_x - 1;
		if (ray.wall.img == game->textures.wall_W.img)
			ray.texture_x = ray.wall.width - ray.texture_x - 1;
		// Calcular o "step" para percorrer a textura uniformemente
		ray.texture_step = (float)ray.wall.height / ray.height;
		// Definir a posição inicial na textura
		ray.texture_pos = (ray.start_y - (WINDOW_HEIGHT - ray.height) / 2) * ray.texture_step;
		// Percorrer os píxeis verticais e desenhá-los corretamente
		while (ray.start_y < ray.end)
		{
			ray.texture_y = (int)ray.texture_pos % ray.wall.height;
			ray.color = get_texture_pixel(&ray.wall, ray.texture_x, ray.texture_y);
			ft_put_pixel(i, ray.start_y, ray.color, game);
			// Avançar na textura de forma proporcional
			ray.texture_pos += ray.texture_step;
			ray.start_y++;
		}
	}
}
