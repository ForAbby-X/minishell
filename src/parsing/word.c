/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:22:08 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/24 18:37:40 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static inline int	__is_whitespace(char const c)
// {
// 	return (c == ' ' || c == '\f' || c == '\n'
// 		|| c == '\r' || c == '\t' || c == '\v');
// }

// static inline char	*__sub_str(char *const str, size_t const len)
// {
// 	char *const	ret = malloc(len + 1);

	
// }

// static inline char	*__parse_simple(
// 		char const *const str,
// 		t_length *const index,
// 		t_vector *const tokens)
// {
// }

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
		if (tokens_add(tokens, &token) == NULL)
			return (free(token.data), MEMORY_ERROR);
		return (SUCCESS);
	}
	return (PARSING_ERROR);
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
		if (line[index] == '"' || line[index] == '\'')
		{
			error = __parse_quotes(line, &index, tokens);
			if (error)
				return (error);
		}
		index++;
	}
	return (SUCCESS);
}
