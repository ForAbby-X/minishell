/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/25 22:39:14 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"

static inline t_merror	__exit_err(char *str, int code)
{
	set_err("exit", (char *[]){str}, 1, code);
	return (FAILURE);
}

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
				if (get_exit_code() == 0)
					set_exit_code(1);
				__exit_err("too many arguments", get_exit_code());
				return (FAILURE);
			}
		}
		else
		{
			set_err("exit",
				(char *[]){argv[1], ": numeric argument required"}, 2, 2);
		}
	}
	set_exit_code(exit_code & 255);
	return (CHILD_ERROR);
}
