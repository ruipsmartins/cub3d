/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:35:00 by addicted          #+#    #+#             */
/*   Updated: 2025/04/11 16:21:01 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	check_for_xpm(char *str, t_game *game)
{
	int	len;

	if (!str)
	{
		ft_printf("Error\nMissing texture\n");
		clean_game(game);
	}
	len = ft_strlen(str);
	if (str[len - 1] != 'm' || str[len - 2] != 'p'
		|| str[len - 3] != 'x' || str[len - 4] != '.')
	{
		printf("string = %s \n", str);
		printf("c = %c\n", str[len - 1]);
		printf("Error\nTextures should end with \".xpm\" and have no spaces after\n");
		clean_game(game);
	}
}

void	get_north_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_no = ft_strdup(line + 3);
	printf("NO: %s\n", game->path_no);
}

void	get_south_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_so = ft_strdup(line + 3);
	printf("SO: %s\n", game->path_so);
}

void	get_west_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_we = ft_strdup(line + 3);
	printf("WE: %s\n", game->path_we);
}

void	get_east_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_ea = ft_strdup(line + 3);
	printf("EA: %s\n", game->path_ea);
}
