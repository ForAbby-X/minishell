/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:27 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/28 17:07:44 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "env.h"

static inline t_merror	__expand_var_word(
	t_vector *const tokens,
	t_length *index,
	char *var)
{
	char	temp;
	char	*str[2];

	while (*var)
	{
		while (*var && is_separator(*var))
			var++;
		if (*var == '\0')
			return (vector_insert(tokens, &(t_token){NULL, SEPARATOR}, *index)
				, *index += 1, SUCCESS);
		str[0] = var;
		while (*var && !is_separator(*var))
			var++;
		temp = *var;
		*var = '\0';
		str[1] = ft_strdup(str[0]);
		if (str[1] == NULL)
			return (MEMORY_ERROR);
		*var = temp;
		if (is_separator(*var))
			vector_insert(tokens, &(t_token){NULL, SEPARATOR}, *index);
		vector_insert(tokens, &(t_token){str[1], WORD}, *index);
		*index += 1 + is_separator(*var);
	}
	return (SUCCESS);
}

static inline t_merror	__expand_var_quoted(
	t_vector *const tokens,
	t_length *index,
	char *var,
	int flag)
{
	t_token	token;

	token.type = WORD;
	token.data = ft_strdup(var);
	if (flag)
		free(var);
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

typedef struct s_norm
{
	t_vector	*toks;
	t_token		tok;
}	t_norm;

static inline t_merror	__expand_var(
	t_norm norm,
	t_length *const index,
	char **const str,
	t_vector const *const env)
{
	char	*ptr;
	char	*start;
	char	*var;
	char	tmp;

	ptr = *str + 1;
	if (ft_strchr("?$\0", *ptr))
		return (*str += (1 + (*ptr != '\0')),
			__expand_var_quoted(norm.toks, index, exp_get_var(*ptr), 1));
	if (ft_isdigit(*ptr) || !(ft_isalnum(*ptr) || *ptr == '_'))
		return (*str += 2, tmp = *(ptr + 1), *(ptr + 1) = 0, \
		__expand_var_quoted(norm.toks, index, ptr - 1, 0), *(ptr + 1) = tmp, 0);
	start = ptr;
	while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
		ptr++;
	tmp = *ptr;
	*ptr = '\0';
	var = ft_getenv(env, start);
	*ptr = tmp;
	*str = ptr;
	if (var == NULL)
		return (SUCCESS);
	if (norm.tok.type == WORD)
		return (__expand_var_word(norm.toks, index, var));
	return (__expand_var_quoted(norm.toks, index, var, 0));
}

t_merror	expand_token(
	t_vector *const tokens,
	t_length *const index,
	t_token *const token,
	t_vector const *const env)
{
	t_token	temp;
	t_token	*lisa;
	char	*start;
	int		flag;

	temp = *token;
	start = token->data;
	vector_erase(tokens, *index);
	lisa = vector_get(tokens, *index);
	flag = (lisa
			&& (lisa->type == DOUBLE_QUOTED || lisa->type == SINGLE_QUOTED));
	while (*start)
	{
		if (*start == '$')
		{
			if (*(start + 1) == '\0' && flag)
				return (*index += 1, free(temp.data), SUCCESS);
			else if (__expand_var((t_norm){tokens, temp}, index, &start, env))
				return (free(temp.data), MEMORY_ERROR);
		}
		else if (__expand_word(tokens, index, &temp, &start))
			return (free(temp.data), MEMORY_ERROR);
	}
	return (free(temp.data), SUCCESS);
}
