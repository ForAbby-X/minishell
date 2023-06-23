/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:35:44 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/24 00:36:20 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "vector.h"
# include "error.h"
# include "libft.h"

char	**env_add(t_vector *const vector, char	*const obj)
		__attribute__((always_inline));

char	**env_get(t_vector *const vector, t_length const index)
		__attribute__((always_inline));

char	*ft_getenv(t_vector *const vector, const char *name);

#endif
