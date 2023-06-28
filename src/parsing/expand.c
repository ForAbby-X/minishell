/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:27 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/28 21:18:18 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline t_merror	__expand_var_word(
	t_vector *const tokens,
	t_length *index,
	char *var)
{
	t_token	token;
	char	temp;
	char	*start;

	while (*var)
	{
		while (*var && is_separator(*var))
			var++;
		start = var;
		while (*var && !is_separator(*var))
			var++;
		temp = *var;
		*var = '\0';
		token.data = ft_strdup(start);
		if (token.data == NULL)
			return (MEMORY_ERROR);
		*var = temp;
		token.type = WORD;
		if (is_separator(*var))
			vector_insert(tokens, &(t_token){NULL, SEPARATOR}, *index);
		vector_insert(tokens, &token, *index);
		*index += 1 + is_separator(*var);
	}
	return (SUCCESS);
}

static inline t_merror	__expand_var_quoted(
	t_vector *const tokens,
	t_length *index,
	char const *const var)
{
	t_token	token;

	token.type = WORD;
	if (var)
		token.data = ft_strdup(var);
	else
		token.data = ft_strdup("");
	if (token.data == NULL)
		return (MEMORY_ERROR);
	vector_insert(tokens, &token, *index);
	*index += 1;
	return (SUCCESS);
}

static inline t_merror	__expand_word(
	t_vector *const tokens,
	t_length *const index,
	t_token *const token,
	char **const str)
{
	char *const	start = *str;
	char		tmp;
	t_token		temp_token;

	(void)token;
	while (**str && **str != '$')
		*str += 1;
	tmp = **str;
	**str = '\0';
	temp_token = (t_token){ft_strdup(start), WORD};
	**str = tmp;
	if (temp_token.data == NULL)
		return (MEMORY_ERROR);
	vector_insert(tokens, &temp_token, *index);
	*index += 1;
	return (SUCCESS);
}

static inline t_merror	__expand_var(
	t_vector *const tokens,
	t_length *const index,
	t_token *const token,
	char **const str)
{
	char	*ptr;
	char	*start;
	char	*var;
	char	tmp;

	ptr = *str + 1;
	if (*ptr == '$')
		return (*str += 2, __expand_var_quoted(tokens, index, "PROCESS_PID"));
	if (*ptr == '?')
		return (*str += 2, __expand_var_quoted(tokens, index, "ERROR_CODE"));
	if (ft_isdigit(*ptr))
		return (*str += 2, SUCCESS);
	start = ptr;
	while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
		ptr++;
	tmp = *(ptr + (ptr == start));
	*(ptr + (ptr == start)) = '\0';
	if (ptr == start)
		return (*str += 2, __expand_var_quoted(tokens, index, start - 1),
			*(ptr + 1) = tmp, SUCCESS);
	var = getenv(start); // REPLACE WITH CUSTOM GETENV
	*ptr = tmp;
	*str = ptr;
	if (var == NULL && token->type == WORD)
		return (SUCCESS);
	if (token->type == WORD)
		return (__expand_var_word(tokens, index, var));
	return (__expand_var_quoted(tokens, index, var));
}

t_merror	expand_token(
	t_vector *const tokens,
	t_length *const index,
	t_token *const token)
{
	t_token	temp;
	char	*start;

	temp = *token;
	start = token->data;
	vector_erase(tokens, *index);
	while (*start)
	{
		if (*start == '$')
		{
			if (__expand_var(tokens, index, &temp, &start))
				return (MEMORY_ERROR);
		}
		else if (__expand_word(tokens, index, &temp, &start))
			return (MEMORY_ERROR);
	}
	free(temp.data);
	return (SUCCESS);
}
