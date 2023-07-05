/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:12:48 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 15:43:22 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

static inline void	skip_whitepaces(char **str)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		++*str;
}

int	ft_atoi_validate(char *str, int *result)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	skip_whitepaces(&str);
	if (*str == '+' || *str == '-')
	{
		if (str[1] < '0' && str[1] > '9')
			return (1);
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		if (value - (sign == -1) > 2147483647)
			return (1);
		str++;
	}
	skip_whitepaces(&str);
	if (*str != 0)
		return (1);
	return (*result = value * sign, 0);
}
