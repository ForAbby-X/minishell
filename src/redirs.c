/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 22:00:20 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/01 22:22:42 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

void	redir_display(void *const object)
{
	t_redir *const	redir = object;

	if (redir->path)
		printf("[%s] - %s\n", g_redirs_write[redir->type], redir->path);
	else
		printf("[%s]\n", g_redirs_write[redir->type]);
}

void	redir_destroy(void *const object)
{
	t_redir *const	redir = object;

	free(redir->path);
}

t_redir	*redirs_add(t_vector *const vector, t_redir	*const obj)
{
	return ((t_redir *)vector_addback(vector, obj));
}

t_redir	*redirs_get(t_vector *const vector, t_length const index)
{
	return ((t_redir *)vector_get(vector, index));
}
