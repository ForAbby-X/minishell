/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:22:08 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/25 02:44:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static inline int	__is_whitespace(char const c)
// {
// 	return (c == ' ' || c == '\f' || c == '\n'
// 		|| c == '\r' || c == '\t' || c == '\v');
// }

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

static inline int	__is_separator(char const c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static inline int	__is_quotes(char const c)
{
	return (c == '\'' || c == '"');
}

static inline int	__is_operator(char const c)
{
	return (c == '|' || c == '<' || c == '>');
}

static inline t_merror	__parse_separator(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_token			token;

	while (__is_separator(line[*index]))
		(*index)++;
	token.type = SEPARATOR;
	token.data = NULL;
	if (tokens_add(tokens, &token) == NULL)
		return (MEMORY_ERROR);
	return (SUCCESS);
}

static inline t_merror	__parse_quotes(
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

static inline t_merror	__parse_simple(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_length const	start_i = *index;
	t_token			token;

	while (!__is_separator(line[*index]) && !__is_quotes(line[*index])
		&& !__is_operator(line[*index]) && line[*index])
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

static inline int	__ft_strncmp(char const *str0, char const *str1, size_t len)
{
	while (--len && *str0 && *str0 == *str1)
	{
		++str0;
		++str1;
	}
	return (*str0 - *str1);
}

static inline t_merror	__parse_operator(
		char const *const line,
		t_length *const index,
		t_vector *const tokens)
{
	t_token		token;
	t_length	i;

	i = 0;
	while (g_op_list[i].op
		&& __ft_strncmp(line + *index, g_op_list[i].op, g_op_list[i].size))
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

t_merror	parse_everything(
	char const *const line,
	t_vector *const tokens)
{
	t_length	index;
	t_merror	error;

	index = 0;
	while (line[index])
	{
		if (__is_separator(line[index]))
			error = __parse_separator(line, &index, tokens);
		else if (__is_quotes(line[index]))
			error = __parse_quotes(line, &index, tokens);
		else if (__is_operator(line[index]))
			error = __parse_operator(line, &index, tokens);
		else
			error = __parse_simple(line, &index, tokens);
		if (error)
			return (error);
	}
	return (SUCCESS);
}
