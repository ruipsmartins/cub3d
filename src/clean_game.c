/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:59:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/07 14:13:59 by ruidos-s         ###   ########.fr       */
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



int	clean_game(t_game *game)
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


    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);
    if (game->mlx)
        free(game->mlx);
    
    free_map(game);

    exit(game->return_value);
}