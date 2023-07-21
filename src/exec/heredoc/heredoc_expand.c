/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:37:23 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/21 18:44:45 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "parsing.h"

static inline t_merror	__join_var(char **str, char *var, int flag)
{
	char	*tmp;

	if (var == NULL)
		return (SUCCESS);
	if (*str == NULL)
	{
		*str = ft_strdup(var);
		if (flag)
			free(var);
		return (SUCCESS);
	}
	tmp = ft_strjoin(*str, var);
	if (flag)
		free(var);
	if (tmp == NULL)
		return (MEMORY_ERROR);
	free(*str);
	*str = tmp;
	return (SUCCESS);
}

static inline t_merror	__expand_var(
		char **in_str,
		char **out_str,
		t_vector *env)
{
	char		*start;
	char		tmp;
	t_merror	err;

	err = SUCCESS;
	if (is_separator(**in_str) || **in_str == '\0')
		return (__join_var(out_str, "$", 0));
	if (**in_str == '$')
		return (++(*in_str), __join_var(out_str, ft_getpid(), 1));
	if (**in_str == '?')
		return (++(*in_str), __join_var(out_str, ft_itoa(get_exit_code()), 1));
	if (ft_isdigit(**in_str) || !(ft_isalnum(**in_str) || **in_str == '_'))
		return (__join_var(out_str, "", 0));
	start = *in_str;
	while (**in_str && (ft_isalnum(**in_str) || **in_str == '_'))
		++(*in_str);
	tmp = **in_str;
	**in_str = '\0';
	err = __join_var(out_str, ft_getenv(env, start), 0) != SUCCESS;
	**in_str = tmp;
	return (err);
}

t_merror	string_expander(char *in_str, char **out_str, t_vector *env)
{
	char	*start;

	start = in_str;
	while (*in_str)
	{
		if (*in_str == '$')
		{
			if (in_str != start)
			{
				*in_str = '\0';
				if (__join_var(out_str, start, 0) == MEMORY_ERROR)
					return (MEMORY_ERROR);
			}
			in_str ++;
			if (__expand_var(&in_str, out_str, env) == MEMORY_ERROR)
				return (MEMORY_ERROR);
			start = in_str;
		}
		else
			in_str ++;
	}
	if (__join_var(out_str, start, 0) == MEMORY_ERROR)
		return (MEMORY_ERROR);
	return (SUCCESS);
}
