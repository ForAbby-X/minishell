/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/24 00:57:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

static int const	g_redir_flag_table[] = {
[IN] = O_RDONLY,
[OUT] = O_WRONLY | O_CREAT | O_TRUNC,
[APPEND] = O_WRONLY | O_CREAT | O_APPEND,
[HEREDOC] = 0,
};

static t_merror	redir_error(t_token *redir, char *const str)
{
	ft_putstr_fd(redir->data, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FAILURE);
}

static int	get_token_fd(t_token *redir)
{
	return (open(redir->data, g_redir_flag_table[redir->type], 0644));
}

static t_merror	apply_redir(t_token *redir)
{
	int	fd;

	fd = get_token_fd(redir);
	if (fd == -1)
		return (FAILURE);
	if (redir->type == IN | redir->type == HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), FAILURE);
		close(fd);
	}
	else if (redir->type == OUT | redir->type == APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), FAILURE);
		close(fd);
	}
	close(fd);
	return (SUCCESS);
}

t_merror	handle_redirs(t_vector *redirs)
{
	t_length	index;

	index = 0;
	while (index < redirs->size)
	{
		if (apply_redir(vector_get(redirs, index)) != SUCCESS)
		{
			return (redir_error(vector_get(redirs, index), strerror(errno)));
		}
		index++;
	}
	return (SUCCESS);
}
