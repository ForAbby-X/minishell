/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exceptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:04:15 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/18 17:33:41 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*exp_get_var(char const c)
{
	if (c == '\0')
		return ("$");
	else if (c == '$')
		return ("MY_PID");
	else if (c == '?')
		return ("ERROR_CODE");
	return (NULL);
}
