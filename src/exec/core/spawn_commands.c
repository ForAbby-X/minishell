/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:07:22 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 00:22:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handlers.h"

t_merror	spawn_last_command(t_command *command, t_vector *env,
	int in_fd, pid_t *cpid)
{
	*cpid = fork();
	if (*cpid == -1)
		return (perror("fork error"), FAILURE);
	if (*cpid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		return (run_command(command, env), CHILD_ERROR);
	}
	else
	{
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		return (SUCCESS);
	}
}

static void	apply_pipe_redirect(int cpid, int prev_pipe_rd, int pipefd[2])
{
	if (cpid == -1)
	{
		(close(prev_pipe_rd), close(pipefd[0]), close(pipefd[1]));
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
		if (prev_pipe_rd != STDIN_FILENO)
			close(prev_pipe_rd);
		close(pipefd[1]);
	}
}

int	wait_childs(t_length childs_count, pid_t watch_cpid)
{
	t_length	i;
	int			wstatus;
	int			watch_status;

	i = 0;
	watch_status = 0;
	while (i < childs_count)
	{
		if (wait(&wstatus) == watch_cpid)
		{
			watch_status = wstatus;
		}
		i ++;
	}
	if (WIFSIGNALED(watch_status))
	{
		if (WCOREDUMP(watch_status))
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		set_exit_code(128 + WTERMSIG(watch_status));
	}
	else
		set_exit_code(WEXITSTATUS(watch_status));
	return (watch_status);
}

t_merror	exec_piped_commands(t_command *commands,
	t_length commands_count, t_vector *env)
{
	int			pipefd[2];
	int			prev_pipe_rd;
	t_length	i;
	int			cpid;

	prev_pipe_rd = STDIN_FILENO;
	i = 0;
	while (commands_count && i < commands_count - 1)
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
	if (commands_count && i < commands_count && spawn_last_command(commands + i,
			env, prev_pipe_rd, &cpid) == CHILD_ERROR)
		return (CHILD_ERROR);
	wait_childs(commands_count, cpid);
	return (SUCCESS);
}
