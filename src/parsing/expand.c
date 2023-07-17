/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:27 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/17 18:18:45 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "env.h"

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
		token.data = start;
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
	char *var)
{
	t_token	token;

	token.type = WORD;
	if (var)
		token.data = var;
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
	printf("expanding var 0\n");
	if (ft_strchr("?$\0", *ptr))
		return (*str += (2 - (*ptr == '\0')),
			__expand_var_quoted(norm.toks, index, exp_get_var(*ptr)));
	printf("expanding var 1\n");
	if (ft_isdigit(*ptr) || !(ft_isalnum(*ptr) || *ptr == '_'))
		return (*str += 2, tmp = *(ptr + 1), *(ptr + 1) = 0, \
		__expand_var_quoted(norm.toks, index, ptr - 1), *(ptr + 1) = tmp, 0);
	printf("expanding var 2\n");
	start = ptr;
	while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
		ptr++;
	tmp = *ptr;
	*ptr = '\0';
	var = ft_getenv(env, start);
	*ptr = tmp;
	if (norm.tok.type == WORD)
		return (*str = ptr, !var || __expand_var_word(norm.toks, index, var));
	printf("expanding var 3\n");
	return (*str = ptr, __expand_var_quoted(norm.toks, index, var));
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

	temp = *token;
	start = token->data;
	vector_erase(tokens, *index);
	lisa = vector_get(tokens, *index);
	while (lisa && (lisa->type == SEPARATOR || (token && lisa == token)))
		lisa++;
	while (*start)
	{
		if (*start == '$')
		{
			// if (lisa && *(start + 1) == '\0'
			// 	&& (lisa->type == DOUBLE_QUOTED || lisa->type == SINGLE_QUOTED))
			// {
			// 	start++;
			// 	__expand_var_quoted(tokens, index, NULL);
			// }
			if (__expand_var((t_norm){tokens, temp}, index, &start, env))
				return (MEMORY_ERROR);
		}
		else if (__expand_word(tokens, index, &temp, &start))
			return (MEMORY_ERROR);
	}
	vector_for_each(tokens, &token_display);
	printf("\n");
	free(temp.data);
	return (SUCCESS);
}
