/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:59:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 15:26:58 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

/* int	clean_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->screen_img.img);
	mlx_destroy_image(game->mlx, game->textures.wall_N.img);
	mlx_destroy_image(game->mlx, game->textures.wall_S.img);
	mlx_destroy_image(game->mlx, game->textures.wall_E.img);
	mlx_destroy_image(game->mlx, game->textures.wall_W.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game);
	exit(0);
} */

void	free_images(t_game *game)
{
	if (game->screen_img.img)
		mlx_destroy_image(game->mlx, game->screen_img.img);
	if (game->textures.wall_N.img)
		mlx_destroy_image(game->mlx, game->textures.wall_N.img);
	if (game->textures.wall_S.img)
		mlx_destroy_image(game->mlx, game->textures.wall_S.img);
	if (game->textures.wall_E.img)
		mlx_destroy_image(game->mlx, game->textures.wall_E.img);
	if (game->textures.wall_W.img)
		mlx_destroy_image(game->mlx, game->textures.wall_W.img);
	if (game->textures.minimap_frame.img)
		mlx_destroy_image(game->mlx, game->textures.minimap_frame.img);
}

void	free_path(t_game *game)
{
	if (game->path_no)
		free(game->path_no);
	if (game->path_so)
		free(game->path_so);
	if (game->path_we)
		free(game->path_we);
	if (game->path_ea)
		free(game->path_ea);
}

void	free_single_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map);
	}
}

void	free_all_maps(t_game *game)
{
	free_single_map(game->map);
	game->map = NULL;
	free_single_map(game->map_copy);
	game->map_copy = NULL;
}

int	clean_game(t_game *game)
{
	free_images(game);
	free_path(game);
	free_all_maps(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	exit(game->return_value);
}
