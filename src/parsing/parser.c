/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:29:55 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/02 00:11:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline t_merror	__set_cmd(
	t_token *const last_token,
	t_token *const token)
{
	if (last_token->type == PIPE
		&& (token->type == WORD || token->type == SINGLE_QUOTED
			|| token->type == DOUBLE_QUOTED))
		token->type = CMD;
	return (FAILURE);
}

static inline t_merror	__rem_sep(
	t_vector *const tokens,
	t_token *const last_token,
	t_token *const token,
	t_length const index
	)
{
	if (token->type == SEPARATOR
		&& (last_token->type != WORD && last_token->type != SINGLE_QUOTED
			&& last_token->type != DOUBLE_QUOTED))
	{
		token_destroy(token);
		vector_erase(tokens, index);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_merror	parser(t_vector *const tokens)
{
	t_token		*last_token;
	t_token		*token;
	t_length	index;

	index = 0;
	last_token = &(t_token){NULL, PIPE};
	while (index < vector_size(tokens))
	{
		token = tokens_get(tokens, index);
		if (__rem_sep(tokens, last_token, token, index))
			continue ;
		__set_cmd(last_token, token);
		last_token = token;
		index++;
	}
	return (SUCCESS);
}
