/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:29:51 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 12:12:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_putstr(char *s)
{
	size_t	len;

	if (!s)
		return (ft_putstr("(null)"));
	len = 0;
	while (s[len] != 0)
		len++;
	write(1, s, len);
	return (len);
}
