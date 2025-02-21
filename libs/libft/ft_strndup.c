/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:35:32 by duamarqu          #+#    #+#             */
/*   Updated: 2025/02/21 12:20:32 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates sufficient memory for a copy of the string s1, does the copy,
	and returns a pointer to it.
	The pointer may subsequently be used as an argument to the function free(3).
	If insufficient memory is available, NULL is returned. */
char	*ft_strndup(const char *s1, size_t n)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(n + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
