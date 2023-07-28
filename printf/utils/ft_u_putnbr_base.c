/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_putnbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:27:13 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 12:12:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_put_u_nbr_base(unsigned long n, unsigned long base,
		const char *base_alphabet)
{
	int	out;

	out = 0;
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
