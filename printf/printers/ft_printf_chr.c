/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:55:43 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 13:37:56 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"

int	ft_printf_chr(va_list *argptr)
{
	return (ft_putchar(va_arg(*argptr, int)));
}
