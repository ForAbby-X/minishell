/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 03:04:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static inline t_merror	__env_err(char *str)
{
	set_err("env", (char *[]){str}, 1, 1);
	return (FAILURE);
}

int	env_var_display(void *const object)
{
	char *const	*line = object;

	if (*line)
	{
		return (ft_putstrendl_fd_check(*line, STDOUT_FILENO));
	}
	return (0);
}

t_merror	builtin_env(int argc, char **argv, t_vector *env)
{
	t_length	index;

	(void) argv;
	if (argc > 1)
	{
		__env_err("too many arguments");
		return (FAILURE);
	}
	index = 0;
	while (index < env->size)
	{
		if (env_var_display(env->data + env->type_size * index))
		{
			set_err("env",
				(char*[]){"write error: ", strerror(errno)}, 2, 125);
			return (FAILURE);
		}
		index++;
	}
	set_exit_code(0);
	return (SUCCESS);
}
