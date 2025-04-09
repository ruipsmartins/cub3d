#include "./cub3D.h"

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
            c == 'E' || c == 'W' || c == '2' || ft_isspace(c));
}


void	check_map(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (game->map_copy[i])
	{
		k = 0;
		printf("i = %c\n", game->map_copy[i][k]);
		while (game->map_copy[i][k])
		{
			if (!is_valid_map_char(game->map_copy[i][k]))
			{
				printf("char: %c\n", game->map_copy[i][k]);
				printf("Error\nInvalid character in map\n");
				free_all_maps(game);
				exit(1);
			}

			// Fix space in map
			if (game->map_copy[i][k] == ' ')
				game->map_copy[i][k] = '1';
			k++;
		}
		i++;
	}
}



int	skip_def(t_game *game)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (game->map[i] && game->map[i][0] != '1'
		&& !ft_isspace(game->map[i][0]))
		i++;
	if (!game->map[i])
	{
		printf("Error\nNo map found\n");
		free_map(game);
		exit(1);
	}
	while (game->map[height])
		height++;
	height = height - i;
	game->map_copy = ft_calloc(height + 1, sizeof(char *)); /// melhor comecar tudo com ft_calloc para nao dar cond jump
	game->map_height = height; // Store the height of the map
	//
	game->map_copy[height] = NULL;
	//
	if (!game->map_copy)
	{
		printf("Error\nMemory allocation failed\n");
		exit(1);
	}
	return (i);
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

void	copy_map(t_game *game)
{
	int		skip;
	char	**map;
	int		k;
	int		i;

	skip = skip_def(game);
	map = game->map + skip;
	k = 0;
	i = 0;
	while (map[i])
	{
			game->map_copy[i] = malloc(sizeof(char) * (game->map_len + 1));
			if (!game->map_copy[i])
			{
				printf("Error\nMemory allocation failed\n");
				exit(1);
			}
			k = 0;
			while (map[i][k] && map[i][k] != '\n')
			{
				if (map[i][k] == '1' || ft_isspace(map[i][k]))
					game->map_copy[i][k] = '1';
				else
					game->map_copy[i][k] = map[i][k];
				k++;
			}
			while (k < game->map_len)
			{
				game->map_copy[i][k] = '2';
				k++;
			}
			game->map_copy[i][k] = '\0';
		i++;
	}
	game->map_copy[i] = NULL;
	print_map(game->map_copy);
	check_map(game);
//print_map(game->map_copy);
}


void	ff_map(t_game *game)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map)
	{
		printf("ERROR\n Failed malloc on ff_map\n");
		exit(1);
	}
	while (game->map_copy[i])
	{
		map[i] = ft_strdup(game->map_copy[i]);
		i++;
	}
	map[i] = NULL;
	flood_fill(game, (int)game->player.y / BLOCK, (int)game->player.x / BLOCK,
		map);
	printf("\n\n AFTER FLOOD FILL \n\n");
	i = 0;
	while(map[i])
		free(map[i++]);
	free(map);
	//print_map(map);
}
