/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 17:02:15 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "error.h"
#include "env.h"

static void	_display_env_sorted(t_vector *env)
{
	char	**last;
	char	**str;
	char	**less;

	last = NULL;
	less = vector_get(env, 0);
	while (less != NULL)
	{
		str = vector_get(env, 0);
		while (*str != NULL && last != NULL && ft_strcmp(*str, *last) <= 0)
			str++;
		less = str;
		while (*str != NULL)
		{
			if (ft_strcmp(*str, *less) < 0
				&& (last == NULL || ft_strcmp(*str, *last) > 0))
				less = str;
			str ++;
		}
		if (less == last || *less == NULL)
			return ;
		printf("%s\n", *less);
		last = less;
	}
}

static int	_is_valid_name(char *name, char *end)
{
	if (name == NULL || ft_isdigit(*name) || name == end)
		return (0);
	while (name < end && name != NULL)
	{
		if (!ft_isalnum(*name) && *name != '_')
		{
			return (0);
		}
		name ++;
	}
	return (1);
}

static t_merror	_export_var(char *var, t_vector *env)
{
	char		*sep;

	sep = ft_strchr(var, '=');
	if (sep == NULL)
	{
		ft_putstr_fd("export: \"", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		return (_set_err("\" not a valid identifier", 1, FAILURE));
	}
	else if (_is_valid_name(var, sep))
	{
		if (set_env_var(var, sep, env) == MEMORY_ERROR)
			return (_set_err("export: memory error", 1, FAILURE));
	}
	else
	{
		ft_putstr_fd("export: \"", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		return (_set_err("\" not a valid identifier", 1, FAILURE));
	}
	return (SUCCESS);
}

t_merror	builtin_export(int argc, char **argv, t_vector *env)
{
	t_merror	err;

	err = SUCCESS;
	if (argc == 1)
		return (_display_env_sorted(env), set_exit_code(0), SUCCESS);
	while (*++argv)
	{
		if (*argv != NULL)
		{
			err |= _export_var(*argv, env);
		}
	}
	if (err == SUCCESS)
		set_exit_code(0);
	return (err);
}
