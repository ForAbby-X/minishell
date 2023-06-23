/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:25:45 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/24 01:00:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_getenv(t_vector *const env, const char *name)
{
	t_length	i;
	int			name_len;
	char		*current;

	i = 0;
	name_len = ft_strlen(name);
	while (i < env->size)
	{
		current = *env_get(env, i);
		if (!ft_strncmp(current, name, name_len) && current[name_len] == '=')
			return (ft_strtrim(current + name_len + 1, "\t "));
		i++;
	}
	return (NULL);
}

char	**env_add(t_vector *const vector, char	*const obj)
{
	return ((char **)vector_addback(vector, obj));
}

char	**env_get(t_vector *const vector, t_length const index)
{
	return ((char **)vector_get(vector, index));
}
