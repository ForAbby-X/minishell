/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:12:48 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/24 06:00:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

int	ft_strcpyl(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
		if (*s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	return (0);
}

int	ft_putstrendl_fd_check(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	return ((write(fd, s, len) != len) | (write(fd, "\n", 1) != 1));
}

int	ft_putstr_fd_check(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	return ((write(fd, s, len) != len));
}
