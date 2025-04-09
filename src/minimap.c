/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:51:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/09 12:48:35 by ruidos-s         ###   ########.fr       */
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

static void	init_minimap(t_minimap *minimap)
{
	minimap->tile_size = 16;
	minimap->center_x = 150;
	minimap->center_y = 150;
	minimap->minimap_radius = 95;
}

/* Função para desenhar os tiles do minimapa */
static void	draw_minimap_tiles(t_game *game, t_minimap *minimap)
{
	int	y;
	int	x;

	y = 0;
	while (game->map_copy[y])
	{
		x = 0;
		while (game->map_copy[y][x])
		{
			/* Calcula as coordenadas de desenho do tile */
			minimap->draw_x = minimap->center_x + (x * minimap->tile_size)
				- ((int)(game->player.x / 4));
			minimap->draw_y = minimap->center_y + (y * minimap->tile_size)
				- ((int)(game->player.y / 4));
			/* Verifica se o tile está dentro da área do minimapa */
			if (minimap->draw_x + minimap->tile_size < minimap->center_x
				- minimap->minimap_radius
				|| minimap->draw_x > minimap->center_x
				+ minimap->minimap_radius
				|| minimap->draw_y + minimap->tile_size < minimap->center_y
				- minimap->minimap_radius
				|| minimap->draw_y > minimap->center_y
				+ minimap->minimap_radius)
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

/* Função principal do minimapa */
void	draw_minimap(t_game *game)
{
	t_minimap	minimap;

	init_minimap(&minimap);
	/* Desenha o fundo do minimapa */
	draw_minimap_background(game, minimap.center_x, minimap.center_y,
		minimap.minimap_radius);
	/* Desenha os tiles do minimapa */
	draw_minimap_tiles(game, &minimap);
	/* Desenha o jogador no minimapa */
	draw_player(game, minimap.center_x, minimap.center_y);
}
