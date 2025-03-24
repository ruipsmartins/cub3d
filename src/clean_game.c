/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:59:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/24 16:56:33 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"



int	clean_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->screen_img.img);
	mlx_destroy_image(game->mlx, game->img_wall.img);

	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game);
	exit(0);
}