/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:25:45 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 01:01:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_getenv(t_vector *const env, const char *name)
{
	char	**str;
	int		name_len;

	str = vector_get(env, 0);
	name_len = ft_strlen(name);
	while (*str)
	{
		if (!ft_strncmp(*str, name, name_len) && (*str)[name_len] == '=')
			return (ft_strtrim((*str) + name_len + 1, "\t "));
		str++;
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
