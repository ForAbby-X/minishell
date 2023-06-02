/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:24:50 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/01 23:54:20 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_display(void *const object)
{
	t_token *const	token = object;

	if (token->data)
		printf("[%s] - %s\n", g_type_write[token->type], token->data);
	else
		printf("[%s]\n", g_type_write[token->type]);
}

void	token_destroy(void *const object)
{
	t_token *const	token = object;

	free(token->data);
}

t_token	*tokens_add(t_vector *const vector, t_token	*const obj)
{
	return ((t_token *)vector_addback(vector, obj));
}

t_token	*tokens_get(t_vector *const vector, t_length const index)
{
	return ((t_token *)vector_get(vector, index));
}

int	is_tok_operator(t_token *const token)
{
	if (token->type >= HEREDOC && token->type >= PIPE)
		return (1);
	return (0);
}
