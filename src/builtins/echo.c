/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:27 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/25 22:39:14 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "errno.h"
#include "utils.h"

static inline int	__echo_putstr(char *str)
{
	if (ft_putstr_fd_check(str, STDOUT_FILENO))
	{
		set_err("echo",
			(char*[]){"write error: ", strerror(errno)}, 2, 1);
		return (1);
	}
	return (0);
}

t_merror	builtin_echo(int argc, char **argv, t_vector *env)
{
	int	index;
	int	display_nl;

	(void) env;
	index = 1;
	display_nl = 1;
	while (argc > index && (ft_strncmp(argv[index], "-n", 3) == 0))
	{
		display_nl = 0;
		index++;
	}
	if (index < argc && __echo_putstr(argv[index]))
		return (FAILURE);
	index ++;
	while (index < argc)
	{
		if (__echo_putstr(" ") || __echo_putstr(argv[index]))
			return (FAILURE);
		index++;
	}
	if (display_nl && __echo_putstr("\n"))
		return (FAILURE);
	set_exit_code(0);
	return (SUCCESS);
}
