/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:51:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/04 12:07:48 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_game *game)
{
	int	size;
	int	color;
	int	px;
	int	py;

	size = 4;
	color = 0xFF0000;
	px = 20 + (int)(game->player.x / 4);
	py = 20 + (int)(game->player.y / 4);
	draw_square(px - size / 2, py - size / 2, size, color, game);
}

void	draw_map(t_game *game)
{
	int color;
	int y;
	int x;

	char **map = game->map_copy;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(20 + x * 16, 20 + y * 16, 16, color, game);
			else
				draw_square(20 + x * 16, 20 + y * 16, 16, 0x000000, game);
			x++;
		}
		y++;
	}
	draw_player(game);
}
