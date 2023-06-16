/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:41:00 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 17:18:17 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_separator(char const c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	is_quotes(char const c)
{
	return (c == '\'' || c == '"');
}

int	is_operator(char const c)
{
	return (c == '|' || c == '<' || c == '>');
}
