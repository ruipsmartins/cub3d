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

void	copy_map(t_game *game)
{
	int i = 0;
	int k = 0;

	while(game->map[i] && game->map[i][0] != '1' && game->map[i][0] != ' ')
		i++;
	if (!game->map[i])
	{
		printf("Error\nNo map found\n");
		exit(1);
	}
	while(game->map[k])
		k++;
	game->map_copy = malloc(sizeof(char **) * (k - i + 1));
	if (!game->map_copy)
	{
		printf("Error\nMemory allocation failed\n");
		exit(1);
	}
	int j = 0;
	while(game->map[i] && (game->map[i][0] == '1' || game->map[i][0] == ' '))
	{
		game->map_copy[j] = ft_strdup(game->map[i]);
		if (!game->map_copy[j])
		{
			printf("Error\nMemory allocation failed\n");
			exit(1);
		}
		printf("%s\n", game->map_copy[j]);
		i++;
		j++;
	}
	game->map_copy[j] = NULL;
	if (check_map(game))
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
}
