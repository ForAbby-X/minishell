/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/22 05:00:25 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"


t_merror		redir_error(t_redir *redir, char *const str)
{
	ft_putstr_fd(redir->path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FAILURE);
}

static int const redir_flag_table[] = {
   [R_REDIR_IN] = O_RDONLY,
   [R_REDIR_OUT] = O_WRONLY | O_CREAT | O_TRUNC,
   [R_APPEND] = O_WRONLY | O_CREAT | O_APPEND,
   [R_HEREDOC] = 0,
};

static int	get_redir_fd(t_redir *redir)
{
	return (open(redir->path, redir_flag_table[redir->type], 0644));
}

static t_merror apply_redir(t_redir *redir)
{
	int	fd;

	fd = get_redir_fd(redir);
	if (fd == -1)
		return (FAILURE);
	if (redir->type == R_REDIR_IN | redir->type == R_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), FAILURE);
		close(fd);
	}
	else if (redir->type == R_REDIR_OUT | redir->type == R_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), FAILURE);
		close(fd);
	}
	close(fd);
	return (SUCCESS);
}

t_merror handle_redirs(t_vector *redirs)
{
	t_length index;

	index = 0;
	while (index < redirs->size)
	{
		if (apply_redir(redirs_get(redirs, index)) != SUCCESS)
		{
			return (redir_error(redirs_get(redirs, index), strerror(errno)));
		}
		index++;
	}
	return (SUCCESS);
}