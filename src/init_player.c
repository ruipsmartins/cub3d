/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/09 16:29:41 by ruidos-s         ###   ########.fr       */
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
			{
				if (game->player.x)
				{
					free_all_maps(game);
					printf("Error\nPlayer positions\n");
					exit(1);
				}
				printf("x: %d y: %d\n", x, y);
				game->player.x = x;
				game->player.y = y;
			}
			x++;
		}
		y++;
	}
}
void	find_player_angle(t_game *game)
{
	game->player.angle = -1;
	if (game->player.x == 0 || game->player.y == 0)
	{
		printf("Error\nNo player position found\n");
		free_all_maps(game);
		exit(1);
	}
	printf("x: %f y: %f\n", game->player.x, game->player.y);
	if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'S')
		game->player.angle = PI / 2;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'W')
		game->player.angle = PI;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'E')
		game->player.angle = 0;
	printf("angle: %f\n", game->player.angle);
	if (game->player.angle == -1)
	{
		printf("x: %d y: %d\n", (int)game->player.x, (int)game->player.y);
		printf("map: %c\n",
			game->map_copy[(int)game->player.y][(int)game->player.x]);
		printf("Error\nInvalid player position\n");
		exit(1);
	}
	game->player.x = game->player.x * BLOCK + 32;
	game->player.y = game->player.y * BLOCK + 32;
}

void	init_player(t_game *game)
{
	// ft_bzero(&game->player, sizeof(t_player));
	printf("init_player\n");
	find_player_pos(game);
	find_player_angle(game);
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_right = false;
	game->player.key_left = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}