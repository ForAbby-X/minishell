/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:26:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/29 15:09:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	g_exit_code = 0;

void	set_exit_code(int exit_code)
{
	fprintf(stderr, "\nEXIT STATUS : %i\n", exit_code);
	g_exit_code = exit_code;
}

int	get_exit_code(void)
{
	return (g_exit_code);
}
