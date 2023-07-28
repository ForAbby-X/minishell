/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:54:56 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 13:38:16 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTERS_H
# define PRINTERS_H

# include <stdio.h>
# include "../utils/utils.h"

# define HEX_UC_ALPHABET "0123456789ABCDEF"
# define HEX_LC_ALPHABET "0123456789abcdef"
# define DEC_ALPHABET "0123456789"

//texts
int	ft_printf_str(va_list *argptr);
int	ft_printf_chr(va_list *argptr);
//numbers
int	ft_printf_hex(va_list *argptr, int uppercase);
int	ft_printf_int(va_list *argptr);
int	ft_printf_u_int(va_list *argptr);
//others
int	ft_printf_ptr(va_list *argptr);
int	ft_printf_percent(void);

#endif
