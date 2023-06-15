/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:20:04 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 00:52:26 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline t_merror	__merge_two_tokens(
	t_token *const first,
	t_token *const second,
	t_vector *const tokens,
	t_length const index)
{
	char	*temp;

	first->type = WORD;
	temp = first->data;
	first->data = ft_strjoin(first->data, second->data);
	free(temp);
	if (first->data == NULL)
		return (MEMORY_ERROR);
	token_destroy(second);
	vector_erase(tokens, index);
	return (SUCCESS);
}

t_merror	merge_all_tokens(t_vector *const tokens)
{
	t_token		*last_token;
	t_token		*token;
	t_length	index;

	index = 0;
	last_token = &(t_token){NULL, SEPARATOR};
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		if (is_tok_alpha(token) && is_tok_alpha(last_token))
		{
			__merge_two_tokens(last_token, token, tokens, index);
			continue ;
		}
		last_token = token;
		index++;
	}
	return (SUCCESS);
}
