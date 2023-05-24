/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:24:50 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/24 19:05:55 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_display(void *const object)
{
	t_token *const	token = object;

	printf("[%s]token : %s\n", g_type_write[token->type], token->data);
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
