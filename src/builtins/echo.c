/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:27 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/18 18:23:06 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"

t_merror	builtin_echo(int argc, char **argv, t_vector *env)
{
	int	index;
	int	display_nl;

	sleep(5);
	(void) env;
	index = 1;
	display_nl = 1;
	while (argc > index && (ft_strncmp(argv[index], "-n", 3) == 0))
	{
		display_nl = 0;
		index++;
	}
	if (index < argc)
		ft_putstr_fd(argv[index], STDOUT_FILENO);
	index ++;
	while (index < argc)
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(argv[index], STDOUT_FILENO);
		index++;
	}
	if (display_nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	set_exit_code(0);
	return (SUCCESS);
}
