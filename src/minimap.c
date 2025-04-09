/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:51:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/09 15:13:44 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/* Calcula as coordenadas de desenho do tile */
static void	calculate_draw_coords(t_minimap *minimap, t_game *game, int x, int y)
{
	minimap->draw_x = minimap->center_x + (x * minimap->tile_size)
		- ((int)(game->player.x / 4));
	minimap->draw_y = minimap->center_y + (y * minimap->tile_size)
		- ((int)(game->player.y / 4));
}

/* Verifica se o tile está fora do minimapa */
static int	is_outside_minimap(t_minimap *minimap)
{
	if (minimap->draw_x + minimap->tile_size < minimap->center_x
		- minimap->minimap_radius
		|| minimap->draw_x > minimap->center_x + minimap->minimap_radius
		|| minimap->draw_y + minimap->tile_size < minimap->center_y
		- minimap->minimap_radius
		|| minimap->draw_y > minimap->center_y + minimap->minimap_radius)
		return (1);
	return (0);
}

/* Função para desenhar os tiles do minimapa */
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
					minimap->tile_size, 0x0000FF, game);
			x++;
		}
		y++;
	}
}



void	draw_frame(t_img *src, t_game *game, int offset_x, int offset_y)
{
	int	x;
	int	y;
	int	center_x;
	int	center_y;
	int	radius_squared;
	unsigned char	rgb[3];

	center_x = src->width / 2;
	center_y = src->height / 2;
	radius_squared = 100 * 100;

	y = 0;
	while (y < src->height)
	{
		int	line_offset = y * src->size_line;
		int	dy = y - center_y;

		x = 0;
		while (x < src->width)
		{
			int	dx = x - center_x;

			if ((dx * dx + dy * dy) > radius_squared)
			{
				int	pixel_offset = line_offset + (x * (src->bpp / 8));

				rgb[2] = src->pixel_buffer[pixel_offset + 2];	// Red
				rgb[1] = src->pixel_buffer[pixel_offset + 1];	// Green
				rgb[0] = src->pixel_buffer[pixel_offset];		// Blue

				int	color = (rgb[2] << 16) | (rgb[1] << 8) | rgb[0];
				ft_put_pixel(x + offset_x, y + offset_y, color, game);
			}
			x++;
		}
		y++;
	}
}

/* Função principal do minimapa */
void	draw_minimap(t_game *game)
{
	t_minimap	minimap;

	init_minimap(&minimap);
	draw_minimap_background(game, minimap.center_x, minimap.center_y,
		minimap.minimap_radius + 5);
	draw_minimap_tiles(game, &minimap);
	draw_player(game, minimap.center_x, minimap.center_y);
	draw_frame(&game->textures.minimap_frame, game, 35, 35);
}
