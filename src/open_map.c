/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:49:32 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/16 11:55:56 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**open_map(char *path)
{
	int		fd;
	char	*line;
	char	*map_data;
	char	*holder;
	char	**map;
	bool	in_map;

	in_map = false;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_data = ft_strdup("");
	while (true)
	{
		line = get_next_line(fd);
		printf("line: %s\n", line);
		if (!line)
			break ;
		if (line[0] == '1')
			in_map = true;
		if (in_map)
		{
			if ( line[0] == '\n')
			{
				ft_putstr_fd("Empty line in map\n", 2);
				free(line);
				free(map_data);
				close(fd);
				return (NULL);
			}
		}
		holder = map_data;
		map_data = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	map = ft_split(map_data, '\n');
	free(map_data);
	close(fd);
	return (map);
}
