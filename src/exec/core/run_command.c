/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:41 by olivier           #+#    #+#             */
/*   Updated: 2023/07/03 18:15:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handlers.h"
#include "builtins_cmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_merror
	run_command_error(t_exec_command *command, char *const str, int exit_code)
{
	ft_putstr_fd(*(char **)vector_get(&(command->args), 0), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	set_exit_code(exit_code);
	return (FAILURE);
}

t_merror	run_command(t_exec_command *command, t_vector *env)
{
	int					err;
	t_builtin_cmd_ptr	builtin_func;

	builtin_func = NULL;
	restore_default_signal_handlers();
	if (handle_redirs(&(command->redirs)) != SUCCESS)
		return (FAILURE);
	builtin_func = get_builtin_cmd(*(char **)(command->args.data));
	if (builtin_func != NULL)
		return (builtin_func(command->args.size - 1, command->args.data, env));
	else
		err = ft_execvpe(*(char **)(command->args.data), &(command->args), env);
	if (err == -2)
		run_command_error(command, "command not found", 127);
	else
		run_command_error(command, strerror(errno), 126);
	return (FAILURE);
}
