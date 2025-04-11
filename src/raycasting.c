/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:35:55 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 16:04:19 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

// Execute the DDA algorithm to find the wall hit
void	perform_dda(t_ray *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->ray_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->ray_y += ray->step_y;
			ray->side = 1;
		}
		if (touch(ray->ray_x, ray->ray_y, game))
			ray->hit = 1;
	}
}

// Calculate the distance from the player to the wall
// and the height of the wall to be drawn
void	calculate_wall_projection(t_ray *ray, t_player *player, t_game *game)
{
	ray->dist = fixed_dist(game, player, ray);
	//proj_plane_dist = (WINDOW_WIDTH / 2) / tan(0.55);
	ray->height = (BLOCK / ray->dist) * ray->proj_plane_dist;
	ray->start_y = (WINDOW_HEIGHT - ray->height) / 2;
	ray->end = ray->start_y + ray->height;
	if (ray->start_y < 0)
		ray->start_y = 0;
	if (ray->end >= WINDOW_HEIGHT)
		ray->end = WINDOW_HEIGHT - 1;
}

// Selects the appropriate wall texture and calculates texture coordinates
void	select_wall_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 1)
	{
		if (ray->step_y == -1)
			ray->wall = game->textures.wall_n;
		else
			ray->wall = game->textures.wall_s;
	}
	else
	{
		if (ray->step_x == -1)
			ray->wall = game->textures.wall_w;
		else
			ray->wall = game->textures.wall_e;
	}
	if (ray->side == 0)
		ray->texture_x = (int)(ray->ray_y) % ray->wall.width;
	else
		ray->texture_x = (int)(ray->ray_x) % ray->wall.width;
	if (ray->wall.img == game->textures.wall_s.img)
		ray->texture_x = ray->wall.width - ray->texture_x - 1;
	if (ray->wall.img == game->textures.wall_w.img)
		ray->texture_x = ray->wall.width - ray->texture_x - 1;
}

// Draws a vertical slice of the wall on the screen
void	render_wall_slice(t_ray *ray, int column, t_game *game)
{
	float	texture_pos;
	int		y;
	int		texture_y;
	int		color;

	select_wall_texture(ray, game);
	ray->texture_step = (float)ray->wall.height / (ray->height);
	texture_pos = (ray->start_y - (WINDOW_HEIGHT - ray->height) / 2)
		* ray->texture_step;
	y = ray->start_y;
	while (y < ray->end)
	{
		texture_y = (int)texture_pos % ray->wall.height;
		color = get_texture_pixel(&ray->wall, ray->texture_x, texture_y);
		ft_put_pixel(column, y, color, game);
		texture_pos += ray->texture_step;
		y++;
	}
}

// Main function to draw a ray cast
void	draw_ray_cast(t_player *player, t_game *game, float ray_angle, int i)
{
	t_ray	ray;

	init_ray(&ray, player, ray_angle);
	perform_dda(&ray, game);
	calculate_wall_projection(&ray, player, game);
	render_wall_slice(&ray, i, game);
}
