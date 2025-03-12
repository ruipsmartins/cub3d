/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/12 16:41:55 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->pixel_buffer = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	//mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	init_player(&game->player);

	game->player.img = mlx_xpm_file_to_image(game->mlx,
		"./img/player_s.xpm", &game->player.img_width, &game->player.img_height);
	

	game->img_wall.img = mlx_xpm_file_to_image(game->mlx,
		"./img/bricksx64.xpm", &game->img_wall.img_width, &game->img_wall.img_height);

	
	
	
}

void	init_player(t_player *player)
{
	player->x = 200;
	player->y = 200;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}