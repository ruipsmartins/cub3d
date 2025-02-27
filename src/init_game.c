/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:48:11 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/25 12:23:29 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	window_size(t_data *data)
{
	int	y;

	y = 0;
	data->map_size_x = (ft_strlen(data->map[0]));
	while (data->map[y])
		y++;
	data->map_size_y = y;
}

void init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->angle = PI / 2;
	player->speed = 0.5;
	player->img_player = NULL;
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;

    player->left_rotate = false;
    player->right_rotate = false;
}



void	init_game(t_data *data)
{
	init_player(data->player);

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_size_x,
			data->map_size_y, "Cub3D");
	data->player->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/player_s.xpm", &data->img_width, &data->img_height);
	data->img_ground = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/fundo.xpm", &data->img_width, &data->img_height);
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/bricksx64.xpm", &data->img_width, &data->img_height);
	map_draw(data);
}
