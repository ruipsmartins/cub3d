/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:51:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/09 12:18:43 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Função para desenhar uma linha usando o algoritmo de Bresenham
void draw_direction_line(t_player *player, t_game *game)
{
    float ray_x = 150;
    float ray_y = 150;
    int i = 0;
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

void draw_player(t_game *game, int center_x, int center_y)
{
    int size = 4;
    int color = 0xFF0000;
    
    draw_direction_line(&game->player, game);
    draw_square(center_x - size / 2, center_y - size / 2, size, color, game);
}

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


void	draw_minimap(t_game *game)
{
	int tile_size = 16;
	int center_x = 150;
	int center_y = 150;
	int minimap_radius = 95; // metade do lado do minimapa (200x200)
	int y, x;
	char **map = game->map_copy;

	// Calcula a posição do jogador no sistema de coordenadas do minimapa

	y = 0;
	draw_minimap_background(game, center_x, center_y, minimap_radius);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
				//deslocando para manter o jogador centrado
			int draw_x = center_x + (x * tile_size) - ((int)(game->player.x / 4));
			int draw_y = center_y + (y * tile_size) - ((int)(game->player.y / 4));

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
			x++;
		}
		y++;
	}
	draw_player(game, center_x, center_y);
}

