/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 06:10:56 by olimarti         ###   ########.fr       */
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
		if (legal_number(argv[1], &exit_code) == 0)
		{
			if (argc >= 3)
			{
				if (get_exit_code() == 0)
					set_exit_code(1);
				display_err("exit", (char *[]){"too many arguments"}, 1);
				return (FAILURE);
			}
		}
		else
		{
			set_err("exit",
				(char *[]){argv[1], ": numeric argument required"}, 2, 2);
			return (CHILD_ERROR);
		}
	}
	set_exit_code(exit_code & 255);
	return (CHILD_ERROR);
}
