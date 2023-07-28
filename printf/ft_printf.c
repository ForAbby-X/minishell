/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:54:58 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 14:31:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//return 1 : match
int	pattern_matcher(char const *str, const char *pattern)
{
	if (pattern == NULL || str == NULL)
		return (1);
	while (*pattern == *str && *pattern != 0)
	{
		pattern++;
		str++;
	}
	return (*pattern == 0);
}

int	flag_handler(const char *str, size_t *letter_count, va_list *argprt)
{
	if (pattern_matcher(str, CHR_PATTERN))
		*letter_count += ft_printf_chr(argprt);
	else if (pattern_matcher(str, STR_PATTERN))
		*letter_count += ft_printf_str(argprt);
	else if (pattern_matcher(str, DEC_PATTERN)
		|| pattern_matcher(str, INT_PATTERN))
		*letter_count += ft_printf_int(argprt);
	else if (pattern_matcher(str, U_INT_PATTERN))
		*letter_count += ft_printf_u_int(argprt);
	else if (pattern_matcher(str, HEX_PATTERN))
		*letter_count += ft_printf_hex(argprt, 0);
	else if (pattern_matcher(str, HEX_UC_PATTERN))
		*letter_count += ft_printf_hex(argprt, 1);
	else if (pattern_matcher(str, PTR_PATTERN))
		*letter_count += ft_printf_ptr(argprt);
	else if (pattern_matcher(str, PERCENT_PATTERN))
		*letter_count += ft_printf_percent();
	else
		return (0);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	size_t	letter_count;
	va_list	argprt;

	va_start(argprt, str);
	i = 0;
	letter_count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (*str == 0)
				return (-1);
			i += flag_handler(str + i, &letter_count, &argprt);
		}
		else
		{
			letter_count += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(argprt);
	return (letter_count);
}
