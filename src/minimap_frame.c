/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:35:00 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/04/11 16:12:01 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Gets the color of a pixel from the image */
static int	get_pixel_color(t_img *src, int pixel_offset)
{
	unsigned char	rgb[3];

	rgb[2] = src->pixel_buffer[pixel_offset + 2];
	rgb[1] = src->pixel_buffer[pixel_offset + 1];
	rgb[0] = src->pixel_buffer[pixel_offset];
	return ((rgb[2] << 16) | (rgb[1] << 8) | rgb[0]);
}

/* Checks if a point is outside the circle */
static bool	is_outside_circle(int dx, int dy, int radius_squared)
{
	return ((dx * dx + dy * dy) > radius_squared);
}

/* Processes a pixel to draw the frame */
static void	process_pixel(t_game *game, int x, int y, int offset)
{
	int		dx;
	int		dy;
	int		pixel_offset;
	int		color;
	t_img	frame;

	frame = game->textures.minimap_frame;
	dx = x - (frame.width / 2);
	dy = y - (frame.height / 2);
	if (is_outside_circle(dx, dy, 100 * 100))
	{
		pixel_offset = (y * frame.size_line) + (x * (frame.bpp / 8));
		color = get_pixel_color(&frame, pixel_offset);
		ft_put_pixel(x + offset, y + offset, color, game);
	}
}

/* Draws the circular frame around the minimap */
void	draw_frame(t_img *src, t_game *game)
{
	int	x;
	int	y;
	int	offset;

	offset = 35;
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			process_pixel(game, x, y, offset);
			x++;
		}
		y++;
	}
}
