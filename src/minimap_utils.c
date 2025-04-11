/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:58:18 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 17:29:17 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Initializes the minimap
void	init_minimap(t_minimap *minimap)
{
	minimap->tile_size = 16;
	minimap->center_x = 150;
	minimap->center_y = 150;
	minimap->minimap_radius = 95;
}

// Draws the background of the minimap
void	draw_minimap_background(t_game *game, int center_x, int center_y,
		int minimap_radius)
{
	int	top_left_x;
	int	top_left_y;
	int	size;
	int	i;
	int	j;

	top_left_x = center_x - minimap_radius;
	top_left_y = center_y - minimap_radius;
	size = minimap_radius * 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_put_pixel(top_left_x + j, top_left_y + i, game->color_floor,
				game);
			j++;
		}
		i++;
	}
}

// Função para desenhar uma linha usando o algoritmo de Bresenham
void	draw_direction_line(t_player *player, t_game *game)
{
	float	ray_x;
	float	ray_y;
	int		i;

	ray_x = 150;
	ray_y = 150;
	i = 0;
	game->ray.cos_angle = cos(player->angle);
	game->ray.sin_angle = sin(player->angle);
	(void)player;
	while (i < 10)
	{
		ft_put_pixel((int)ray_x, (int)ray_y, 0x00FFFF, game);
		ray_x += game->ray.cos_angle;
		ray_y += game->ray.sin_angle;
		i++;
	}
}

// Draws the player on the minimap
void	draw_player(t_game *game, int center_x, int center_y)
{
	int	size;

	size = 4;
	draw_direction_line(&game->player, game);
	draw_square(center_x - size / 2, center_y - size / 2, size, game);
}
