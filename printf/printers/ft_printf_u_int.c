/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:55:43 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 13:37:24 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"

int	ft_printf_u_int(va_list *argptr)
{
	return (ft_put_u_nbr_base(va_arg(*argptr, unsigned int), 10, DEC_ALPHABET));
}
