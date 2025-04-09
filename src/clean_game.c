/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:59:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/09 18:54:43 by duamarqu         ###   ########.fr       */
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


void free_images(t_game *game)
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
	if(game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

void free_all_maps(t_game *game)
{
    int i = 0;

    if (game->map)
    {
        while (game->map[i])
        {
            free(game->map[i]);
            game->map[i] = NULL; // Avoid dangling pointers
            i++;
        }
        free(game->map);
        game->map = NULL; // Avoid dangling pointer
    }

    i = 0;
    if (game->map_copy)
    {
        while (game->map_copy[i])
        {
            free(game->map_copy[i]);
            game->map_copy[i] = NULL; // Avoid dangling pointers
            i++;
        }
        free(game->map_copy);
        game->map_copy = NULL; // Avoid dangling pointer
    }
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