/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:34:50 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 12:28:24 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins_cmd.h"
#include "signal_handlers.h"

static t_merror	run_builtin_command(t_builtin_cmd_ptr builtin_func,
	t_exec_command *command, t_vector *env)
{
	int			saved_stdin;
	int			saved_stdout;
	t_merror	result;

	restore_default_signal_handlers();
	builtin_func = get_builtin_cmd(*(char **)(command->args.data));
	if (builtin_func == NULL)
		return (FAILURE);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (FAILURE);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return (close(saved_stdin), FAILURE);
	if (handle_redirs(&(command->redirs)) != SUCCESS)
	{
		if (restore_redirs(saved_stdin, saved_stdout) == FATAL_ERROR)
			return (FATAL_ERROR);
		return (FAILURE);
	}
	result = builtin_func(command->args.size - 1, command->args.data, env);
	if (restore_redirs(saved_stdin, saved_stdout) == FATAL_ERROR)
		return (FATAL_ERROR);
	return (result);
}

t_merror	exec_builtins_layer(t_exec_command *commands,
	t_length commands_count, t_vector *env)
{
	t_builtin_cmd_ptr	func;

	func = NULL;
	if (commands_count == 1)
		func = get_builtin_cmd(*(char **)(commands->args.data));
	if (func != NULL)
		return (run_builtin_command(func, commands, env));
	return (exec_piped_commands(commands, commands_count, env));
}
