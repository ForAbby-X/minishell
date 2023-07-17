/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:27:15 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/28 18:02:05 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_merror	merge_redirs(t_vector *const tokens)
{
	t_token		*last_token;
	t_token		*token;
	t_length	index;

	index = 0;
	last_token = &(t_token){NULL, SEPARATOR};
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		if (is_tok_operator(last_token)
			&& last_token->type != PIPE && is_tok_alpha(token))
		{
			if (last_token->type == HEREDOC && token->type != WORD)
				last_token->type = HEREDOC_NO_EXPAND;
			free(last_token->data);
			last_token->data = ft_strdup(token->data);
			token_destroy(vector_erase(tokens, index));
			if (last_token->data == NULL)
				return (MEMORY_ERROR);
		}
		last_token = token;
		index++;
	}
	return (SUCCESS);
}
