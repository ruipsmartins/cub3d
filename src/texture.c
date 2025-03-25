#include "./cub3D.h"

void	get_north_texture(t_game *game, char *line)
{
	game->path_no = ft_strdup(line +3);
	printf("NO: %s\n", game->path_no);
}

void	get_south_texture(t_game *game, char *line)
{
	game->path_so = ft_strdup(line +3);
	printf("SO: %s\n", game->path_so);
}

void	get_west_texture(t_game *game, char *line)
{
	game->path_we = ft_strdup(line +3);
	printf("WE: %s\n", game->path_we);
}

void	get_east_texture(t_game *game, char *line)
{
	game->path_ea = ft_strdup(line +3);
	printf("EA: %s\n", game->path_ea);
}

void	get_textures(t_game *game)
{
	int		i;

	i = 0;
	while(game->map[i])
	{
		if (game->map[i][0] == 'N' && game->map[i][1] == 'O' && game->path_no == NULL)
			get_north_texture(game, game->map[i]);
		else if (game->map[i][0] == 'S' && game->map[i][1] == 'O' && game->path_so == NULL)
			get_south_texture(game, game->map[i]);
		else if (game->map[i][0] == 'W' && game->map[i][1] == 'E' && game->path_we == NULL)
			get_west_texture(game, game->map[i]);
		else if (game->map[i][0] == 'E' && game->map[i][1] == 'A' && game->path_ea == NULL)
			get_east_texture(game, game->map[i]);
		else if ((game->map[i][0] == 'N' && game->map[i][1] == 'O' && game->path_no != NULL) ||
			(game->map[i][0] == 'S' && game->map[i][1] == 'O' && game->path_so != NULL) ||
			(game->map[i][0] == 'W' && game->map[i][1] == 'E' && game->path_we != NULL) ||
			(game->map[i][0] == 'E' && game->map[i][1] == 'A' && game->path_ea != NULL))
			ft_printf("Error\nDuplicate texture\n");
		i++;
	}
	if (game->path_no == NULL || game->path_so == NULL || game->path_we == NULL || game->path_ea == NULL)
		ft_printf("Error\nMissing texture\n");

	printf("texture nort: %s\n", game->path_no);
}
