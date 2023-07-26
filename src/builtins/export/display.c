/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 07:03:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"

static inline int	__env_var_display(void *const object)
{
	char *const	*line = object;

	errno = 0;
	if (*line)
	{
		if (ft_putstrendl_fd_check(*line, STDOUT_FILENO))
		{
			set_err("export",
				(char*[]){"write error: ", strerror(errno)}, 2, 1);
			return (1);
		}
	}
	return (0);
}

void	display_env_sorted(t_vector *env)
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
		if (__env_var_display(less))
			return ;
		last = less;
	}
}
