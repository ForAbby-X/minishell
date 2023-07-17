/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:56:09 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/17 17:17:33 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "exec.h"
#include "signal_handlers.h"
#include "builtins_cmd.h"

static t_merror
	open_heredocs_command(t_vector *redirs, t_vector *heredocs, t_vector *env)
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
		if (redir->type == HEREDOC || redir->type == HEREDOC_NO_EXPAND)
		{
			error = heredoc_file(redir->data, &filename, env,
					(redir->type != HEREDOC_NO_EXPAND));
			if (error == 0)
			{
				error = vector_addback(heredocs, &filename) == NULL;
				free(redir->data);
				redir->data = filename;
			}
		}
		i++;
		redir = (t_token *)vector_get(redirs, i);
	}
	return (error);
}

static t_merror
	open_heredocs(t_vector *commands, t_vector	*heredocs, t_vector *env)
{
	t_merror		error;
	t_length		i;

	i = 0;
	error = SUCCESS;
	while (error == SUCCESS && i < commands->size)
	{
		error = open_heredocs_command(
				&(((t_command *)vector_get(commands, i))->redirs),
				heredocs, env);
		i ++;
	}
	return (error);
}

static void	delete_hd(char **path)
{
	fprintf(stderr, "DELETE TMP FILE : %s\n", *path);
	unlink(*path);
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
	error = open_heredocs(commands, &heredocs, env);
	if (error == 0)
	{
		set_ignore_signal_handlers();
		error = exec_builtins_layer(commands->data, commands->size, env);
	}
	vector_for_each(&heredocs, (void (*)(t_object))delete_hd);
	vector_destroy(&heredocs);
	return (error);
}
