/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:35:00 by addicted          #+#    #+#             */
/*   Updated: 2025/04/11 15:56:46 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	atoi_for_rgb(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && str[i] != ',')
		return (-1);
	return (res * sign);
}

int	validate_rgb_value(int value)
{
	if (value < 0 || value > 255)
		return (0);
	return (1);
}

int	combine_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	rgb_str_to_hex(char *rgb_str)
{
	int		rgb[3];
	char	*token;
	int		i;
	int		new_color;

	i = 0;
	token = ft_strtok(rgb_str, ",");
	while (token != NULL && i < 3)
	{
		rgb[i] = atoi_for_rgb(token);
		if (!validate_rgb_value(rgb[i]))
			return (write(2, "Error\nInvalid RGB format\n", 26) * 0 - 1);
		i++;
		token = ft_strtok(NULL, ",");
	}
	if (i != 3)
	{
		free(token);
		return (write(2, "Error\nInvalid RGB format\n", 26) * 0 - 1);
	}
	free(token);
	new_color = combine_rgb(rgb[0], rgb[1], rgb[2]);
	return (new_color);
}
