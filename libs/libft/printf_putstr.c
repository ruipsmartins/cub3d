/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:33:15 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/21 12:19:13 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string ’s’ to the given file
descriptor. */
int	printf_putstr(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		s = ("(null)");
	while (*s)
	{
		printf_putchar(*s++);
		count++;
	}
	return (count);
}
