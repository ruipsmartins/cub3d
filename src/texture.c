/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:33:23 by addicted          #+#    #+#             */
/*   Updated: 2025/04/11 17:33:59 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	validate_textures(t_game *game)
{
	if (game->path_no == NULL || game->path_so == NULL
		|| game->path_we == NULL || game->path_ea == NULL)
	{
		ft_putstr_fd("Error\nMissing texture\n", 2);
		clean_game(game);
	}
}

void	check_duplicate_textures(t_game *game, int index)
{
	if ((game->map[index][0] == 'N' && game->map[index][1] == 'O'
			&& game->path_no != NULL)
		|| (game->map[index][0] == 'S' && game->map[index][1] == 'O'
			&& game->path_so != NULL)
		|| (game->map[index][0] == 'W' && game->map[index][1] == 'E'
			&& game->path_we != NULL)
		|| (game->map[index][0] == 'E' && game->map[index][1] == 'A'
			&& game->path_ea != NULL))
	{
		ft_putstr_fd("Error\nDuplicate texture\n", 2);
		clean_game(game);
	}
}

void	process_texture_line(t_game *game, int index)
{
	if (game->map[index][0] == 'N' && game->map[index][1] == 'O'
		&& game->path_no == NULL)
		get_north_texture(game, game->map[index]);
	else if (game->map[index][0] == 'S' && game->map[index][1] == 'O'
		&& game->path_so == NULL)
		get_south_texture(game, game->map[index]);
	else if (game->map[index][0] == 'W' && game->map[index][1] == 'E'
		&& game->path_we == NULL)
		get_west_texture(game, game->map[index]);
	else if (game->map[index][0] == 'E' && game->map[index][1] == 'A'
		&& game->path_ea == NULL)
		get_east_texture(game, game->map[index]);
}

void	get_textures(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[index])
	{
		check_duplicate_textures(game, index);
		process_texture_line(game, index);
		index++;
	}
	validate_textures(game);
}
