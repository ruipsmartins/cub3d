/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:51:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 17:28:44 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Calculates where to draw each tile in the minimap */
static void	calculate_draw_coords(t_minimap *minimap, t_game *game, int x,
		int y)
{
	minimap->draw_x = minimap->center_x + (x * minimap->tile_size)
		- ((int)(game->player.x / 4));
	minimap->draw_y = minimap->center_y + (y * minimap->tile_size)
		- ((int)(game->player.y / 4));
}

/* Checks if a tile is outside the minimap boundaries */
static int	is_outside_minimap(t_minimap *minimap)
{
	if (minimap->draw_x + minimap->tile_size < minimap->center_x
		- minimap->minimap_radius || minimap->draw_x > minimap->center_x
		+ minimap->minimap_radius || minimap->draw_y
		+ minimap->tile_size < minimap->center_y - minimap->minimap_radius
		|| minimap->draw_y > minimap->center_y + minimap->minimap_radius)
		return (1);
	return (0);
}

/* Draws all map tiles in the minimap */
void	draw_minimap_tiles(t_game *game, t_minimap *minimap)
{
	int	y;
	int	x;

	y = 0;
	while (game->map_copy[y])
	{
		x = 0;
		while (game->map_copy[y][x])
		{
			calculate_draw_coords(minimap, game, x, y);
			if (is_outside_minimap(minimap))
			{
				x++;
				continue ;
			}
			if (game->map_copy[y][x] == '1')
				draw_square(minimap->draw_x, minimap->draw_y,
					minimap->tile_size, game);
			x++;
		}
		y++;
	}
}

/* Main function that draws the minimap */
void	draw_minimap(t_game *game)
{
	t_minimap	minimap;

	init_minimap(&minimap);
	draw_minimap_background(game, minimap.center_x, minimap.center_y,
		minimap.minimap_radius + 5);
	draw_minimap_tiles(game, &minimap);
	draw_player(game, minimap.center_x, minimap.center_y);
	draw_frame(&game->textures.minimap_frame, game);
}
