#include "./cub3D.h"

static void	check_for_xpm(char *str, t_game *game);
static void	get_north_texture(t_game *game, char *line);
static void	get_south_texture(t_game *game, char *line);
static void	get_west_texture(t_game *game, char *line);
static void	get_east_texture(t_game *game, char *line);
static void	check_duplicate_textures(t_game *game, int index);
static void	process_texture_line(t_game *game, int index);
static void	validate_textures(t_game *game);

static void	check_for_xpm(char *str, t_game *game)
{
	int	len;

	if (!str)
	{
		ft_printf("Error\nMissing texture\n");
		clean_game(game);
	}
	len = ft_strlen(str);
	if (str[len - 1] != 'm' || str[len - 2] != 'p'
		|| str[len - 3] != 'x' || str[len - 4] != '.')
	{
		printf("string = %s \n", str);
		printf("c = %c\n", str[len - 1]);
		printf("Error\nTextures should end with \".xpm\" and have no spaces after\n");
		clean_game(game);
	}
}

static void	get_north_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_no = ft_strdup(line + 3);
	printf("NO: %s\n", game->path_no);
}

static void	get_south_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_so = ft_strdup(line + 3);
	printf("SO: %s\n", game->path_so);
}

static void	get_west_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_we = ft_strdup(line + 3);
	printf("WE: %s\n", game->path_we);
}

static void	get_east_texture(t_game *game, char *line)
{
	check_for_xpm(line, game);
	game->path_ea = ft_strdup(line + 3);
	printf("EA: %s\n", game->path_ea);
}

static void	check_duplicate_textures(t_game *game, int index)
{
	if ((game->map[index][0] == 'N' && game->map[index][1] == 'O'
			&& game->path_no != NULL)
		|| (game->map[index][0] == 'S' && game->map[index][1] == 'O'
			&& game->path_so != NULL)
		|| (game->map[index][0] == 'W' && game->map[index][1] == 'E'
			&& game->path_we != NULL)
		|| (game->map[index][0] == 'E' && game->map[index][1] == 'A'
			&& game->path_ea != NULL))
		ft_printf("Error\nDuplicate texture\n");
}

static void	process_texture_line(t_game *game, int index)
{
	if (game->map[index][0] == 'N' && game->map[index][1] == 'O'
		&& game->path_no == NULL)
		get_north_texture(game, game->map[index]);
	else if (game->map[index][0] == 'S' && game->map[index][1] == 'O'
		&& game->path_so == NULL)
		get_south_texture(game, game->map[index]);
	else if (game->map[index][0] == 'W' && game->map[index][1] == 'E'
		&& game->path_we == NULL)
		get_west_texture(game, game->map[index]);
	else if (game->map[index][0] == 'E' && game->map[index][1] == 'A'
		&& game->path_ea == NULL)
		get_east_texture(game, game->map[index]);
}

static void	validate_textures(t_game *game)
{
	if (game->path_no == NULL || game->path_so == NULL
		|| game->path_we == NULL || game->path_ea == NULL)
	{
		ft_printf("Error\nMissing texture\n");
		clean_game(game);
	}
}

void	get_textures(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[index])
	{
		check_duplicate_textures(game, index);
		process_texture_line(game, index);
		index++;
	}
	validate_textures(game);
}
