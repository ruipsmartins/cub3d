#include "./cub3D.h"

int	atoi_for_rgb(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && !ft_isspace(str[i]) && str[i] != ',')
		return (-1);
	return (res * sign);
}

static int	validate_rgb_value(int value)
{
	if (value < 0 || value > 255)
		return (0);
	return (1);
}

static int	combine_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	rgb_str_to_hex(char *rgb_str)
{
	int		rgb[3];
	char	*token;
	int		i;
	int		new_color;

	i = 0;
	token = strtok(rgb_str, ",");
	while (token != NULL && i < 3)
	{
		rgb[i] = atoi_for_rgb(token);
		if (!validate_rgb_value(rgb[i]))
			return (printf("Error\nInvalid RGB format\n") * 0 - 1);
		i++;
		token = strtok(NULL, ",");
	}
	if (i != 3)
	{
		free(token);
		return (printf("Error\nInvalid RGB format\n") * 0 - 1);
	}
	free(token);
	new_color = combine_rgb(rgb[0], rgb[1], rgb[2]);
	return (new_color);
}

void	get_floor_color(t_game *game, char *line)
{
	char	*color_str;
	int		number;

	color_str = ft_strdup(line + 2);
	number = rgb_str_to_hex(color_str);
	game->color_floor = number;
	free(color_str);
	printf("Floor color: %d\n", number);
}

void	get_ceiling_color(t_game *game, char *line)
{
	char	*color_str;
	int		number;

	color_str = ft_strdup(line + 2);
	number = rgb_str_to_hex(color_str);
	game->color_ceiling = number;
	free(color_str);
	printf("Ceiling color: %d\n", game->color_ceiling);
}

static void	check_duplicate_colors(t_game *game, int i)
{
	if ((game->map[i][0] == 'F' && game->color_floor >= 0)
		|| (game->map[i][0] == 'C' && game->color_ceiling >= 0))
	{
		printf("Error\nDuplicate floor or ceiling color\n");
		free_all_maps(game);
		free_path(game);
		exit(1);
	}
}

void	get_rgb(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (game->map[i][0] == 'F' && game->color_floor < 0)
			get_floor_color(game, game->map[i]);
		else if (game->map[i][0] == 'C' && game->color_ceiling < 0)
			get_ceiling_color(game, game->map[i]);
		else
			check_duplicate_colors(game, i);
		i++;
	}
	if (game->color_floor < 0 || game->color_ceiling < 0)
	{
		printf("Error\nMissing floor or ceiling color\n");
		free_all_maps(game);
		free_path(game);
		exit(1);
	}
}


