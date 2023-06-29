/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:56:09 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/29 15:05:29 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "exec.h"
#include "signal_handlers.h"

static t_merror	open_heredocs_command(t_vector *redirs, t_vector *heredocs)
{
	t_length	i;
	char		*filename;
	t_merror	error;
	t_token		*redir;

	error = 0;
	i = 0;
	redir = (t_token *)vector_get(redirs, i);
	while (error == 0 && redir)
	{
		if (redir->type == HEREDOC)
		{
			error = heredoc_file(redir->data, &filename);
			if (error == 0)
			{
				error = vector_addback(heredocs, &filename) == NULL;
				redir->data = filename;
			}
		}
		i++;
		redir = (t_token *)vector_get(redirs, i);
	}
	return (error);
}

static t_merror	open_heredocs(t_vector *commands, t_vector	*heredocs)
{
	t_merror		error;
	t_length		i;

	i = 0;
	error = SUCCESS;
	while (error == SUCCESS && i < commands->size)
	{
		error = open_heredocs_command(
				&(((t_exec_command *)vector_get(commands, i))->redirs),
				heredocs);
		i ++;
	}
	return (error);
}

static void	delete_hd(char **path)
{
	fprintf(stderr, "DELETE TMP FILE : %s\n", *path);
	unlink(*path);
	free(*path);
}

t_merror	exec_heredocs_layer(t_vector *commands, t_vector *env)
{
	t_vector	heredocs;
	int			error;

	error = 0;
	heredocs = vector_create(sizeof(char *));
	if (heredocs.buffer == NULL)
		return (MEMORY_ERROR);
	set_hd_signal_handlers();
	error = open_heredocs(commands, &heredocs);
	if (error == 0)
	{
		set_ignore_signal_handlers();
		error = exec_piped_commands(commands->data, commands->size, env);
	}
	exec_command_display(commands->data);
	vector_for_each(&heredocs, (void (*)(t_object))delete_hd);
	vector_destroy(&heredocs);
	return (error);
}
