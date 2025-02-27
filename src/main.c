/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:28 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/25 12:03:13 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	close_game(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->player->img_player);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_map(data);
	ft_putchar_fd('\n', 1);
	exit(0);
}


int main(int argc, char **argv)
{
	t_data data;
	t_player player;
	data.map_size_x = 1920;
	data.map_size_y = 1080;
	data.player = &player;
	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	data.map = open_map(argv[1]);
	init_game(&data);
	//data_init(&data);

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, player.img_player, player.x, player.y);
	mlx_hook(data.win_ptr, DestroyNotify, NoEventMask, close_game, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, (void *)move_player, &data); // Corrigido para passar o ponteiro correto

	mlx_loop(data.mlx_ptr);
	return (0);
}