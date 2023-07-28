/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:43:51 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 03:29:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_merror	_init_env(char **env, t_vector *const vector)
{
	char		*tmp;
	t_merror	err;

	err = SUCCESS;
	while (*env && err == SUCCESS)
	{
		tmp = ft_strdup(*env);
		if (!tmp)
			err = MEMORY_ERROR;
		if (vector_addback(vector, &tmp) == NULL)
			err = MEMORY_ERROR;
		env++;
	}
	if (vector_addback(vector, &(char *){0}) == NULL)
		err = MEMORY_ERROR;
	if (err)
		_env_destroy(vector);
	if (err == SUCCESS && handle_shlvl(vector) != SUCCESS)
	{
		display_err("warning",
			(char *[]){"failed to initialize SHLVL environment variable"}, 1);
	}
	return (err);
}
