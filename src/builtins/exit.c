/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 15:41:19 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"

t_merror	builtin_exit(int argc, char **argv, t_vector *env)
{
	int	exit_code;

	(void) env;
	exit_code = get_exit_code();
	if (argc >= 2)
	{
		if (ft_atoi_validate(argv[1], &exit_code) == 0)
		{
			if (argc >= 3)
			{
				ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
				if (get_exit_code() == 0)
					set_exit_code(1);
				return (FAILURE);
			}
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			set_exit_code(2);
		}
	}
	set_exit_code(exit_code & 255);
	return (CHILD_ERROR);
}
