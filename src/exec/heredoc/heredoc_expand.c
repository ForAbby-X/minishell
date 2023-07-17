/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:37:23 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/08 19:52:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static t_merror	_join_var(char **str, char *var)
{
	char	*tmp;

	if (var == NULL)
		return (SUCCESS);
	if (*str == NULL)
		return (*str = ft_strdup(var), SUCCESS);
	tmp = ft_strjoin(*str, var);
	if (tmp == NULL)
		return (MEMORY_ERROR);
	free(*str);
	*str = tmp;
	return (SUCCESS);
}

static t_merror	__expand_var(char **in_str, char **out_str, t_vector *env)
{
	char		*var;
	char		*start;
	char		tmp;
	t_merror	err;

	err = SUCCESS;
	if (**in_str == 0)
		return (++(*in_str), _join_var(out_str, "$"));
	if (**in_str == '$')
		return (++(*in_str), _join_var(out_str, "PROCESS_PID"));
	if (**in_str == '?')
		return (++(*in_str), _join_var(out_str, "ERROR_CODE"));
	if (ft_isdigit(**in_str) || !(ft_isalnum(**in_str) || **in_str == '_'))
		return (_join_var(out_str, ""));
	start = *in_str;
	while (**in_str && (ft_isalnum(**in_str) || **in_str == '_'))
		++(*in_str);
	tmp = **in_str;
	**in_str = '\0';
	var = ft_getenv(env, start);
	err = _join_var(out_str, var) != SUCCESS;
	free(var);
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
				if (_join_var(out_str, start) == MEMORY_ERROR)
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
	if (_join_var(out_str, start) == MEMORY_ERROR)
		return (MEMORY_ERROR);
	return (SUCCESS);
}
