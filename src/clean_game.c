/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:59:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/07 16:24:25 by ruidos-s         ###   ########.fr       */
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


void clean_images(t_game *game)
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
}

void free_path(t_game *game)
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

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	i = 0;
	while (game->map_copy[i])
	{
		free(game->map_copy[i]);
		i++;
	}
	free(game->map_copy);
}

int	clean_game(t_game *game)
{
    
	clean_images(game);
	free_path(game);
	free_map(game);

    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);
    if (game->mlx)
        free(game->mlx);
    

    exit(game->return_value);
}