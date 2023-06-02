/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:22:08 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/01 23:44:08 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_op
{
	char		*op;
	int			size;
	t_ttoken	type;
}	t_op;

static t_op const	g_op_list[] = {
{"<<<", 3, 0},
{">>>", 3, 0},
{"<<", 2, HEREDOC},
{">>", 2, APPEND},
{"<", 1, OUT},
{">", 1, IN},
{"|", 1, PIPE},
{NULL, 0, 0}
};

static inline t_merror	__lexer_separator(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_token			token;

	while (is_separator(line[*index]))
		(*index)++;
	if (vector_size(tokens) == 0)
		return (SUCCESS);
	token.type = SEPARATOR;
	token.data = NULL;
	if (tokens_add(tokens, &token) == NULL)
		return (MEMORY_ERROR);
	return (SUCCESS);
}

static inline t_merror	__lexer_quotes(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_length const	start_i = *index + 1;
	char const		char_type = line[*index];
	t_token			token;

	(*index)++;
	while (line[*index] != char_type && line[*index])
		(*index)++;
	if (line[*index] == char_type)
	{
		token.data = malloc(*index - start_i + 1);
		if (token.data == NULL)
			return (MEMORY_ERROR);
		_vec_memcpy(token.data, (void *)line + start_i, *index - start_i);
		token.data[*index - start_i] = '\0';
		token.type = SINGLE_QUOTED + (char_type == '"');
		(*index)++;
		if (tokens_add(tokens, &token) == NULL)
			return (free(token.data), MEMORY_ERROR);
		return (SUCCESS);
	}
	return (PARSING_ERROR);
}

static inline t_merror	__lexer_word(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_length const	start_i = *index;
	t_token			token;

	while (!is_separator(line[*index]) && !is_quotes(line[*index])
		&& !is_operator(line[*index]) && line[*index])
		(*index)++;
	token.data = malloc(*index - start_i + 1);
	if (token.data == NULL)
		return (MEMORY_ERROR);
	_vec_memcpy(token.data, (void *)line + start_i, *index - start_i);
	token.data[*index - start_i] = '\0';
	token.type = WORD;
	if (tokens_add(tokens, &token) == NULL)
		return (free(token.data), MEMORY_ERROR);
	return (SUCCESS);
}

static inline t_merror	__lexer_operator(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_token		token;
	t_length	i;

	i = 0;
	while (g_op_list[i].op
		&& ft_strncmp(line + *index, g_op_list[i].op, g_op_list[i].size))
		i++;
	if (i == 0 || i == 1)
		return (PARSING_ERROR);
	token.data = malloc(g_op_list[i].size + 1);
	if (token.data == NULL)
		return (MEMORY_ERROR);
	_vec_memcpy(token.data, g_op_list[i].op, g_op_list[i].size + 1);
	token.type = g_op_list[i].type;
	if (tokens_add(tokens, &token) == NULL)
		return (free(token.data), MEMORY_ERROR);
	(*index) += g_op_list[i].size;
	return (SUCCESS);
}

t_merror	lexer(char const *const line, t_vector *const tokens)
{
	t_length	index;
	t_merror	error;

	index = 0;
	while (line[index])
	{
		if (is_separator(line[index]))
			error = __lexer_separator(line, &index, tokens);
		else if (is_quotes(line[index]))
			error = __lexer_quotes(line, &index, tokens);
		else if (is_operator(line[index]))
			error = __lexer_operator(line, &index, tokens);
		else
			error = __lexer_word(line, &index, tokens);
		if (error)
			return (error);
	}
	return (parser(tokens));
}
