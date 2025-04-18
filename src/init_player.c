/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:28 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/16 10:48:10 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	find_player_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->player.x = 0;
	game->player.y = 0;
	while (y <= game->map_height)
	{
		x = 0;
		if (!game->map_copy[y])
			break ;
		while (game->map_copy[y][x])
		{
			if (game->map_copy[y][x] == 'N' || game->map_copy[y][x] == 'S'
				|| game->map_copy[y][x] == 'W' || game->map_copy[y][x] == 'E')
				check_multiple_players(game, x, y);
			x++;
		}
		y++;
	}
}

static void	set_player_angle(t_game *game)
{
	if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'S')
		game->player.angle = PI / 2;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'W')
		game->player.angle = PI;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'E')
		game->player.angle = 0;
}

static void	check_invalid_angle(t_game *game)
{
	if (game->player.angle == -1)
	{
		ft_putstr_fd("Error\nInvalid player position\n", 2);
		free_all_maps(game);
		exit(1);
	}
}

void	find_player_angle(t_game *game)
{
	game->player.angle = -1;
	if (game->player.x == 0 || game->player.y == 0)
	{
		ft_putstr_fd("Error\nNo player position found\n", 2);
		free_all_maps(game);
		exit(1);
	}
	set_player_angle(game);
	check_invalid_angle(game);
	game->player.x = game->player.x * BLOCK + 32;
	game->player.y = game->player.y * BLOCK + 32;
}

void	init_player(t_game *game)
{
	find_player_pos(game);
	find_player_angle(game);
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_right = false;
	game->player.key_left = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}
