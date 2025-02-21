/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:40:06 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/21 12:21:13 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* checks for an alphabetic character;
 in the standard "C" locale, it is equivalent to (isupper(c) || islower(c)). */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
		printf("%d\n", ft_isalpha('Z'));
		printf("%d\n", isalpha('Z'));
		printf("%d\n", isalpha(38463));
}
*/