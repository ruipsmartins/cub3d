/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:51:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/08 17:34:25 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_game *game, int center_x, int center_y)
{
	int	size;
	int	color;

	size = 4;
	color = 0xFF0000;
	// Desenha o jogador sempre no centro do minimapa
	draw_square(center_x - size / 2, center_y - size / 2, size, color, game);
}

void	draw_rectangle(int x, int y, int width, int height, int color,
		t_game *game)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ft_put_pixel(x + j, y + i, color, game);
		}
	}
}

void	draw_minimap_border(t_game *game, int center_x, int center_y,
		int minimap_radius)
{
	int	border_thickness;
	int	top_left_x;
	int	top_left_y;
	int	size;

	int border_color = 0xFFFFFF; // Branco
	border_thickness = 2;
	top_left_x = center_x - minimap_radius;
	top_left_y = center_y - minimap_radius;
	size = minimap_radius * 2;
	// Topo
	draw_rectangle(top_left_x, top_left_y, size, border_thickness, border_color,
		game);
	// Fundo
	draw_rectangle(top_left_x, top_left_y + size - border_thickness, size,
		border_thickness, border_color, game);
	// Esquerda
	draw_rectangle(top_left_x, top_left_y, border_thickness, size, border_color,
		game);
	// Direita
	draw_rectangle(top_left_x + size - border_thickness, top_left_y,
		border_thickness, size, border_color, game);
}

void	draw_map(t_game *game)
{
	int tile_size = 16;
	int center_x = 150;
	int center_y = 150;
	int minimap_radius = 100; // metade do lado do minimapa (200x200)
	int y, x;
	char **map = game->map_copy;

	// Calcula a posição do jogador no sistema de coordenadas do minimapa
	int player_minimap_x = (int)(game->player.x / 4);
	int player_minimap_y = (int)(game->player.y / 4);

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// Calcula a posição de desenho de cada tile,
				//deslocando para manter o jogador centrado
			int draw_x = center_x + (x * tile_size) - player_minimap_x;
			int draw_y = center_y + (y * tile_size) - player_minimap_y;

			// Verifica se o tile está dentro da área de visualização do minimapa
			if (draw_x + tile_size < center_x - minimap_radius
				|| draw_x > center_x + minimap_radius || draw_y
				+ tile_size < center_y - minimap_radius || draw_y > center_y
				+ minimap_radius)
			{
				x++;
				continue ; // ignora tiles fora da área
			}

			if (map[y][x] == '1')
				draw_square(draw_x, draw_y, tile_size, 0x0000FF, game);
			else
				draw_square(draw_x, draw_y, tile_size, 0x000000, game);
			x++;
		}
		y++;
	}
	draw_player(game, center_x, center_y);
	draw_minimap_border(game, center_x, center_y, minimap_radius);
}

