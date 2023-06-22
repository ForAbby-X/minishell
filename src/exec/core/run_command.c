/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:41 by olivier           #+#    #+#             */
/*   Updated: 2023/06/22 02:13:25 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_merror		run_command_error(t_exec_command *command, char *const str)
{
	ft_putstr_fd(*(char **)vector_get(&(command->args), 0), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FAILURE);
}

t_merror run_command(t_exec_command *command, t_vector *env)
{
	int err;
	handle_redirs(&command->redirs);
	err = ft_execvpe(*(char **)vector_get(&(command->args), 0), &(command->args), env);
	if (err == -2)
		run_command_error(command, "command not found");
	else
		run_command_error(command, strerror(errno));
	return (FAILURE);
}

t_merror spawn_command(t_exec_command *command, t_vector *env, int in_fd, int out_fd)
{
	int cpid;

	cpid = fork();
	if (cpid == -1)
	{
		//ERROR
	}
	if (cpid == 0)
	{
		//child
		dup2(in_fd, STDIN_FILENO);
		dup2(out_fd, STDOUT_FILENO);
		run_command(command, env);
		//child failed to execute
		//fd_in and fd_out are closed in run_command
		return (CHILD_ERROR);
	}
	else
	{	
		close(in_fd);
		close(out_fd);
		return (SUCCESS);
	}
}