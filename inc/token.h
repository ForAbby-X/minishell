/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:26:36 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/19 18:23:26 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "vector.h"

static char const *const	g_type_write[] = {
	"WORD",
	"SINGLE_QUOTED",
	"DOUBLE_QUOTED",
	"SEPARATOR",
	"HEREDOC",
	"HEREDOC_NO_EXPAND",
	"APPEND",
	"IN",
	"OUT",
	"PIPE"
};

typedef enum e_type_token {
	WORD,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	SEPARATOR,
	HEREDOC,
	HEREDOC_NO_EXPAND,
	APPEND,
	IN,
	OUT,
	PIPE
}	t_ttoken;

typedef struct s_token
{
	char		*data;
	t_ttoken	type;
}	t_token;

void	token_display(void *const object);
void	token_destroy(void *const object);
void	*token_cpy(void *dest, void *src, t_length const len);
t_token	*tokens_add(t_vector *const vector, t_token	*const obj);

#endif
