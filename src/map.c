/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:10:39 by addicted          #+#    #+#             */
/*   Updated: 2025/04/11 18:10:40 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

static int	init_map_copy(t_game *game, int i)
{
	int	height;

	height = 0;
	while (game->map[height])
		height++;
	height = height - i;
	game->map_copy = ft_calloc(height + 1, sizeof(char *));
	game->map_height = height;
	game->map_copy[height] = NULL;
	if (!game->map_copy)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		clean_game(game);
	}
	return (height);
}

int	skip_def(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i] && game->map[i][0] != '1'
		&& !ft_isspace(game->map[i][0]))
		i++;
	if (!game->map[i])
	{
		ft_putstr_fd("Error\nNo map found\n", 2);
		free_single_map(game->map);
		exit(1);
	}
	return (i);
}

static void	allocate_map_line(t_game *game, int i)
{
	game->map_copy[i] = malloc(sizeof(char) * (game->map_len + 1));
	if (!game->map_copy[i])
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		clean_game(game);
		exit(1);
	}
}

static void	copy_map_line(char *src, int i, t_game *game)
{
	int	k;

	k = 0;
	while (src[k] && src[k] != '\n')
	{
		if (src[k] == '1' || ft_isspace(src[k]))
			game->map_copy[i][k] = '1';
		else if (src[k] == '2')
		{
			ft_putstr_fd("Error\nInvalid map\n", 2);
			clean_game(game);
		}
		else
			game->map_copy[i][k] = src[k];
		k++;
	}
	while (k < game->map_len)
	{
		game->map_copy[i][k] = '2';
		k++;
	}
	game->map_copy[i][k] = '\0';
}

void	copy_map(t_game *game)
{
	int		skip;
	char	**map;
	int		i;

	skip = skip_def(game);
	map = game->map + skip;
	init_map_copy(game, skip);
	i = 0;
	while (map[i])
	{
		allocate_map_line(game, i);
		copy_map_line(map[i], i, game);
		i++;
	}
	game->map_copy[i] = NULL;
	check_map(game);
}
