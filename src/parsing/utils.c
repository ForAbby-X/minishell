/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:41:00 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/27 01:43:53 by alde-fre         ###   ########.fr       */
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

int	ft_strncmp(char const *str0, char const *str1, size_t len)
{
	while (--len && *str0 && *str0 == *str1)
	{
		++str0;
		++str1;
	}
	return (*str0 - *str1);
}
