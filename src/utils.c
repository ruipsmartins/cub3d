/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:31:19 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 17:34:40 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	draw_square(int x, int y, int size, t_game *game)
{
	int	i;
	int	j;
	int	color;

	if (size == 4)
		color = 0xFF0000;
	else if (size == 16)
		color = 0x0000FF;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_put_pixel(x + i, y + j, color, game);
			j++;
		}
		i++;
	}
}

// our own put_img function
void	ft_put_img(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, image, x * 64, y * 64);
}

// our own put_pixel function
void	ft_put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	index = (x * game->screen_img.bpp / 8) + (y * game->screen_img.size_line);
	game->screen_img.pixel_buffer[index] = color & 0xFF;
	game->screen_img.pixel_buffer[index + 1] = (color & 0xFF00) >> 8;
	game->screen_img.pixel_buffer[index + 2] = (color & 0xFF0000) >> 16;
}

// our own clear_image function
void	clear_image(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		if (y < WINDOW_HEIGHT / 2)
			color = game->color_ceiling;
		else
			color = game->color_floor;
		while (x < WINDOW_WIDTH)
		{
			ft_put_pixel(x, y, color, game);
			x++;
		}
		y++;
	}
}

// function to check if the frame should be updated
int	should_update_frame(void)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	long					elapsed_time;
	int						frame_time;

	frame_time = 26667;
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000000
		+ (current_time.tv_usec - last_time.tv_usec);
	if (elapsed_time < frame_time)
		return (0);
	last_time = current_time;
	return (1);
}
