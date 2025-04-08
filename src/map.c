#include "./cub3D.h"

int        check_map(t_game *game)
{
	int i = 0;
	int k = 0;
	//char c = NULL;

	while(game->map_copy[i])
	{
		k = 0;
		while (game->map_copy[i][k])
		{
			if(game->map_copy[i][k] != '1' && game->map_copy[i][k] != ' ' &&
			 game->map_copy[i][k] != '0' && game->map_copy[i][k] != 'N' &&
			  game->map_copy[i][k] != 'S' && game->map_copy[i][k] != 'W' &&
			   game->map_copy[i][k] != 'E')
			{
				printf("Error\nInvalid character in map\n");
				return (1);
			}
				//Fix space in map
			if(game->map_copy[i][k] == ' ')				
				game->map_copy[i][k] = '1';
			k++;
		}
		i++;
	}
	return (0);
}

// void	allocate_map(t_game *game)
// {
// 	int i = 0;

// 	while(game->map_copy[i])
// 	{
// 		game->map_copy[i] = ft_strdup(game->map_copy[i]);
// 		if (!game->map_copy[i])
// 		{
// 			printf("Error\nMemory allocation failed\n");
// 			exit(1);
// 		}

// 		i++;
// 	}
// }

int	skip_def(t_game *game)
{
	int i = 0;
	int height = 0;

	while (game->map[i] && game->map[i][0] != '1' && !ft_isspace(game->map[i][0]))
		i++;
	if (!game->map[i])
	{
		printf("Error\nNo map found\n");
		exit(1);
	}
	while(game->map[height])
		height++;
	height = height - i;
	game->map_copy = malloc(sizeof(char **) * (height + 1));
	
	
	game->map_height = height; // Store the height of the map

	if (!game->map_copy)
	{
		printf("Error\nMemory allocation failed\n");
		exit(1);
	}
	return (i);
}

void print_map(char **map)
{
	int i;

	i = 0;
	while(map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	copy_map(t_game *game)
{
	int skip = skip_def(game);
	char **map = game->map + skip;
	int k = 0;
	int i = 0;
	while(map[i])
	{
		if (map[i][0] == '1' || ft_isspace(map[i][0]))
		{
			game->map_copy[i] = malloc (sizeof(char) * game->map_len + 1);
			if (!game->map_copy[i])
			{
				printf("Error\nMemory allocation failed\n");
				exit(1);
			}
			k = 0;
			while(map[i][k] && map[i][k] != '\n')
			{
				if (map[i][k] == '1' || ft_isspace(map[i][k]))
					game->map_copy[i][k] = '1';
				else
				game->map_copy[i][k] = map[i][k];
				k++;
			}
			while(k < game->map_len)
			{
				game->map_copy[i][k] = '2';
				k++;
			}
			game->map_copy[i][k] = '\0';
		}
		else if (!ft_isspace(map[i][0]) && map[i][0] != '1')
		{
			printf("Error\nInvalid map\n");
			exit(1);
		}
		i++;
	}
	// Null-terminate the map_copy array
	game->map_copy[i] = NULL;

	print_map(game->map_copy);
}


/*
void copy_map(t_game *game)
{
	int i = skip_def(game);
	int j = 0;
	int len = i;
	while (game->map[len])
	len++;
	
	game->map_copy = malloc(sizeof(char *) * (len + 1));
	while (game->map[i] && (game->map[i][0] == '1' || game->map[i][0] == ' '))
	{
		game->map_copy[j] = ft_strdup(game->map[i]);
		if (!game->map_copy[j])
		{
			printf("Error\nMemory allocation failed\n");
			exit(1);
		}
		i++;
		j++;
	}
	if (game->map[i] && game->map[i][0] != '1' && game->map[i][0] != ' ')
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
	game->map_copy[j] = NULL;
	if (check_map(game))
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
	printf("\n");
	print_map(game->map_copy);
}

*/

void ff_map(t_game *game)
{
	int i = 0;

	char **map;
	map = malloc(sizeof(char **) * game->map_height + 1);
	if (!map)
	{
		printf("ERROR\n Failed malloc on ff_map\n");
		exit(1);
	}
	while(game->map_copy[i])
	{
		map[i] = ft_strdup(game->map_copy[i]);
		i++;
	}
	map[i] = NULL;
	flood_fill(game, (int)game->player.y / BLOCK, (int)game->player.x / BLOCK, map);
	printf("\n\n AFTER FLOOD FILL \n\n");
	print_map(map);
}
