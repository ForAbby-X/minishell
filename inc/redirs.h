/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 22:00:03 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/01 22:01:37 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRS_H
# define REDIRS_H

# include "vector.h"

static char const *const	g_redirs_write[] = {
	"REDIR_IN",
	"REDIR_OUT",
	"HEREDOC",
	"APPEND"
};

typedef enum e_tredir
{
	R_REDIR_IN,
	R_REDIR_OUT,
	R_HEREDOC,
	R_APPEND
}	t_tredir;

typedef struct s_redir
{
	char		*path;
	t_tredir	type;
}	t_redir;

void	redir_display(void *const object);
void	redir_destroy(void *const object);
t_redir	*redirs_add(t_vector *const vector, t_redir	*const obj);
t_redir	*redirs_get(t_vector *const vector, t_length const index);

#endif
