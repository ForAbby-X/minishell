/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:41:00 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 13:15:03 by alde-fre         ###   ########.fr       */
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

int	is_tok_alpha(t_token const *const token)
{
	return (token->type == WORD
		|| token->type == DOUBLE_QUOTED
		|| token->type == SINGLE_QUOTED);
}

int	is_tok_operator(t_token const *const token)
{
	if (token->type >= HEREDOC && token->type <= PIPE)
		return (1);
	return (0);
}
