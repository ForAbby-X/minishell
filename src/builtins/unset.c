/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 02:21:29 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static void	_remove_var(char	*name, t_vector *env)
{
	int			name_len;
	char		**str;
	t_length	i;

	i = 0;
	name_len = ft_strlen(name);
	str = vector_get(env, 0);
	while (i + 1 < env->size)
	{
		if (ft_strncmp(str[i], name, name_len) == 0 && str[i][name_len] == '=')
			vector_erase(env, i);
		++i;
	}
}

t_merror	builtin_unset(int argc, char **argv, t_vector *env)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i] != NULL && argv[i][0] != '\0')
			_remove_var(argv[i], env);
		++i;
	}
	set_exit_code(0);
	return (SUCCESS);
}
