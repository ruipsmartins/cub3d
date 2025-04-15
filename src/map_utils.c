/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:04:19 by addicted          #+#    #+#             */
/*   Updated: 2025/04/11 18:12:21 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '2' || ft_isspace(c));
}

void	check_map(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	while (game->map_copy[i])
	{
		k = 0;
		while (game->map_copy[i][k])
		{
			if (!is_valid_map_char(game->map_copy[i][k]))
			{
				printf("Error\nInvalid character in map\n");
				free_all_maps(game);
				exit(1);
			}
			if (ft_isspace(game->map_copy[i][k]))
				game->map_copy[i][k] = '1';
			k++;
		}
		i++;
	}
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
