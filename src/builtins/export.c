/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 14:45:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
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

static void	_remove_env_var_size(char *name, t_vector *env, int name_len)
{
	char		**str;
	t_length	i;

	i = 0;
	str = vector_get(env, 0);
	while (i + 1 < env->size)
	{
		if (ft_strncmp(str[i], name, name_len) == 0 && str[i][name_len] == '=')
			vector_erase(env, i);
		++i;
	}
}

static t_merror	_set_env_var(char *var, char	*sep, t_vector *env)
{
	char	*copy;

	copy = ft_strdup(var);
	if (copy == NULL)
		return (FAILURE);
	_remove_env_var_size(var, env, sep - var);
	if (vector_insert(env, &copy, env->size - 1) == NULL)
		return (free(copy), FAILURE);
	return (SUCCESS);
}

t_merror	builtin_export(int argc, char **argv, t_vector *env)
{
	int			i;
	char		*sep;
	t_merror	err;

	i = 1;
	err = SUCCESS;
	if (argc == 1)
		return (_display_env_sorted(env), set_exit_code(0), SUCCESS);
	while (i < argc)
	{
		if (argv[i] != NULL)
		{
			sep = ft_strchr(argv[i], '=');
			if (sep == NULL)
				return (FAILURE);
			if (_is_valid_name(argv[i], sep))
				err |= (_set_env_var(argv[i], sep, env));
		}
		++i;
	}
	if (err)
		set_exit_code(1);
	else
		set_exit_code(0);
	return (err);
}
