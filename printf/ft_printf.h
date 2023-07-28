/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:54:56 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 13:36:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "utils/utils.h"
# include "printers/printers.h"

# define CHR_PATTERN "c"
# define STR_PATTERN "s"
# define DEC_PATTERN "d"
# define INT_PATTERN "i"
# define U_INT_PATTERN "u"
# define HEX_PATTERN "x"
# define HEX_UC_PATTERN "X"
# define PTR_PATTERN "p"
# define PERCENT_PATTERN "%"

int	ft_printf(const char *str, ...);

#endif
