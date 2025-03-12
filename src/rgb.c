#include "./cub3D.h"

void	get_floor_color(t_game *game, char *line)
{
	game->color_floor = ft_strdup(line + 2);
	printf("Floor color: %s\n", game->color_floor);
}

void	get_ceiling_color(t_game *game, char *line)
{
	game->color_ceiling = ft_strdup(line + 2);
	printf("Ceiling color: %s\n", game->color_ceiling);
}

void	get_rgb(t_game *game)
{
	int		i;

	i = 0;
	while(game->map[i])
	{
		if (game->map[i][0] == 'F' && game->color_floor == NULL)
		{
			get_floor_color(game, game->map[i]);
		}
		else if (game->map[i][0] == 'C' && game->color_ceiling == NULL)
		{
			get_ceiling_color(game, game->map[i]);
		}
		else if ((game->map[i][0] == 'F' && game->color_floor != NULL) || (game->map[i][0] == 'C' && game->color_ceiling != NULL))
		{
			printf("Error\nDuplicate floor or ceiling color\n");
		}
		i++;
	}
	if (game->color_floor == NULL || game->color_ceiling == NULL)
	{
		printf("Error\nMissing floor or ceiling color\n");
	}
}


