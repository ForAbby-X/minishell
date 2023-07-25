/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:25:45 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/24 02:58:37 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_getenv(t_vector const *const env, const char *name)
{
	char	**str;
	int		name_len;

	str = vector_get(env, 0);
	name_len = ft_strlen(name);
	while (*str)
	{
		if (!ft_strncmp(*str, name, name_len) && (*str)[name_len] == '=')
			return (ft_strchr(*str, '=') + 1);
		str++;
	}
	return (NULL);
}

static void	_remove_env_var_size(char *name, t_vector *env, int name_len)
{
	char		**str;
	t_length	i;

	i = 0;
	str = vector_get(env, 0);
	while (env->size && i < env->size - 1)
	{
		if (ft_strncmp(str[i], name, name_len) == 0 && str[i][name_len] == '=')
		{
			free(*((char **)vector_get(env, i)));
			vector_erase(env, i);
		}
		++i;
	}
}

t_merror	set_env_var(char *var, char	*sep, t_vector *env)
{
	char	*copy;

	copy = ft_strdup(var);
	if (copy == NULL)
		return (MEMORY_ERROR);
	_remove_env_var_size(var, env, sep - var);
	if (vector_insert(env, &copy, env->size - 1) == NULL)
		return (free(copy), FAILURE);
	return (SUCCESS);
}

char	**env_add(t_vector *const vector, char *const obj)
{
	return ((char **)vector_addback(vector, obj));
}

char	**env_get(t_vector *const vector, t_length const index)
{
	return ((char **)vector_get(vector, index));
}
