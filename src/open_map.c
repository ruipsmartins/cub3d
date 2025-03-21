/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:49:32 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/21 11:34:59 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
}

// static void check_newlines (char *line, char *holder)
// {
// 	if (line[0] == '\n')
// 	{
// 		ft_printf("newline no mapa\n");
// 		free(holder);
// 		free(line);
// 		exit(1);
// 	}
//}

void draw_map(t_game *game)
{
	char **map = game->map_copy; //tava map so
	int color = 0x0000FF;
	(void)color;
	int y = 0;

	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				//draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
				ft_put_img(game, game->img_wall.img, x, y);
			}
			x++;
		}
		y++;
	}
}

char	**open_map(char *path)
{
	int		fd;
	char	*line;
	char	*map_data;
	char	*holder;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_data = ft_strdup("");
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		holder = map_data;
		//check_newlines(line, holder);
		map_data = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	map = ft_split(map_data, '\n');
	free(map_data);
	close(fd);
	return (map);
}
