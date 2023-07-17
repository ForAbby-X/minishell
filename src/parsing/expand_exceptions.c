/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exceptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:04:15 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/17 17:39:05 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*exp_get_var(char const c)
{
	if (c == '\0')
		return (ft_strdup("$"));
	else if (c == '$')
		return (ft_strdup("MY_PID"));
	else if (c == '?')
		return (ft_strdup("ERROR_CODE"));

}
