#include "./cub3D.h"

int ft_atoi_for_rgb(const char *str)
{
	int i;
	int sign;
	int res;

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
int rgb_str_to_hex(char *rgb_str)
{
	int rgb[3];  // Stores R, G, B values
	char *token;
	int i = 0;
	int new_color;

	// Split the string by commas
	token = strtok(rgb_str, ",");
	while (token != NULL && i < 3)
	{
		rgb[i++] = ft_atoi_for_rgb(token); // Convert token to integer
		if (rgb[i - 1] < 0)
			return (printf("Error\nInvalid RGB format\n") * 0 - 1); // Error handling
		token = strtok(NULL, ",");
	}
	if (i != 3)
	{
		free(token);
		return (printf("Error\nInvalid RGB format\n") * 0 - 1); // Error handling
	}
	free(token);
	new_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2]; // Combine R, G, B into a single integer
	return new_color;
}

void	get_floor_color(t_game *game, char *line)
{
	char	*color_str;
	int 		number;

	color_str = ft_strdup(line + 2);
	number = rgb_str_to_hex(color_str);
	game->color_floor = number;
	free(color_str);
	printf("Floor color: %d\n", number);
}

void	get_ceiling_color(t_game *game, char *line)
{
	char	*color_str;
	int 		number;

	color_str = ft_strdup(line + 2);
	number = rgb_str_to_hex(color_str);
	game->color_ceiling = number;
	free(color_str);
	printf("Ceiling color: %d\n", game->color_ceiling);
}

void	get_rgb(t_game *game)
{
	int		i;

	i = 0;
	while(game->map[i])
	{
		if (game->map[i][0] == 'F' && game->color_floor < 0)
		{
			get_floor_color(game, game->map[i]);
		}
		else if (game->map[i][0] == 'C' && game->color_ceiling < 0)
		{
			get_ceiling_color(game, game->map[i]);
		}
		else if ((game->map[i][0] == 'F' && game->color_floor >= 0) || (game->map[i][0] == 'C' && game->color_ceiling >= 0))
		{
			printf("Error\nDuplicate floor or ceiling color\n");
			free_all_maps(game);
			free_path(game);
			exit(1);
		}
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


