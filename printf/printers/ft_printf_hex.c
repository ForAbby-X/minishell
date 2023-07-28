/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:55:43 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 13:38:07 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"

int	ft_printf_hex(va_list *argptr, int uppercase)
{
	char	*alphabet;

	if (uppercase)
		alphabet = HEX_UC_ALPHABET;
	else
		alphabet = HEX_LC_ALPHABET;
	return (ft_putnbr_base(va_arg(*argptr, unsigned int), 16, alphabet));
}
