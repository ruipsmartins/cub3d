/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:53:57 by addicted          #+#    #+#             */
/*   Updated: 2025/04/16 14:26:35 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	get_floor_color(t_game *game, char *line)
{
	char	*color_str;
	int		number;

	color_str = ft_strdup(line + 1);
	number = rgb_str_to_hex(color_str);
	if (number < 0)
	{
		free(color_str);
		clean_game(game);
	}
	game->color_floor = number;
	free(color_str);
}

void	get_ceiling_color(t_game *game, char *line)
{
	char	*color_str;
	int		number;

	color_str = ft_strdup(line + 1);
	number = rgb_str_to_hex(color_str);
	if (number < 0)
	{
		free(color_str);
		clean_game(game);
	}
	game->color_ceiling = number;
	free(color_str);
}

static void	check_duplicate_colors(t_game *game, int i)
{
	if ((game->map[i][0] == 'F' && game->color_floor >= 0)
		|| (game->map[i][0] == 'C' && game->color_ceiling >= 0))
	{
		printf("Error\nDuplicate floor or ceiling color\n");
		free_all_maps(game);
		free_path(game);
		exit(1);
	}
}

void	get_rgb(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (game->map[i][0] == 'F' && game->color_floor < 0)
			get_floor_color(game, game->map[i]);
		else if (game->map[i][0] == 'C' && game->color_ceiling < 0)
			get_ceiling_color(game, game->map[i]);
		else
			check_duplicate_colors(game, i);
		i++;
	}
	if (game->color_floor < 0 || game->color_ceiling < 0)
	{
		printf("Error\nMissing floor or ceiling color\n");
		free_all_maps(game);
		free_path(game);
		exit(1);
	}
}
