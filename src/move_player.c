/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:14:38 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/27 10:45:08 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define SPEED 0.5
#define ANGLE_SPEED 0.02
#define PI 3.14159265359
#define TILE_SIZE 64
#define FOV 60 * (PI / 180)  // Converte graus para radianos
#define NUM_RAYS 500  // Número de raios (um por cada pixel da largura da tela)
#define RAY_STEP 20 // Distância percorrida por cada iteração do raio

int key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up = true;
	if (keycode == S)
		data->player->key_down = true;
	if (keycode == A)
		data->player->key_left = true;
	if (keycode == D)
		data->player->key_right = true;
	if (keycode == LEFT)
		data->player->left_rotate = true;
	if (keycode == RIGHT)
		data->player->right_rotate = true;
	if (keycode == 65307) // ESC
		close_game(data);
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up = false;
	if (keycode == S)
		data->player->key_down = false;
	if (keycode == A)
		data->player->key_left = false;
	if (keycode == D)
		data->player->key_right = false;
	if (keycode == LEFT)
		data->player->left_rotate = false;
	if (keycode == RIGHT)
		data->player->right_rotate = false;
	return (0);
}

void cast_rays(t_player *player, t_data *data)
{
    float ray_angle;
    float angle_step = FOV / NUM_RAYS;  // Passo de variação do ângulo
    int ray;

    for (ray = 0; ray < NUM_RAYS; ray++)
    {
        ray_angle = player->angle - (FOV / 2) + (ray * angle_step);  // Ângulo do raio atual

        float ray_x = player->x;
        float ray_y = player->y;

        // Incrementa o raio até encontrar uma parede
        while (1)
        {
            ray_x += cos(ray_angle) * RAY_STEP;
            ray_y += sin(ray_angle) * RAY_STEP;

            int map_x = (int)(ray_x / TILE_SIZE);
            int map_y = (int)(ray_y / TILE_SIZE);

            if (data->map[map_y][map_x] == '1')  // Se encontrou uma parede, para
                break;

            mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray_x, ray_y, 0xFF0000); // Desenha o raio em vermelho
        }
    }
}

void move_player(t_data *data)
{
	t_player *player = data->player;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);
	bool moved = false;

	// Atualizar rotação
	if (player->left_rotate)
	{
		player->angle -= ANGLE_SPEED;
		moved = true;
	}
	if (player->right_rotate)
	{
		player->angle += ANGLE_SPEED;
		moved = true;
	}
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;

	// Atualizar posição
	if (player->key_up)
	{
		player->x += cos_angle * SPEED;
		player->y += sin_angle * SPEED;
		moved = true;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * SPEED;
		player->y -= sin_angle * SPEED;
		moved = true;
	}
	if (player->key_left)
	{
		player->x += sin_angle * SPEED;
		player->y -= cos_angle * SPEED;
		moved = true;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * SPEED;
		player->y += cos_angle * SPEED;
		moved = true;
	}

	// Atualizar a janela apenas se o jogador tiver se movido
	if (moved)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		map_draw(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, player->img_player,
				player->x, player->y);
		cast_rays(data->player, data);
	}
}



static void	update_player(t_data *data, char c)
{
	t_player	*player;
	player = data->player;
	mlx_destroy_image(data->mlx_ptr, player->img_player);
	if (c == 'w')
	player->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
				"./img/player_w.xpm", &data->img_width, &data->img_height);
	else if (c == 'a')
	player->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
				"./img/player_a.xpm", &data->img_width, &data->img_height);
	else if (c == 's')
	player->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
				"./img/player_s.xpm", &data->img_width, &data->img_height);
	else if (c == 'd')
	player->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
				"./img/player_d.xpm", &data->img_width, &data->img_height);
}

void	move_player_w(t_data *data)
{
	update_player(data, 'w');
	data->player->y -= data->player->speed;	
}

void	move_player_a(t_data *data)
{
	update_player(data, 'a');
	data->player->x -= data->player->speed;
}

void	move_player_s(t_data *data)
{
	update_player(data, 's');
	data->player->y += data->player->speed;
}

void	move_player_d(t_data *data)
{
	update_player(data, 'd');
	data->player->x += data->player->speed;
}
