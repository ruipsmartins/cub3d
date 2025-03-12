/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/12 11:38:02 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	//mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	init_player(&game->player);
	game->player.img = mlx_xpm_file_to_image(game->mlx,
		"./img/player_s.xpm", &game->player.img_width, &game->player.img_height);
	if(!game->player.img)
	{
		ft_putstr_fd("Error\nPlayer image not found\n", 2);
		exit(1);
	}
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
		"./img/bricksx64.xpm", &game->img_width, &game->img_height);

	game->img_background = mlx_xpm_file_to_image(game->mlx,
	"./img/background.xpm", &game->img_width, &game->img_height);
	if(!game->img_background)
	{
		ft_putstr_fd("Error\nbackground image not found\n", 2);
		exit(1);
	}
	
	
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