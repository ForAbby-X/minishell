/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:41 by olivier           #+#    #+#             */
/*   Updated: 2023/07/25 03:31:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handlers.h"
#include "builtins_cmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_merror
	run_command_error(t_command *command, char *const str, int exit_code)
{
	_set_err(*(char **)vector_get(&(command->words), 0),
		(char *[]){str}, 1, exit_code);
	return (FAILURE);
}

t_merror	run_command(t_command *command, t_vector *env)
{
	int					err;
	t_builtin_cmd_ptr	builtin_func;

	builtin_func = NULL;
	restore_default_signal_handlers();
	if (vector_addback(&command->words, &(char *){NULL}) == NULL)
		return (FAILURE);
	if (handle_redirs(&(command->redirs)) != SUCCESS)
		return (FAILURE);
	builtin_func = get_builtin_cmd(command);
	if (builtin_func != NULL)
		return (builtin_func(command->words.size - 1,
				command->words.data, env));
	else
		err = ft_execvpe(*(char **)(command->words.data),
				&(command->words), env);
	if (err == -2)
		run_command_error(command, "command not found", 127);
	else if (err == -1)
		run_command_error(command, strerror(errno), 126);
	else if (err == -3)
		set_exit_code(0);
	return (FAILURE);
}
