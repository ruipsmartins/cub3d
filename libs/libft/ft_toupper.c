/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:57:45 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/21 12:17:58 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts a lower-case letter to the corresponding upper-case letter.
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}

/* #include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("toupper: %c\n", toupper('r'));
	printf("ft_toupper: %c\n", ft_toupper('r'));
	return (0);
}
 */