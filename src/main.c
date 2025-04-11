/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:28 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 15:36:11 by addicted         ###   ########.fr       */
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
		return (0);
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
		draw_minimap(game);
	return (0);
}
void	check_cub(char *str)
{
	if(str[strlen(str) -1] != 'b' || str[strlen(str) -2] != 'u' ||
	 str[strlen(str) -3] != 'c' || str[strlen(str) -4] != '.')
		{
			printf("ERROR\nMap file has to end with \".cub\"\n");
			exit(1);
		}
}
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	ft_memset(&game, '\0', sizeof(t_game)); // This initializes all members to 0/NULL 
	//Ver se podemos fazer isto
	check_cub(argv[1]);
	game.map = open_map(argv[1]);
	init_game(&game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, clean_game, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
