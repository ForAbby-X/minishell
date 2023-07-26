/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:37:58 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 03:30:56 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

static t_merror	_set_env_shlvl(char *shlvl, t_vector *env)
{
	shlvl = ft_strjoin("SHLVL=", shlvl);
	if (!shlvl)
		return (MEMORY_ERROR);
	set_env_var(shlvl, ft_strchr(shlvl, '='), env);
	free(shlvl);
	return (SUCCESS);
}

t_merror	handle_shlvl(t_vector *env)
{
	char		*shlvl_var;
	int			shlvl;
	t_merror	err;

	shlvl = 0;
	shlvl_var = ft_getenv(env, "SHLVL");
	if (shlvl_var != NULL && legal_number(shlvl_var, &shlvl))
		shlvl = 0;
	if (shlvl < 0)
		shlvl = -1;
	++shlvl;
	shlvl_var = ft_itoa(shlvl);
	if (shlvl >= MAX_SHLVL - 1 && shlvl_var)
	{
		display_err("warning", (char *[]){"shell level (",
			shlvl_var, ") too high, resetting on 1"}, 3);
		shlvl = 1;
		free(shlvl_var);
		shlvl_var = ft_itoa(shlvl);
	}
	if (shlvl_var == NULL)
		return (MEMORY_ERROR);
	err = _set_env_shlvl(shlvl_var, env);
	free(shlvl_var);
	return (err);
}
