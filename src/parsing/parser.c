/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:29:55 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/28 19:26:41 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline t_merror	__remove_separators(t_vector *const tokens)
{
	t_token		*token;
	t_length	index;

	index = 0;
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		if (token->type == SEPARATOR)
		{
			token_destroy(token);
			vector_erase(tokens, index);
		}
		else
			index++;
	}
	return (SUCCESS);
}

static inline int	__is_tok_expandable(t_token *const token)
{
	return ((token->type == WORD || token->type == DOUBLE_QUOTED)
		&& ft_strchr(token->data, '$'));
}

static inline t_merror	__expand_all(t_vector *const tokens)
{
	t_token		*token;
	t_length	index;
	int			flag;

	index = 0;
	flag = 0;
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		flag += token->type == HEREDOC;
		if (flag == 0 && __is_tok_expandable(token)
			&& expand_token(tokens, &index, token))
			return (FAILURE);
		if (!is_tok_alpha(token) && token->type != HEREDOC)
			flag = 0;
		index++;
	}
	return (SUCCESS);
}

t_merror	parser(char const *const line, t_vector *const commands)
{
	t_vector	tokens;
	t_merror	error;

	tokens = vector_create(sizeof(t_token));
	if (tokens.buffer == NULL)
		return (MEMORY_ERROR);
	error = lexer(line, &tokens);
	printf("\n");
	if (error || __expand_all(&tokens) || merge_all_alpha(&tokens)
		|| __remove_separators(&tokens))
	{
		vector_for_each(&tokens, &token_destroy);
		return (vector_destroy(&tokens), error);
	}
	error = check_tok_error(&tokens);
	if (error)
	{
		vector_for_each(&tokens, &token_destroy);
		return (vector_destroy(&tokens), error);
	}
	error |= (merge_redirs(&tokens) || split_to_commands(&tokens, commands));
	vector_for_each(&tokens, &token_destroy);
	return (vector_destroy(&tokens), error);
}
