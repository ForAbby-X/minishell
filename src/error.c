/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:26:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 17:03:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

int	g_exit_code = 0;

void	set_exit_code(int exit_code)
{
	g_exit_code = exit_code;
}

int	get_exit_code(void)
{
	return (g_exit_code);
}

t_merror	_set_err(char *str, int code, t_merror status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	set_exit_code(code);
	return (status);
}
