/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:35:55 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/31 11:45:46 by ruidos-s         ###   ########.fr       */
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

// Inicializa os parâmetros iniciais do raio
void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->cos_angle = cos(ray_angle);
	ray->sin_angle = sin(ray_angle);
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	// Cálculo das distâncias delta
	ray->delta_dist_x = fabs(1 / ray->cos_angle);
	ray->delta_dist_y = fabs(1 / ray->sin_angle);
	// Determina os passos em X e Y
	ray->step_x = (ray->cos_angle < 0) ? -1 : 1;
	ray->step_y = (ray->sin_angle < 0) ? -1 : 1;
	// Calcula as distâncias laterais iniciais
	ray->side_dist_x = (ray->cos_angle < 0) ? (ray->ray_x - (int)ray->ray_x)
		* ray->delta_dist_x : (((int)ray->ray_x + 1 - ray->ray_x)
			* ray->delta_dist_x);
	ray->side_dist_y = (ray->sin_angle < 0) ? (ray->ray_y - (int)ray->ray_y)
		* ray->delta_dist_y : (((int)ray->ray_y + 1 - ray->ray_y)
			* ray->delta_dist_y);
	ray->hit = 0;
}
