/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:24:50 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/28 18:08:34 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

void	token_display(void *const object)
{
	t_token *const	token = object;

	if (token->data)
		printf("[%s, \e[94m%s\e[0m] ", g_type_write[token->type], token->data);
	else
		printf("[%s] ", g_type_write[token->type]);
}

void	token_destroy(void *const object)
{
	t_token *const	token = object;

	free(token->data);
}

void	*token_cpy(void *dest, void *src, t_length const len)
{
	t_token *const	dest1 = dest;
	t_token *const	src1 = src;

	(void)len;
	*dest1 = *src1;
	if (dest1->data)
		dest1->data = ft_strdup(dest1->data);
	return (dest1);
}
