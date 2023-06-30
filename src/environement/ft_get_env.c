/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:23:16 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/30 18:51:02 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

char	*ft_get_env(t_vector const *const env, char const *const var)
{
	char	**str;

	str = vector_get(env, 0);
	while (*str)
	{
		if (ft_strncmp(*str, var, ft_strlen(var)) == 0)
			return (ft_strchr(*str, '=') + 1);
		str++;
	}
	return (NULL);
}
