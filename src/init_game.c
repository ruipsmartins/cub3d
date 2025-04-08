/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/08 14:53:59 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	init_texture_and_rgb(t_game *game)
{
	game->path_no = NULL;
	game->path_so = NULL;
	game->path_we = NULL;
	game->path_ea = NULL;
	game->color_floor = -1;
	game->color_ceiling = -1;
	game->textures.wall_E.img = NULL;
	game->textures.wall_W.img = NULL;
	game->textures.wall_N.img = NULL;
	game->textures.wall_S.img = NULL;
}


void load_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Erro ao carregar a textura %s\n", path);
		game->return_value = 1;
		clean_game(game);
	}
	texture->pixel_buffer = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

int flood_fill(t_game *game, int y, int x, char **map)
{
	if (y < 0 || y > game->map_height || x < 0 || x >= game->map_len)
		return (0);
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == '2')
	{
		printf("\n\n AFTER FLOOD FILL \n\n");
		print_map(map);
		printf("Error\nMap not closed\n");
		exit(1);
	}
	map[y][x] = '1';
	flood_fill(game, y + 1, x, map);
	flood_fill(game, y - 1, x, map);
	flood_fill(game, y, x + 1, map);
	flood_fill(game, y, x - 1, map);
	return (1);
}

void load_textures(t_game *game)
{
	load_texture(game, &game->textures.wall_N, game->path_no);
	load_texture(game, &game->textures.wall_S, game->path_so);
	load_texture(game, &game->textures.wall_W, game->path_we);
	load_texture(game, &game->textures.wall_E, game->path_ea);
}

void	init_game(t_game *game)
{
	game->return_value = 0;

	map_len(game);
	init_texture_and_rgb(game);
	copy_map(game);
	init_player(game);
	ff_map(game);
	get_textures(game);
	get_rgb(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nFailed to initialize mlx\n");
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
	{
		printf("Error\nFailed to create window\n");
		exit(1);
	}
	game->screen_img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->screen_img.pixel_buffer = mlx_get_data_addr(game->screen_img.img, &game->screen_img.bpp, &game->screen_img.size_line, &game->screen_img.endian);
	load_textures(game);
	init_player(game);

	
	// int x = (int)game->player.x / BLOCK;
	// int y = (int)game->player.y / BLOCK;
	// game->map = game->map + skip_def(game);
	// flood_fill(game, y, x);

}

void	map_len(t_game *game)
{
	int size;
	int i;

	i = 0;
	size = ft_strlen(game->map[i]);
	while(game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) > size)
			size = ft_strlen(game->map[i]);
		i++;
	}

	game->map_len = size;
}

void	map_height(t_game *game)
{
	int i;

	i = 0;
	while(game->map[i])
		i++;
	game->map_height = i;
}

void	find_player_pos(t_game *game)
{
	int x;
	int y;
	
	y = 0;
	game->player.x = 0;
	game->player.y = 0;
	
	while(y <= game->map_height)
	{
		x = 0;
		if(!game->map_copy[y])
			break;
		while(game->map_copy[y][x])
		{
			if (game->map_copy[y][x] == 'N' || game->map_copy[y][x] == 'S' ||
			 game->map_copy[y][x] == 'W' || game->map_copy[y][x] == 'E')
			{
				if (game->player.x)
				{
					printf("Error\nPlayer positions\n");
					exit(1);
				}
				printf("x: %d y: %d\n", x, y);
				game->player.x = x;
				game->player.y = y;
			}
			x++;
		}
		
		y++;
	}

}
void	find_player_angle(t_game *game)
{
	game->player.angle = -1;
	if(game->player.x == 0 || game->player.y == 0)
	{
		printf("Error\nNo player position found\n");
		exit(1);
	}
	printf("x: %f y: %f\n", game->player.x, game->player.y);
	if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'S')
		game->player.angle = PI / 2;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'W')
		game->player.angle = PI;
	else if (game->map_copy[(int)game->player.y][(int)game->player.x] == 'E')
		game->player.angle = 0;
	printf("angle: %f\n", game->player.angle);
	if(game->player.angle == -1)
	{
		printf("x: %d y: %d\n", (int)game->player.x, (int)game->player.y);
		printf("map: %c\n", game->map_copy[(int)game->player.y][(int)game->player.x]);
		printf("Error\nInvalid player position\n");
		exit(1);
	}
	game->player.x *= BLOCK;
	game->player.y *= BLOCK;
}


void	init_player(t_game *game)
{
	//ft_bzero(&game->player, sizeof(t_player));
	printf("init_player\n");
	find_player_pos(game);
	find_player_angle(game);
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_right = false;
	game->player.key_left = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}