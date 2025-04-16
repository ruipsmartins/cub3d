/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:19 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'F' || line[i] == 'C' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (false);
		if (line[i] == '1')
			return (true);
		i++;
	}
	return (false);
}

static void	check_empty_line(char *line, char *map_data, int fd)
{
	if (line[0] == '\n')
	{
		ft_putstr_fd("Error\nEmpty line in map\n", 2);
		free(line);
		free(map_data);
		close(fd);
		exit(1);
	}
}

static char	*read_map_data(int fd)
{
	char	*line;
	char	*map_data;
	char	*holder;
	bool	in_map;

	in_map = false;
	map_data = ft_strdup("");
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map_line(line))
			in_map = true;
		if (in_map)
			check_empty_line(line, map_data, fd);
		holder = map_data;
		map_data = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	return (map_data);
}

char	**open_map(char *path)
{
	int		fd;
	char	*map_data;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_data = read_map_data(fd);
	close(fd);
	map = ft_split(map_data, '\n');
	free(map_data);
	return (map);
}
