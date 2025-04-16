/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:49:32 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/16 13:01:04 by ruidos-s         ###   ########.fr       */
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
	int		i;

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
		
		i=0;
		while (line[i])
		{
			if(line[i] == 'F' || line[i] == 'C' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
				break;
			if (line[i] == '1')
				in_map = true;
			i++;
		}

		if (in_map)
		{
			if (line[0] == '\n')
			{
				ft_putstr_fd("Error\nEmpty line in map\n", 2);
				free(line);
				free(map_data);
				close(fd);
				exit (1);
			}
		}
		holder = map_data;
		map_data = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	map = ft_split(map_data, '\n');
	free(map_data);
	i = 0;
	while (map[i])
	{
		printf("map[%d]: %s\n", i, map[i]);
		i++;
	}

	close(fd);
	return (map);
}
