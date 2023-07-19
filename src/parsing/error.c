/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:30:36 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/19 15:58:59 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_merror	pars_error(char *const str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	write(STDERR_FILENO, "\'\n", 2);
	set_exit_code(2);
	return (PARSING_ERROR);
}

t_merror	check_tok_error(t_vector *const tokens)
{
	t_token		*last_token;
	t_token		*token;
	t_length	index;

	index = 0;
	last_token = &(t_token){NULL, PIPE};
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		if (is_tok_operator(last_token) && token->type == PIPE)
			return (pars_error(token->data));
		else if (is_tok_operator(last_token) && is_tok_operator(token)
			&& last_token->type != PIPE)
			return (pars_error(token->data));
		else if (index == vector_size(tokens) - 1 && is_tok_operator(token))
			return (pars_error("newline"));
		last_token = token;
		index++;
	}
	return (SUCCESS);
}
