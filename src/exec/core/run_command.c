/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:41 by olivier           #+#    #+#             */
/*   Updated: 2023/06/24 02:09:48 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	int	err;

	if (handle_redirs(&(command->redirs)) != SUCCESS)
		return (FAILURE);
	err = ft_execvpe(*(char **)(command->args.data), &(command->args), env);
	if (err == -2)
		run_command_error(command, "command not found", 127);
	else
		run_command_error(command, strerror(errno), 126);
	return (FAILURE);
}
