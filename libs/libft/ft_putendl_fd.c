/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:31:32 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/02/21 12:14:35 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string ’s’ to the given file descriptor
followed by a newline. */
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/* 
#include <fcntl.h>

int	main(void)
{
	char	*str = "Hello World!!";
	int		fd;

	fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT, 0640);
	ft_putendl_fd(str, fd);
	return (0);
}
 */