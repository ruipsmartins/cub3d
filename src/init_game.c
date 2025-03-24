/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/24 14:39:47 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	init_texture_and_rgb(t_game *game)
{
	game->path_no = NULL;
	game->path_so = NULL;
	game->path_we = NULL;
	game->path_ea = NULL;
	game->color_floor = -1;
	game->color_ceiling = -1;
}

void	init_game(t_game *game)
{
	init_texture_and_rgb(game);
	copy_map(game);

	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	game->screen_img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->screen_img.pixel_buffer = mlx_get_data_addr(game->screen_img.img, &game->screen_img.bpp, &game->screen_img.size_line, &game->screen_img.endian);
	//mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	init_player(&game->player);

		// textura da parede apenas para testar
	game->img_wall.img = mlx_xpm_file_to_image(game->mlx,
		"./img/bricksx64.xpm", &game->img_wall.width, &game->img_wall.height);
	game->img_wall.pixel_buffer = mlx_get_data_addr(game->img_wall.img, &game->img_wall.bpp, &game->img_wall.size_line, &game->img_wall.endian);
	
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