/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:35:55 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/03/31 11:47:02 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

// Executa o algoritmo DDA para encontrar a colisão com a parede
void	perform_dda(t_ray *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->ray_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->ray_y += ray->step_y;
			ray->side = 1;
		}
		if (touch(ray->ray_x, ray->ray_y, game))
			ray->hit = 1;
	}
}

// Calcula a projeção da parede com base na distância do raio
void	calculate_wall_projection(t_ray *ray, t_player *player, t_game *game)
{
	// Calcula a distância perpendicular para evitar o efeito "fish-eye"
	ray->dist = fixed_dist(player->x, player->y, ray->ray_x, ray->ray_y, game);
	// Calcula a altura da parede
	ray->height = (BLOCK / ray->dist) * (WINDOW_WIDTH / 2);
	ray->start_y = (WINDOW_HEIGHT - ray->height) / 2;
	ray->end = ray->start_y + ray->height;
	// Garante que os limites fiquem dentro da janela
	if (ray->start_y < 0)
		ray->start_y = 0;
	if (ray->end >= WINDOW_HEIGHT)
		ray->end = WINDOW_HEIGHT - 1;
}

// Mapeia a textura e desenha a coluna correspondente à parede
void	render_wall_slice(t_ray *ray, int column, t_game *game)
{
	float	texture_pos;
	int		y;
	int		texture_y;
	int		color;

	// Seleciona a textura consoante a orientação da parede
	if (ray->side == 1)
	{
		if (ray->step_y == -1)
			ray->wall = game->textures.wall_N;
		else
			ray->wall = game->textures.wall_S;
	}
	else
	{
		if (ray->step_x == -1)
			ray->wall = game->textures.wall_W;
		else
			ray->wall = game->textures.wall_E;
	}
	// Ajuste no mapeamento horizontal
	if (ray->side == 0)
		ray->texture_x = (int)(ray->ray_y) % ray->wall.width;
	else
		ray->texture_x = (int)(ray->ray_x) % ray->wall.width;
	if (ray->wall.img == game->textures.wall_S.img)
		ray->texture_x = ray->wall.width - ray->texture_x - 1;// melhorar isto aqui
	if (ray->wall.img == game->textures.wall_W.img)
		ray->texture_x = ray->wall.width - ray->texture_x - 1;
	// Calcula o "step" para percorrer a textura
	ray->texture_step = (float)ray->wall.height / ray->height;
	texture_pos = (ray->start_y - (WINDOW_HEIGHT - ray->height) / 2)
		* ray->texture_step;
	y = ray->start_y;
	while (y < ray->end)
	{
		texture_y = (int)texture_pos % ray->wall.height;
		color = get_texture_pixel(&ray->wall, ray->texture_x, texture_y);
		ft_put_pixel(column, y, color, game);
		texture_pos += ray->texture_step;
		y++;
	}
}

// Função principal que chama as subfunções para o raycasting
void	draw_ray_cast(t_player *player, t_game *game, float ray_angle, int i)
{
	t_ray	ray;

	init_ray(&ray, player, ray_angle);
	perform_dda(&ray, game);
	calculate_wall_projection(&ray, player, game);
	render_wall_slice(&ray, i, game);
}
