/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:11:35 by addicted          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	flood_fill(t_game *game, int y, int x, char **map)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_len)
	{
		ft_putstr_fd("Error\nFlood fill out of bounds\n", 2);
		free_single_map(map);
		clean_game(game);
	}
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == '2')
	{
		ft_putstr_fd("Error\nMap not closed\n", 2);
		free_single_map(map);
		clean_game(game);
	}
	map[y][x] = '1';
	flood_fill(game, y + 1, x, map);
	flood_fill(game, y - 1, x, map);
	flood_fill(game, y, x + 1, map);
	flood_fill(game, y, x - 1, map);
	return (1);
}

void	check_wrong_options(t_game *game)
{
	int		i;
	char	*str;

	i = 0;
	str = game->map[i];
	while (str)
	{
		if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
			&& str[0] != 'F' && str[0] != 'C' && str[0] != '1' && str[0] != '0'
			&& !ft_isspace(str[0]))
		{
			ft_putstr_fd("Error\nWrong options on map file\n", 2);
			clean_game(game);
		}
		if (str[0] == 'N' || str[0] == 'S' || str[0] == 'W' || str[0] == 'E')
		{
			if ((ft_strncmp(str, "NO", 2) * ft_strncmp(str, "SO", 2)
					* ft_strncmp(str, "WE", 2) * ft_strncmp(str, "EA", 2)) != 0)
			{
				ft_putstr_fd("Error\nWrong options on map file\n", 2);
				clean_game(game);
			}
		}
		str = game->map[++i];
	}
}

void	map_len(t_game *game)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(game->map[i]);
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) > size)
			size = ft_strlen(game->map[i]);
		i++;
	}
	game->map_len = size;
}

void	map_height(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		i++;
	game->map_height = i;
}

void	ff_map(t_game *game)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map)
	{
		ft_putstr_fd("Error\nFailed malloc on ff_map\n", 2);
		clean_game(game);
	}
	while (game->map_copy[i])
	{
		map[i] = ft_strdup(game->map_copy[i]);
		i++;
	}
	map[i] = NULL;
	flood_fill(game, (int)game->player.y / BLOCK, (int)game->player.x / BLOCK,
		map);
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
