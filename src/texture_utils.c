/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:35:00 by addicted          #+#    #+#             */
/*   Updated: 2025/04/16 10:41:07 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	check_for_xpm(char *str, t_game *game)
{
	int	len;

	if (!str)
	{
		ft_putstr_fd("Error\nMissing texture\n", 2);
		clean_game(game);
	}
	len = ft_strlen(str);
	if (str[len - 1] != 'm' || str[len - 2] != 'p'
		|| str[len - 3] != 'x' || str[len - 4] != '.')
	{
		ft_putstr_fd("Error\nTextures should end with \".xpm\"", 2);
		ft_putstr_fd(" and have no spaces after\n", 2);
		clean_game(game);
	}
}

void	get_north_texture(t_game *game, char *line)
{
	char	*trimmed;

	check_for_xpm(line, game);
	trimmed = ft_strtrim((line + 2), " ");
	game->path_no = ft_strdup(trimmed);
	free(trimmed);
}

void	get_south_texture(t_game *game, char *line)
{
	char	*trimmed;

	check_for_xpm(line, game);
	trimmed = ft_strtrim((line + 2), " ");
	game->path_so = ft_strdup(trimmed);
	free(trimmed);
}

void	get_west_texture(t_game *game, char *line)
{
	char	*trimmed;

	check_for_xpm(line, game);
	trimmed = ft_strtrim((line + 2), " ");
	game->path_we = ft_strdup(trimmed);
	free(trimmed);
}

void	get_east_texture(t_game *game, char *line)
{
	char	*trimmed;

	check_for_xpm(line, game);
	trimmed = ft_strtrim((line + 2), " ");
	game->path_ea = ft_strdup(trimmed);
	free(trimmed);
}
