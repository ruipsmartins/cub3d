/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:11:35 by addicted          #+#    #+#             */
/*   Updated: 2025/04/16 10:47:49 by ruidos-s         ###   ########.fr       */
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
	game->textures.wall_e.img = NULL;
	game->textures.wall_w.img = NULL;
	game->textures.wall_n.img = NULL;
	game->textures.wall_s.img = NULL;
	game->textures.minimap_frame.img = NULL;
}

void	load_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		ft_putstr_fd("Error\nFailed to load texture ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		clean_game(game);
	}
	texture->pixel_buffer = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->textures.wall_n, game->path_no);
	load_texture(game, &game->textures.wall_s, game->path_so);
	load_texture(game, &game->textures.wall_w, game->path_we);
	load_texture(game, &game->textures.wall_e, game->path_ea);
	load_texture(game, &game->textures.minimap_frame,
		"./img/minimap_frame.xpm");
}

static void	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize mlx\n", 2);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		exit(1);
	}
	game->screen_img.img = mlx_new_image(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	game->screen_img.pixel_buffer = mlx_get_data_addr(game->screen_img.img,
			&game->screen_img.bpp, &game->screen_img.size_line,
			&game->screen_img.endian);
}

void	init_game(t_game *game)
{
	game->return_value = 1;
	if (!game->map)
	{
		ft_putstr_fd("Error\nDidnt find the map!\n", 2);
		exit(1);
	}
	map_len(game);
	check_wrong_options(game);
	init_texture_and_rgb(game);
	copy_map(game);
	init_player(game);
	ff_map(game);
	get_textures(game);
	get_rgb(game);
	init_mlx_window(game);
	load_textures(game);
}
