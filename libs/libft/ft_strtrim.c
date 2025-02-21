/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:09:49 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/21 12:17:29 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//trim beginning and end of string with the specified characters
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
/* 
#include <stdio.h>

int	main(void)
{
	char	*s = "ola hello world! allll";
	char	*trim = "alo ";
	char	*trimmed_str;
	
	trimmed_str = ft_strtrim(s, trim);
	printf("%s\n", trimmed_str);
	free(trimmed_str);
	return (0);
} */