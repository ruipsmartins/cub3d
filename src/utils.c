
#include "./cub3D.h"

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

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
	int y = 0;
	while (y < WINDOW_HEIGHT)
	{
		int x = 0;
		int color;

		if (y < WINDOW_HEIGHT / 2)
			color = game->color_ceiling; // Azul claro para o teto
		else
			color = game->color_floor; // Castanho para o chão

		while (x < WINDOW_WIDTH)
		{
			ft_put_pixel(x, y, color, game);
			x++;
		}
		y++;
	}
}

int	should_update_frame(void)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	long					elapsed_time;
	int						frame_time;

	frame_time = 26667; // 16.667ms para ~60 FPS
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000000
		+ (current_time.tv_usec - last_time.tv_usec);
	if (elapsed_time < frame_time)
		return (0); // Ainda não passou o tempo necessário
	last_time = current_time; // Atualiza o tempo do último frame
	return (1);               // Indica que é hora de atualizar o frame
}

