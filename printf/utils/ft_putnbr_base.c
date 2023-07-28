/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:26:21 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 12:12:00 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_putnbr_base(long n, long base, const char *base_alphabet)
{
	int	out;

	out = 0;
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
		out += 1;
	}
	if (n < base)
	{
		ft_putchar(base_alphabet[n % base]);
		out += 1;
	}
	else
	{
		out = 1 + out + ft_putnbr_base(n / base, base, base_alphabet);
		ft_putchar(base_alphabet[n % base]);
	}
	return (out);
}
