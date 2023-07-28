/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 07:10:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "builtins_export.h"

static inline t_merror	__export_err(char *str, char *str2)
{
	if (!str2)
		set_err("export", (char *[]){str}, 1, 1);
	else
		set_err("export", (char *[]){"`", str, "'", str2}, 4, 1);
	return (FAILURE);
}

static int	_is_valid_name(char *name, char *end)
{
	if (name == NULL || ft_isdigit(*name) || name == end || *name == '+')
		return (0);
	while (name < end && name != NULL)
	{
		if (!ft_isalnum(*name) && *name != '_')
		{
			if ((name + 1 != end) || *name != '+')
				return (0);
		}
		name ++;
	}
	return (1);
}

static t_merror	_export_var(char *var, t_vector *env)
{
	char		*sep;
	char		*tmp;

	tmp = NULL;
	sep = ft_strchr(var, '=');
	if (sep == NULL)
		return (__export_err(var, " not a valid identifier"));
	else if (_is_valid_name(var, sep))
	{
		if (sep > var && sep[-1] == '+')
		{
			sep[-1] = '\0';
			tmp = ft_strjoin(var, sep);
			sep[-1] = '+';
			sep = tmp + (sep - var) - 1;
			var = tmp;
		}
		if (!var || set_env_var(var, sep, env) == MEMORY_ERROR)
			return (free(tmp), __export_err("memory error", NULL));
		free(tmp);
	}
	else
		return (__export_err(var, " not a valid identifier"));
	return (SUCCESS);
}

t_merror	builtin_export(int argc, char **argv, t_vector *env)
{
	t_merror	err;

	err = SUCCESS;
	if (argc == 1)
	{
		set_exit_code(0);
		display_env_sorted(env);
		return (SUCCESS);
	}
	while (*++argv)
	{
		if (*argv != NULL)
		{
			err |= _export_var(*argv, env);
		}
	}
	if (err != SUCCESS)
		return (FAILURE);
	set_exit_code(0);
	return (SUCCESS);
}
