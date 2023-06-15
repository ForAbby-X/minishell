/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:29:55 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 01:27:10 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline t_merror	__set_redirections(
	t_vector *const tokens,
	t_token *const last_token,
	t_token *const token,
	t_length const index)
{
	if (is_tok_operator(last_token)
		&& last_token->type != PIPE && token->type == WORD)
	{
		free(last_token->data);
		last_token->data = ft_strdup(token->data);
		token_destroy(token);
		vector_erase(tokens, index);
		return (FAILURE);
	}
	return (SUCCESS);
}

static inline t_merror	__remove_separators(t_vector *const tokens)
{
	t_token		*token;
	t_length	index;

	index = 0;
	while (index < vector_size(tokens))
	{
		token = tokens_get(tokens, index);
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

static inline t_merror	__remove_separators_op(
	t_vector *const tokens,
	t_token *const last_token,
	t_token *const token,
	t_length const index)
{
	if (token->type == SEPARATOR && (is_tok_operator(last_token)
			|| index == 0 || index == vector_size(tokens) - 1))
	{
		token_destroy(token);
		vector_erase(tokens, index);
		return (FAILURE);
	}
	return (SUCCESS);
}

static inline t_merror	__clean_and_redir(t_vector *const tokens)
{
	t_token		*last_token;
	t_token		*token;
	t_length	index;

	index = 0;
	last_token = &(t_token){NULL, PIPE};
	while (index < vector_size(tokens))
	{
		token = tokens_get(tokens, index);
		if (__remove_separators_op(tokens, last_token, token, index))
			continue ;
		if (__set_redirections(tokens, last_token, token, index))
			continue ;
		last_token = token;
		index++;
	}
	return (SUCCESS);
}

t_merror	parser(char const *const line, t_vector *const commands)
{
	t_vector	tokens;

	tokens = vector_create(sizeof(t_token));
	if (tokens.buffer == NULL)
		return (MEMORY_ERROR);
	lexer(line, &tokens);
	__clean_and_redir(&tokens);
	merge_all_tokens(&tokens);
	__remove_separators(&tokens);
	split_to_commands(&tokens, commands);
	vector_destroy(&tokens);
	return (SUCCESS);
}
