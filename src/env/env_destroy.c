/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:38:38 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/24 20:47:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	__env_entry_destroy(void *const object)
{
	free(*((char **)object));
}

inline void	_env_destroy(t_vector *env)
{
	vector_for_each(env, &__env_entry_destroy);
}
