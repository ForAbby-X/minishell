/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 19:44:24 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static inline t_merror	__env_err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	set_exit_code(1);
	return (FAILURE);
}

void	env_var_display(void *const object)
{
	char *const	*line = object;

	if (*line)
	{
		ft_putstr_fd(*line, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

t_merror	builtin_env(int argc, char **argv, t_vector *env)
{
	(void) argv;
	if (argc > 1)
	{
		__env_err("env: too many arguments");
		return (FAILURE);
	}
	vector_for_each(env, env_var_display);
	set_exit_code(0);
	return (SUCCESS);
}
