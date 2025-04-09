/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:28 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/09 18:53:39 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"


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
	mlx_put_image_to_window(game->mlx, game->win, game->screen_img.img, 0, 0);
	fraction = PI / 3 / WINDOW_WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		draw_ray_cast(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	if (1)
	{
		// meter aqui função para mostrar os raios e transformar em minimapa
		draw_minimap(game);
		//draw_square(player->x, player->y, 10, 0x00FF00, game);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	ft_memset(&game, '\0', sizeof(t_game)); // This initializes all members to 0/NULL 
	//Ver se podemos fazer isto

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	game.map = open_map(argv[1]);
	init_game(&game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, clean_game, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
