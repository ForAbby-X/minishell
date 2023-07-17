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
	t_command *command, t_vector *env)
{
	int			saved_stdin;
	int			saved_stdout;
	t_merror	result;

	if (vector_addback(&command->words, &(char *){0}) == NULL)
		return (MEMORY_ERROR);
	restore_default_signal_handlers();
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
	result = builtin_func(command->words.size - 1, command->words.data, env);
	if (restore_redirs(saved_stdin, saved_stdout) == FATAL_ERROR)
		return (FATAL_ERROR);
	return (result);
}

t_merror	exec_builtins_layer(t_command *commands,
	t_length commands_count, t_vector *env)
{
	t_builtin_cmd_ptr	func;

	func = NULL;
	if (commands_count == 1)
		func = get_builtin_cmd(*(char **)(commands->words.data));
	if (func != NULL)
		return (run_builtin_command(func, commands, env));
	return (exec_piped_commands(commands, commands_count, env));
}
