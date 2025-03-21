/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:28 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/21 16:19:22 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	should_update_frame(void)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	long					elapsed_time;
	int						frame_time;

	frame_time = 16667; // 16.667ms para ~60 FPS
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000000
		+ (current_time.tv_usec - last_time.tv_usec);
	if (elapsed_time < frame_time)
		return (0); // Ainda não passou o tempo necessário
	last_time = current_time; // Atualiza o tempo do último frame
	return (1);               // Indica que é hora de atualizar o frame
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	if (!should_update_frame())
		return (0); // Se não passou tempo suficiente, sai
	player = &game->player;
	move_player(player, game);
	clear_image(game);
	// ft_put_img(game, game->img_background,0, 0);
	// mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->screen_img.img, 0, 0);
	fraction = PI / 3 / WINDOW_WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	if (DEBUG)
	{
		// meter aqui função para mostrar os raios e transformar em minimapa
		draw_map(game);
		draw_square(player->x, player->y, 10, 0x00FF00, game);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	game.map = open_map(argv[1]);
	init_game(&game);
	get_textures(&game);
	get_rgb(&game);
	
	mlx_hook(game.win, DestroyNotify, NoEventMask, clean_game, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_wall.img, 200, 200);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
