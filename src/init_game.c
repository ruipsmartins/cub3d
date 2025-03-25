/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/25 11:41:36 by duamarqu         ###   ########.fr       */
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


void load_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Erro ao carregar a textura %s\n", path);
		exit(1);
	}
	texture->pixel_buffer = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}


void	init_game(t_game *game)
{
	init_texture_and_rgb(game);
	copy_map(game);
	get_textures(game);
	get_rgb(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	game->screen_img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->screen_img.pixel_buffer = mlx_get_data_addr(game->screen_img.img, &game->screen_img.bpp, &game->screen_img.size_line, &game->screen_img.endian);
	init_player(&game->player);

	// textura da parede apenas para testar
//	load_texture(game, &game->textures.wall_N, "./img/n_texture.xpm");
	load_texture(game, &game->textures.wall_N, game->path_no);
}

// void	find_player(t_game *game)
// {
// 	int x;
// 	int y;


// }

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