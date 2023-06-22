/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:41 by olivier           #+#    #+#             */
/*   Updated: 2023/06/22 05:31:10 by olimarti         ###   ########.fr       */
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
	fprintf(stderr, "RUN COMMAND %s\n", *(char **)vector_get(&(command->args), 0));
	handle_redirs(&(command->redirs));
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

	ft_putstr_fd("FORK LAST\n", 2);
	cpid = fork();
	if (cpid == -1)
		return (perror("fork error"), FAILURE);
	if (cpid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		return (run_command(command, env), CHILD_ERROR);
	}
	else
	{	
		return (close(in_fd), close(out_fd), SUCCESS);
	}
}

// t_merror spawn_piped_command(t_exec_command *command, t_vector *env, int prev_pipe_rd, int pipefd[2])
// {
// 	int cpid;
	
// 	cpid = fork();
// 	if (cpid == -1)
// 		return (perror("fork error"), FAILURE);
// 	if (cpid == 0)
// 	{
// 		//child
// 		close(pipefd[0]);
// 		dup2(prev_pipe_rd, STDIN_FILENO);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		run_command(command, env);
// 		//child failed to execute
// 		//fd_in and fd_out are closed in run_command
// 		return (CHILD_ERROR);
// 	}
// 	else
// 	{	
// 		close(prev_pipe_rd);
// 		close(pipefd[1]);
// 		return (SUCCESS);
// 	}
// }
static void apply_pipe_redirect(int cpid, int prev_pipe_rd, int pipefd[2])
{
	if (cpid == -1)
	{
		close(prev_pipe_rd);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cpid == 0)
	{
		close(pipefd[0]);
		if (prev_pipe_rd != STDIN_FILENO)
		{
			dup2(prev_pipe_rd, STDIN_FILENO);
			close(prev_pipe_rd);
		}
		if (pipefd[1] != STDOUT_FILENO)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
	}
	else
	{	
		close(prev_pipe_rd);
		close(pipefd[1]);
	}
}

void	wait_childs(t_length childs_count)
{
	t_length i;

	i = 0;
	while (i < childs_count)
	{
		fprintf(stderr, "WAIIIT = %i %i\n", i , childs_count);
		//ft_putstr_fd("WAIT--------\n", 2);
		wait(NULL);
		i ++;
	}
}

t_merror exec_piped_commands(t_exec_command *commands, t_length commands_count, t_vector *env)
{
	int	pipefd[2];
	int	last_cpid;
	int prev_pipe_rd;
	t_length i;
	int cpid;
	
	prev_pipe_rd = STDIN_FILENO;
	i = 0;

	while (i < commands_count - 1)
	{
		if (pipe(pipefd) == -1)
			return (close(prev_pipe_rd), perror("pipe error"), FAILURE);
		cpid = fork();
		apply_pipe_redirect(cpid, prev_pipe_rd, pipefd);
		if (cpid == -1)
			return (perror("fork error"), close(prev_pipe_rd), FAILURE);
		if (cpid == 0)
			return (run_command(commands + i, env), CHILD_ERROR);
		prev_pipe_rd = pipefd[0];
		i++;
	}
	if (spawn_command(commands+i, env, prev_pipe_rd, STDOUT_FILENO) == CHILD_ERROR)
		return (CHILD_ERROR);
	wait_childs(commands_count);
	return(SUCCESS);
}



// t_merror exec_piped_commands(t_exec_command *commands, int commands_count, t_vector *env)
// {
// 	int	pipefd[2];
// 	int	last_cpid;
// 	int prev_pipe_rd;
// 	int i;
	
// 	prev_pipe_rd = STDIN_FILENO;
// 	i = 0;

// 	while (i < commands_count)
// 	{
// 		if (pipe(pipefd) == -1)
// 			return (close(prev_pipe_rd), error("pipe error"), FAILURE);
// 		if (spawn_piped_command(commands + i, env, prev_pipe_rd, pipefd) == CHILD_ERROR)
// 			return (CHILD_ERROR); //TODO better error management
// 		else

// 		i++;
// 	}
// }